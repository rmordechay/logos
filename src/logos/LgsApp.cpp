#include "logos/LgsApp.h"
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/Module.h>
#include "analysis/LgsSema.h"
#include "builtins/LgsTest.h"
#include "logos/LgsPaths.h"
#include "utils/ThreadPool.h"
#include "builtins/LgsPrint.h"
#include "builtins/LgsReflect.h"
#include "builtins/LgsSystem.h"
#include "files/LgsEnvFile.h"
#include "codegen/LgsCodeGen.h"
#include "codegen/LgsLinker.h"
#include "data/LgsConfigs.h"
#include "files/LgsTestFile.h"
#include "parser/LgsLexer.h"
#include "parser/LgsParser.h"
#include "utils/LgsUtils.h"
#include "llvm/IR/Verifier.h"
#include <llvm/Target/TargetMachine.h>

void LgsApp::compile() {
    if (!setup()) errHandler.exitWithErrors();
    if (!parse()) errHandler.exitWithErrors();
    if (!analyse()) errHandler.exitWithErrors();
    if (!generate()) errHandler.exitWithErrors();
    if (!link()) errHandler.exitWithErrors();
}

bool LgsApp::setup() {
    if (paths.rootPath == "") {
        errHandler.addError(E10086, nullptr, {paths.rootPath});
        return false;
    }
    // File mode
    if (isLogosFile(paths.rootPath)) {
        appConfigs.isFileMode = true;
        metadata.files.emplace_back(LgsFileMetadata(getNextFileID(), fs::canonical(paths.rootPath)));
        return true;
    }

    // Project mode
    paths.initPaths();
    if (!is_directory(paths.rootPath) || !is_directory(paths.srcDir) || !fs::exists(paths.appFilePath)) {
        errHandler.addError(E10010, nullptr);
        return false;
    }

    // App file
    const auto appFileID = getNextFileID();
    metadata.files.emplace_back(LgsFileMetadata(
        appFileID,
        fs::canonical(paths.appFilePath),
        fs::last_write_time(paths.appFilePath))
    );

    // Src files
    auto isValid = true;
    for (const auto& entry : fs::recursive_directory_iterator(paths.srcDir)) {
        if (!isLogosFile(entry)) continue;
        const auto fileName = entry.path().filename();
        if (fileExists(entry, metadata.files)) {
            errHandler.addError(E10007, nullptr, {fileName});
            isValid = false;
            continue;
        }
        const auto fileID = getNextFileID();
        metadata.files.emplace_back(LgsFileMetadata(
            fileID,
            fs::canonical(entry.path()),
            fs::last_write_time(entry)
        ));
    }

    return isValid;
}

bool LgsApp::parse() {
    // assert(!appConfigs.isFileMode);
    // if (!loadAppConfigFile()) return false;
    // loadEnvFiles();
    for (auto& file : metadata.files) {
        if (file.id == 1) continue;
        threadPool.runTask([&file, this] {
            const auto code = getFileText(file.filePath);
            loadSrcFile(code, file.filePath, file.id);
        });
    }
    threadPool.wait();
    saveMetadata(metadata, paths.filesMetadata);
    return errHandler.successful;
}

