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
#include "exprs/unary/constants/LgsStrConst.h"
#include "lgsc/LgsCLang.h"
#include "files/LgsAppFile.h"
#include "files/LgsEnvFile.h"
#include "funcs/LgsMainFunc.h"
#include "logos/LgsLinker.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsInterface.h"
#include "utils/LgsUtils.h"

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
    execv(paths.execFilePath.c_str(), args.data());
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
    ThreadPool threadPool;
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
    ThreadPool threadPool;
    for (const auto file : files) {
        threadPool.runTask([file, this] {
            SemaAnalyser semaAnalyser(file, globals);
            semaAnalyser.analyse();
            if (semaAnalyser.errHandler.successful) {
                file->runtime = &runtime;
            } else {
                lock_guard lock(mtx);
                errHandler.mergeErrors(semaAnalyser.errHandler);
            }
        });
    }
    threadPool.wait();
    return errHandler.successful;
}

bool LgsApp::generate() {
    initBuild();
    ThreadPool threadPool;
    for (const auto& file : files) {
        threadPool.runTask([this, file] {
            file->codeGen.setupModule(file->name, targetMachine->createDataLayout());
            file->generateIR();
            if (!file->codeGen.IRModule) return;
            lock_guard lock(mtx);
        });
    }
    threadPool.wait();
    writeIRFiles();
    return errHandler.successful;
}

bool LgsApp::link() const {
    const LgsLinker linker(paths, files);
    return linker.link(targetMachine);
}

void LgsApp::parseSrcFile(const string& codeText, fs::path filePath) {
    antlr4::ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    const auto ast = parser.logosFile();
    if (parser.getNumberOfSyntaxErrors() != 0) {
        lock_guard lock(mtx);
        errHandler.setUnsuccessful();
        return;
    }
    AntlrConverter antlrConverter(filePath, globals);
    const auto file = antlrConverter.getLogosFile(ast);
    files.push_back(file);
    if (!file->externalCPaths.empty()) {
        LgsCLang lgsCLang(paths);
        lgsCLang.resolveCFiles(file);
        if (!lgsCLang.errHandler.successful) {
            lock_guard lock(mtx);
            errHandler.mergeErrors(antlrConverter.errHandler);
        }
    }
    if (!antlrConverter.errHandler.successful) {
        lock_guard lock(mtx);
        errHandler.mergeErrors(antlrConverter.errHandler);
    }
}

void LgsApp::parseEnvFile(fs::path fileEntry) {
    const auto absFilePath = new fs::path(fs::canonical(fileEntry));
    AntlrConverter antlerConverter(*absFilePath, globals);
    const auto codeText = getFileText(fileEntry);
    antlr4::ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    auto file = antlerConverter.getEnvFile(parser.logosEnvFile());
    lock_guard lock(mtx);
    envFiles.emplace_back(file);
    errHandler.mergeErrors(antlerConverter.errHandler);
}

void LgsApp::parseAppFile(fs::path fileEntry) {
    const auto absFilePath = new fs::path(fs::canonical(fileEntry));
    AntlrConverter antlerConverter(*absFilePath, globals);
    auto codeText = getFileText(fileEntry);
    antlr4::ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);

    appFile = antlerConverter.getAppFile(parser.logosAppFile());
    for (const auto& varDec : appFile->varDecs) {
        if (varDec->name == "name") {
            name = varDec->expr->asStrConst()->value;
        }
        if (varDec->name == "version") {
            version = varDec->expr->asStrConst()->value;
        }
        if (varDec->name == "activeEnv") {
            activeEnv.name = varDec->expr->asStrConst()->value;
        }
    }
}

bool LgsApp::resolveGlobalTypes() {
    bool successful = true;
    for (const auto& file : files) {
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
    ThreadPool threadPool;
    for (const auto& entry : fs::directory_iterator(paths.envsDir)) {
        if (!isLogosFile(entry)) continue;
        threadPool.runTask([entry, this] {
            parseEnvFile(entry);
        });
    }
    threadPool.wait();
}

void LgsApp::checkRequiredEnvVars() {
    for (const auto& [_, requireEnvVar] : appFile->requireEnvVars) {
        for (const auto envFile : envFiles) {
            auto found = false;
            for (const auto& varDec : envFile->varDecs) {
                if (name == varDec->name && requireEnvVar->equals(varDec->type)) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                errHandler.addError(E10020, nullptr, {envFile->name, name});
            }
        }
    }
}

void LgsApp::setEnvVars() {
    for (char **env = environ; *env != nullptr; ++env) {
        string entry(*env);
        const auto pos = entry.find('=');
        if (pos != string::npos) {
            auto key = entry.substr(0, pos);
            const auto value = entry.substr(pos + 1);
            activeEnv.envVars[key] = value;
        }
    }
}

void LgsApp::setupActiveEnv() {
    setEnvVars();
    parseAppFile(paths.appFilePath);
    loadEnvFiles();
    checkRequiredEnvVars();
}

void LgsApp::initBuild() {
    fs::remove_all(paths.buildDir);
    fs::create_directories(paths.buildDir);
    fs::create_directories(paths.buildIR);
    LgsCodeGen::initLLVM();
    setTargetMachine();
}

void LgsApp::writeIRFiles() const {
    for (const auto file : files) {
        const auto module = file->codeGen.IRModule;
        if (!module) continue;
        if constexpr (WRITE_IR_TO_FILE) {
            const auto filePath = (paths.buildIR / module->getName().str()).string() + ".ll";
            error_code EC;
            raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
            module->print(textFile, nullptr);
        }
        if constexpr (LOG_LEVEL == DEBUG) {
            module->print(outs(), nullptr);
            logInfo("\n-----\n\n");
        }
    }
}

void LgsApp::exitWithErrors() const {
    for (int i = 0; i < errHandler.errors.size(); ++i) {
        const auto lgsError = errHandler.errors[i];
        const auto code = "\n code:  " + string(lgsError.location->code);
        const auto path = "\n   at:  " + getFullPath(*lgsError.location);
        logInfo(LGS_ERROR_STR + string(lgsError.msg));
        // logInfo(code);
        logInfo(path);
        if (i != errHandler.errors.size() - 1) logInfo("\n---\n");
        else logInfo("\n");
        assert(strlen(lgsError.msg) > 0);
        assert(strlen(lgsError.location->filePath) > 0);
        assert(strlen(lgsError.location->code) > 0);
        free(lgsError.msg);
        free(lgsError.location->filePath);
        free(lgsError.location->code);
    }
    exit(1);
}

void LgsApp::setTargetMachine() {
    string error;
    const auto targetTriple = sys::getDefaultTargetTriple();
    const auto target = TargetRegistry::lookupTarget(targetTriple, error);
    targetMachine = target->createTargetMachine(targetTriple, "generic", "", TargetOptions(), nullopt);
}

LgsApp::~LgsApp() {
    for (const auto file : files) {
        delete file;
    }
}
