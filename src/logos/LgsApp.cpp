#include "logos/LgsApp.h"
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/Module.h>
#include "configs/LgsConfig.h"
#include "analysis/LgsParserAdapter.h"
#include "analysis/LgsSema.h"
#include "logos/LgsPaths.h"
#include "utils/ThreadPool.h"
#include "builtins/LgsPrint.h"
#include "builtins/LgsSystem.h"
#include "files/LgsEnvFile.h"
#include "codegen/LgsCodeGenVisitor.h"
#include "codegen/LgsLinker.h"
#include "utils/LgsUtils.h"
#include "llvm/IR/Verifier.h"
#include <llvm/Target/TargetMachine.h>

extern char **environ;

void LgsApp::run() {
    if (!setup()) exitWithErrors();
    if (!parse()) exitWithErrors();
    if (!analyse()) exitWithErrors();
    if (!generate()) exitWithErrors();
    if (!link()) exitWithErrors();
    execute();
}

bool LgsApp::setup() {
    if (isLogosFile(paths.rootDir)) {
        isFileMode = true;
        return true;
    }
    paths.initPaths();
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
            parseSrcFile(entry);
        });
    }
    threadPool.wait();
    return errHandler.successful;
}

bool LgsApp::analyse() {
    LgsTypeResolver typeResolver(errHandler, globals);
    if (!typeResolver.resolveGlobalTypes(ast)) {
        return false;
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
    return errHandler.successful;
}

bool LgsApp::generate() {
    initBuild();
    const auto targetMachine = LgsCodeGen::getTargetMachine();
    for (const auto& file : ast) {
        threadPool.runTask([this, file, targetMachine] {
            LgsCodeGenVisitor code(*file);
            code.generate(configs, *targetMachine);
        });
    }
    threadPool.wait();
    writeIRFiles();
    return errHandler.successful;
}

bool LgsApp::link() {
    const LgsLinker linker(configs, paths, ast);
    return linker.link();
}

void LgsApp::execute() {
    appArgs.insert(appArgs.begin(), const_cast<char*>(paths.execFilePath.c_str()));
    if (appArgs.empty() || appArgs.back() != nullptr) {
        appArgs.push_back(nullptr);
    }
    // freeApp();
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

bool LgsApp::parseAppFile() {
    LgsParserAdapter antlrConverter(0, paths, globals);
    antlrConverter.setAppConfigs(configs);
    if (!antlrConverter.errHandler.successful) {
        errHandler.mergeErrors(antlrConverter.errHandler);
    }
    return errHandler.successful;
}

void LgsApp::parseEnvFile(const fs::path& filePath) {
    const auto fileID = nextFileID.fetch_add(1, std::memory_order_relaxed);
    LgsParserAdapter antlrConverter(fileID, paths, globals);
    auto file = antlrConverter.getEnvFile(filePath);
    std::lock_guard lock(mtx);
    envFiles.emplace_back(file);
    errHandler.mergeErrors(antlrConverter.errHandler);
}

void LgsApp::parseSrcFile(const fs::path& filePath) {
    const auto fileID = nextFileID.fetch_add(1, std::memory_order_relaxed);
    LgsParserAdapter antlrConverter(fileID, paths, globals);
    const auto lgsFile = antlrConverter.parseFile(filePath);
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
        const auto module = file->generator.IRModule;
        if (!module) continue;
        if constexpr (LOG_LEVEL == DEBUG) {
            module->print(outs(), nullptr);
            logInfo(LGS_MSG_LINE_SEPERATOR);
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
        const auto err = errHandler.errors[i];
        const auto posInLine = std::to_string(err.location.posInLine);
        const auto lineNumber = std::to_string(err.location.lineStart);
        const auto file = ast[err.location.fileID];
        const auto filePath = file->absPath.string();
        const auto fullPath = filePath + ":" + lineNumber + ":" + posInLine;
        const auto path = "\n   at: " + fullPath;
        logError(err.msg, path);
        if (i != errHandler.errors.size() - 1) logInfo(LGS_MSG_LINE_SEPERATOR);
    }
    logInfo("\n");
    exit(1);
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