bool LgsApp::analyse() {
    loadBuiltins();
    LgsTypeResolver typeResolver(errHandler, globals);
    if (!typeResolver.resolveGlobals(srcFiles, threadPool)) return false;
    for (const auto file : srcFiles) {
        threadPool.runTask([this, file] {
            LgsSema semaAnalyser(file, globals);
            semaAnalyser.analyse();
            if (semaAnalyser.errHandler.successful) return;
            {
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
    const auto targetMachine = LgsLLVMGen::getTargetMachine();
    for (const auto& file : srcFiles) {
        threadPool.runTask([this, file, targetMachine] {
            LgsCodeGen code(*file, appConfigs, *targetMachine, paths);
            code.generate();
        });
    }
    threadPool.wait();
    writeIRFiles();
    return errHandler.successful;
}

bool LgsApp::link() {
    const LgsLinker linker(appConfigs, paths, srcFiles);
    return linker.link();
}

void LgsApp::loadBuiltins() {
    globals.addSymbol(LgsSymbol(new LgsPrint(), false, true), &errHandler);
    globals.addSymbol(LgsSymbol(new LgsSystem(), false, true), &errHandler);
    globals.addSymbol(LgsSymbol(new LgsTest(), false, true), &errHandler);
    globals.addSymbol(LgsSymbol(new LgsReflect(), false, true), &errHandler);
}

void LgsApp::loadSrcFile(const std::string& code, const fs::path& filePath, size_t fileID) {
    if (fileID == 0) {
        fileID = getNextFileID();
    }
    LgsLexer lexer(fileID, code);
    const auto tokens = lexer.tokenize();
    if (!lexer.errHandler.successful) {
        std::lock_guard lock(mtx);
        errHandler.mergeErrors(lexer.errHandler);
        return;
    }
    LgsParser parser(fileID, filePath, paths, globals, tokens);
    const auto file = parser.parseSrcFile(appConfigs.isTestRun);
    {
        std::lock_guard lock(mtx);
        if (file) srcFiles.push_back(file);
        if (!parser.errHandler.successful) {
            errHandler.mergeErrors(parser.errHandler);
        }
    }
}

bool LgsApp::loadAppConfigFile() {
    const auto appFileID = getNextFileID();
    LgsLexer lexer(appFileID, getFileText(paths.appFilePath));
    const auto tokens = lexer.tokenize();
    if (!lexer.errHandler.successful) {
        errHandler.mergeErrors(lexer.errHandler);
        return false;
    }
    LgsParser parser(appFileID, paths.appFilePath, paths, globals, tokens);
    const auto configFile = parser.parseAppConfigFile();
    errHandler.mergeErrors(parser.errHandler);
    loadAppConfigs(configFile);
    return errHandler.successful;
}

void LgsApp::loadEnvFiles() {
    if (appConfigs.isFileMode) return;
    for (const auto& filePath : fs::directory_iterator(paths.envsDir)) {
        if (!isLogosFile(filePath)) continue;
        threadPool.runTask([filePath, this] {
            const auto code = getFileText(filePath);
            const auto fileID = nextFileID.fetch_add(1, std::memory_order_relaxed);
            LgsLexer lexer(fileID, code);
            const auto tokens = lexer.tokenize();
            if (!lexer.errHandler.successful) {
                errHandler.mergeErrors(lexer.errHandler);
                return;
            }
            LgsParser parser(fileID, filePath, paths, globals, tokens);
            const auto file = parser.parseEnvFile();
            if (!file) return;
            {
                std::lock_guard lock(mtx);
                envFiles.push_back(file);
            }
        });
    }
}

void LgsApp::initBuild() {
    assert(paths.buildDir != "");
    if (!fs::exists(paths.buildDir)) {
        fs::create_directories(paths.buildDir);
    }
    if (!fs::exists(paths.buildDirIR)) {
        fs::create_directories(paths.buildDirIR);
    }
    if (!fs::exists(paths.buildDirObjs)) {
        fs::create_directories(paths.buildDirObjs);
    }
    LgsLLVMGen::initLLVM();
    paths.execFilePath = paths.buildDir / appConfigs.name;
}

void LgsApp::writeIRFiles() {
    for (const auto file : srcFiles) {
        const auto module = file->generator.IRModule;
        if (!module) continue;
        if constexpr (DEBUG) {
            module->print(llvm::outs(), nullptr);
            logInfo(LGS_MSG_LINE_SEPERATOR);
        }
        if (verifyModule(*module, &llvm::errs())) {
            errHandler.setUnsuccessful();
            continue;
        }
        const auto filePath = (paths.buildDirIR / module->getName().str()).string() + ".ll";
        std::error_code EC;
        raw_fd_ostream textFile(filePath, EC, llvm::sys::fs::OF_None);
        module->print(textFile, nullptr);
    }
}

void LgsApp::loadAppConfigs(const LgsAppConfigFile* configFile) {
    if (!errHandler.successful) return;
    for (const auto config : configFile->configs) {
        const auto configNama = config->name;
        if (configNama == "name") {
            appConfigs.name = config->expr->asStrConst()->value;
        }
        if (configNama == "activeEnv") {
            appConfigs.activeEnv = config->expr->asStrConst()->value;
        }
        if (configNama == "version") {
            auto value = config->expr->asStrConst()->value;
            int consumed = 0;
            auto [major, minor, micro] = appConfigs.version;
            const auto s = std::sscanf(value.c_str(), "%lu.%lu.%lu%n", &major, &minor, &micro, &consumed) == 3;
            if (!s || value[consumed] != '\0') {
                errHandler.addError(E10068, &config->location, {value});
            }
        }
    }
    delete configFile;
}

size_t LgsApp::getNextFileID() {
    return nextFileID.fetch_add(1, std::memory_order_relaxed);
}

LgsApp::~LgsApp() {
    for (const auto file : srcFiles) {
        delete file;
    }
    srcFiles.clear();
    for (const auto envFile : envFiles) {
        delete envFile;
    }
    envFiles.clear();
    for (const auto testFile : testsFiles) {
        delete testFile;
    }
    testsFiles.clear();
}
