#include "logos/LgsApp.h"
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/Module.h>
#include "configs/LgsConfig.h"
#include "LogosLexer.h"
#include "analysis/AntlrConverter.h"
#include "analysis/SemaAnalyser.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "logos/LgsPaths.h"
#include "utils/ThreadPool.h"
#include "builtins/LgsBuiltins.h"
#include "builtins/LgsSystem.h"
#include "lgsc/LgsCLang.h"
#include "files/LgsAppInfo.h"
#include "files/LgsEnvFile.h"
#include "funcs/LgsMainFunc.h"
#include "logos/LgsLinker.h"
#include "types/LgsInterface.h"
#include "utils/LgsUtils.h"
#include "llvm/IR/Verifier.h"
#include <llvm/Target/TargetMachine.h>

extern char **environ;

enum LogLevel {
    INFO,
    DEBUG,
    ERROR,
};

void LgsApp::run() {
    // Validation
    if (!validate()) exitWithErrors();

    // Lexing and Parsing
    if (!parse()) exitWithErrors();

    // Semantic analysis
    if (!analyse()) exitWithErrors();

    // Code generation
    if (!generate()) exitWithErrors();

    // Linking
    if (!link()) exitWithErrors();

    // Running
    execute();
}

bool LgsApp::validate() {
    if (!is_directory(paths.rootDir) || !is_directory(paths.srcDir)) {
        errHandler.addError(E10010, nullptr);
        return false;
    }
    if (!exists(paths.appFilePath)) {
        errHandler.addError(E10008, nullptr);
        return false;
    }
    return true;
}

bool LgsApp::parse() {
    loadBuiltins();
    if (!parseAppFile()) return false;
    for (const auto& entry : fs::recursive_directory_iterator(paths.srcDir)) {
        if (!isLogosFile(entry)) continue;
        threadPool.runTask([entry, this] {
            const auto absFilePath = fs::path(canonical(entry));
            const auto codeText = getFileText(absFilePath);
            parseSrcFile(codeText, absFilePath);
        });
    }
    threadPool.wait();
    if (!errHandler.successful) return false;
    return true;
}

bool LgsApp::analyse() {
    if (!resolveGlobalTypes()) exitWithErrors();
    for (const auto file : ast) {
        threadPool.runTask([this, file] {
            SemaAnalyser semaAnalyser(file, globals);
            semaAnalyser.analyse();
            std::lock_guard lock(mtx);
            if (!semaAnalyser.errHandler.successful) {
                errHandler.mergeErrors(semaAnalyser.errHandler);
            }
        });
    }
    threadPool.wait();
    return errHandler.successful;
}

bool LgsApp::generate() {
    initBuild();
    const auto targetMachine = LgsCodeGen::getTargetMachine();
    for (const auto& file : ast) {
        threadPool.runTask([file, targetMachine] {
            file->codeGen.setupModule(file->name, targetMachine->createDataLayout());
            file->generateIR();
        });
    }
    threadPool.wait();
    writeIRFiles();
    return errHandler.successful;
}

bool LgsApp::link() const {
    const LgsLinker linker(paths, ast);
    return linker.link();
}

void LgsApp::execute() {
    args.insert(args.begin(), const_cast<char*>(paths.execFilePath.c_str()));
    if (args.empty() || args.back() != nullptr) {
        args.push_back(nullptr);
    }
    execv(paths.execFilePath.c_str(), args.data());
    perror("Logos execution failed.");
    exit(EXIT_FAILURE);
}

void LgsApp::parseSrcFile(const std::string& codeText, fs::path filePath) {
    antlr4::ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    const auto file = parser.logosFile();
    if (!checkParserErrors(&parser)) return;
    AntlrConverter antlrConverter(filePath, globals);
    const auto lgsFile = antlrConverter.getLogosFile(file);
    ast.push_back(lgsFile);
    if (!lgsFile->externalCPaths.empty()) {
        LgsCLang lgsCLang(paths);
        lgsCLang.resolveCFiles(lgsFile);
        if (!lgsCLang.errHandler.successful) {
            std::lock_guard lock(mtx);
            errHandler.mergeErrors(antlrConverter.errHandler);
        }
    }
    if (!antlrConverter.errHandler.successful) {
        std::lock_guard lock(mtx);
        errHandler.mergeErrors(antlrConverter.errHandler);
    }
}

bool LgsApp::parseAppFile() {
    appInfo.appFilePath = fs::path(fs::canonical(paths.appFilePath));
    if (!fs::exists(appInfo.appFilePath)) return false;
    auto codeText = getFileText(paths.appFilePath);
    AntlrConverter antlerConverter(appInfo.appFilePath, globals);
    antlr4::ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    antlerConverter.getAppInfo(parser.logosAppFile(), appInfo);
    if (!checkParserErrors(&parser)) return false;
    if (!antlerConverter.errHandler.successful) {
        errHandler.mergeErrors(antlerConverter.errHandler);
    }
    return checkParserErrors(&parser) && errHandler.successful;
}

