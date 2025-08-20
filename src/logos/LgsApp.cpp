#include "logos/LgsApp.h"
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/Module.h>
#include "configs/LgsConfig.h"
#include "LogosLexer.h"
#include "analysis/LgsParserAdapter.h"
#include "analysis/LgsSema.h"
#include "logos/LgsPaths.h"
#include "utils/ThreadPool.h"
#include "builtins/LgsBuiltins.h"
#include "builtins/LgsSystem.h"
#include "files/LgsEnvFile.h"
#include "logos/LgsLinker.h"
#include "types/LgsInterface.h"
#include "utils/LgsUtils.h"
#include "llvm/IR/Verifier.h"
#include <llvm/Target/TargetMachine.h>

extern char **environ;

void LgsApp::run() {
    validate();
    parse();
    analyse();
    generate();
    link();
    execute();
}

void LgsApp::validate() {
    if (!is_directory(paths.rootDir) || !is_directory(paths.srcDir)) {
        errHandler.addError(E10010, nullptr);
        exitWithErrors();
    }
    if (!exists(paths.appFilePath)) {
        errHandler.addError(E10008, nullptr);
        exitWithErrors();
    }
}

void LgsApp::parse() {
    loadBuiltins();
    if (!parseAppFile()) exitWithErrors();
    for (const auto& entry : fs::recursive_directory_iterator(paths.srcDir)) {
        if (!isLogosFile(entry)) continue;
        threadPool.runTask([entry, this] {
            const auto absFilePath = fs::path(canonical(entry));
            const auto codeText = getFileText(absFilePath);
            parseSrcFile(codeText, absFilePath);
        });
    }
    threadPool.wait();
    if (!errHandler.successful) exitWithErrors();
}

void LgsApp::analyse() {
    LgsTypeResolver typeResolver(errHandler, globals);
    if (!typeResolver.resolveGlobalTypes(ast)) {
        exitWithErrors();
    }
    for (const auto file : ast) {
        threadPool.runTask([this, file] {
            LgsSema semaAnalyser(file, globals);
            semaAnalyser.analyse();
            if (!semaAnalyser.errHandler.successful) {
                std::lock_guard lock(mtx);
                errHandler.mergeErrors(semaAnalyser.errHandler);
            }
        });
    }
    threadPool.wait();
    if (!errHandler.successful) exitWithErrors();
}

void LgsApp::generate() {
    initBuild();
    const auto targetMachine = LgsCodeGen::getTargetMachine();
    for (const auto& file : ast) {
        threadPool.runTask([this, file, targetMachine] {
            file->codeGen.appConfigs = &configs;
            file->codeGen.setupModule(file->name, targetMachine->createDataLayout());
            file->generateIR();
        });
    }
    threadPool.wait();
    writeIRFiles();
    if (!errHandler.successful) exitWithErrors();
}

void LgsApp::link() {
    const LgsLinker linker(configs, paths, ast);
    if (!linker.link()) exitWithErrors();
}

void LgsApp::execute() {
    appArgs.insert(appArgs.begin(), const_cast<char*>(paths.execFilePath.c_str()));
    if (appArgs.empty() || appArgs.back() != nullptr) {
        appArgs.push_back(nullptr);
    }
    freeApp();
    execv(paths.execFilePath.c_str(), appArgs.data());
    perror("Logos execution failed.");
    exit(EXIT_FAILURE);
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

void LgsApp::setEnvVariables() {
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

bool LgsApp::parseAppFile() {
    if (!fs::exists(paths.appFilePath)) return false;
    auto codeText = getFileText(paths.appFilePath);
    LgsParserAdapter antlrConverter(0, paths, globals);
    antlr4::ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    const auto file = parser.logosAppFile();
    antlrConverter.setAppConfigs(file, paths.appFilePath, configs);
    if (!checkParserErrors(&parser)) return false;
    if (!antlrConverter.errHandler.successful) {
        errHandler.mergeErrors(antlrConverter.errHandler);
    }
    return errHandler.successful;
}

void LgsApp::parseEnvFile(fs::path fileEntry) {
    const auto codeText = getFileText(fileEntry);
    auto fileID = nextFileID.fetch_add(1, std::memory_order_relaxed);
    LgsParserAdapter antlrConverter(fileID, paths, globals);
    antlr4::ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    const auto absFilePath = fs::path(fs::canonical(fileEntry));
    auto file = antlrConverter.getEnvFile(parser.logosEnvFile(), absFilePath);
    if (!checkParserErrors(&parser)) return;
    std::lock_guard lock(mtx);
    envFiles.emplace_back(file);
    errHandler.mergeErrors(antlrConverter.errHandler);
}

void LgsApp::parseSrcFile(const std::string& codeText, fs::path filePath) {
    antlr4::ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    const auto file = parser.logosFile();
    auto fileID = nextFileID.fetch_add(1, std::memory_order_relaxed);
    LgsParserAdapter antlrConverter(fileID, paths, globals);
    const auto lgsFile = antlrConverter.getLogosFile(file, filePath);
    checkParserErrors(&parser);
    {
        std::lock_guard lock(mtx);
        lgsFile->id = ast.size();
        ast.push_back(lgsFile);
        if (antlrConverter.errHandler.successful) return;
        errHandler.mergeErrors(antlrConverter.errHandler);
    }
}

void LgsApp::initBuild() {
    fs::create_directories(paths.buildDir);
    fs::create_directories(paths.buildIR);
    LgsCodeGen::initLLVM();
    paths.objFilePath = paths.buildDir / (configs.name + ".o");
    paths.execFilePath = paths.buildDir / configs.name;
}

void LgsApp::writeIRFiles() {
    for (const auto file : ast) {
        const auto module = file->codeGen.IRModule;
        if (!module) continue;
        if (verifyModule(*module, &errs())) {
            errHandler.setUnsuccessful();
            module->print(outs(), nullptr);
            continue;
        }
        if constexpr (LOG_LEVEL == DEBUG) {
            module->print(outs(), nullptr);
            logInfo(LGS_MSG_LINE_SEPERATOR);
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
        const auto err = errHandler.errors[i];
        const auto posInLine = std::to_string(err.location->posInLine);
        const auto lineNumber = std::to_string(err.location->lineStart);
        const auto file = ast[err.location->fileID];
        const auto filePath = file->absPath.string();
        const auto fullPath = filePath + ":" + lineNumber + ":" + posInLine;
        const auto path = "\n   at:  " + fullPath;
        logError(err.msg, path);
        if (i != errHandler.errors.size() - 1) logInfo(LGS_MSG_LINE_SEPERATOR);
    }
    exit(1);
}

bool LgsApp::checkParserErrors(LogosParser* parser) {
    if (parser->getNumberOfSyntaxErrors() > 0) {
        std::lock_guard lock(mtx);
        errHandler.setUnsuccessful();
        return false;
    }
    return true;
}

void LgsApp::freeApp() {
    for (const auto file : ast) {
        delete file;
    }
    ast.clear();
    for (const auto envFile : envFiles) {
        delete envFile;
    }
    envFiles.clear();
}