void LgsApp::parseEnvFile(fs::path fileEntry) {
    const auto absFilePath = fs::path(fs::canonical(fileEntry));
    const auto codeText = getFileText(fileEntry);
    AntlrConverter antlerConverter(absFilePath, globals);
    antlr4::ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    auto file = antlerConverter.getEnvFile(parser.logosEnvFile());
    if (!checkParserErrors(&parser)) return;
    std::lock_guard lock(mtx);
    envFiles.emplace_back(file);
    errHandler.mergeErrors(antlerConverter.errHandler);
}

bool LgsApp::checkParserErrors(LogosParser* parser) {
    if (parser->getNumberOfSyntaxErrors() > 0) {
        std::lock_guard lock(mtx);
        errHandler.setUnsuccessful();
        return false;
    }
    return true;
}

bool LgsApp::resolveGlobalTypes() {
    bool successful = true;
    for (const auto& file : ast) {
        SemaAnalyser semaAnalyser(file, globals);
        if (const auto mf = dynamic_cast<LgsMainFile*>(file)) {
            for (const auto object : mf->objects) {
                semaAnalyser.resolveObjTypes(object);
            }
            for (const auto interface : mf->interfaces) {
                semaAnalyser.resolveInterfaceTypes(interface);
            }
            for (const auto group : mf->groups) {
                semaAnalyser.resolveGroupTypes(group);
            }
            for (const auto [_, func] : mf->funcs) {
                if (dynamic_cast<LgsMainFunc*>(func)) continue;
                semaAnalyser.resolveFuncTypes(func->funcType);
            }
        } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
            semaAnalyser.resolveObjTypes(objFile->obj);
        } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
            semaAnalyser.resolveInterfaceTypes(interfaceFile->interface);
        }
        if (!semaAnalyser.errHandler.successful) {
            errHandler.mergeErrors(semaAnalyser.errHandler);
        }
        successful = successful && semaAnalyser.errHandler.successful;
    }
    return successful;
}

void LgsApp::loadBuiltins() {
    globals.addSymbol(LgsSymbol(new LgsPrint(), false, true), &errHandler);
    globals.addSymbol(LgsSymbol(new LgsSystem(), false, true), &errHandler);
}

void LgsApp::loadEnvFiles() {
    for (const auto& entry : fs::directory_iterator(paths.envsDir)) {
        if (!isLogosFile(entry)) continue;
        threadPool.runTask([entry, this] {
            parseEnvFile(entry);
        });
    }
    threadPool.wait();
}

void LgsApp::setEnvVars() {
    for (char **env = environ; *env != nullptr; ++env) {
        std::string entry(*env);
        const auto pos = entry.find('=');
        if (pos != std::string::npos) {
            auto key = entry.substr(0, pos);
            const auto value = entry.substr(pos + 1);
            assert(0);
        }
    }
}

void LgsApp::initBuild() {
    fs::create_directories(paths.buildDir);
    fs::create_directories(paths.buildIR);
    LgsCodeGen::initLLVM();
    paths.objFilePath = paths.buildDir / (appInfo.name + ".o");
    paths.execFilePath = paths.buildDir / appInfo.name;
}

void LgsApp::writeIRFiles() {
    for (const auto file : ast) {
        const auto module = file->codeGen.IRModule;
        if (!module) continue;
        if constexpr (LOG_LEVEL == DEBUG) {
            module->print(outs(), nullptr);
            logInfo("\n-----\n\n");
        }
        if (verifyModule(*module, &errs())) {
            errHandler.setUnsuccessful();
            continue;
        }
        if constexpr (WRITE_IR_TO_FILE) {
            const auto filePath = (paths.buildIR / module->getName().str()).string() + ".ll";
            std::error_code EC;
            raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
            module->print(textFile, nullptr);
        }
    }
}

void LgsApp::exitWithErrors() const {
    for (int i = 0; i < errHandler.errors.size(); ++i) {
        const auto lgsError = errHandler.errors[i];
        const auto path = "\n   at:  " + getFullPath(*lgsError.location);
        logInfo(LGS_ERROR_STR + std::string(lgsError.msg));
        logInfo(path);
        if (i != errHandler.errors.size() - 1) logInfo("\n---\n");
        else logInfo("\n");
        assert(strlen(lgsError.msg) > 0);
        free(lgsError.msg);
        if (lgsError.location->filePath) {
            free(lgsError.location->filePath);
        }
    }
    exit(1);
}

LgsApp::~LgsApp() {
    for (const auto file : ast) {
        delete file;
    }
}
