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
#include "parser/LgsParser.h"
#include "utils/LgsUtils.h"
#include <iostream>

inline ThreadPool threadPool;

void LgsApp::compile() {
    if (!setup()) errHandler.exitWithErrors();
    if (!loadConfigFile()) errHandler.exitWithErrors();
    if (!loadDeps()) errHandler.exitWithErrors();
    if (!parse()) errHandler.exitWithErrors();
    if (!analyse()) errHandler.exitWithErrors();
    if (!generate()) errHandler.exitWithErrors();
    if (!link()) errHandler.exitWithErrors();
}

bool LgsApp::setup() {
    if (lgsCode.empty() && (paths.rootPath == "" || !fs::exists(paths.rootPath))) {
        errHandler.addError(E10086, {paths.rootPath});
        return false;
    }

    // Code mode
    if (!lgsCode.empty()) {
        const auto dirName = "lgs_" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
        const auto fullPath = fs::temp_directory_path() / dirName;
        fs::create_directories(fullPath);
        paths.rootPath = fullPath;
        paths.initPaths();
        return true;
    }

    // File mode
    if (isLogosFile(paths.rootPath)) {
        appConfigs.isFileMode = true;
        // rootPath is replaced with temp dir and the file pass is stored in metadata
        const auto filePath = paths.rootPath;
        paths.rootPath = fs::temp_directory_path();
        paths.initPaths();
        appCache.files.emplace_back(LgsFileMetadata(getNextFileID(), filePath));
        return true;
    }

    // Project mode
    paths.initPaths();
    if (!is_directory(paths.rootPath) || !is_directory(paths.srcDir) || !fs::exists(paths.appFilePath)) {
        errHandler.addError(E10010);
        return false;
    }
    appCache.cacheFilePath = paths.cacheFile;

    // App config file
    appCache.files.emplace_back(LgsFileMetadata(getNextFileID(), paths.appFilePath, LGS_APP_CONFIG_FILE));

    // Env files
    if (fs::exists(paths.envsDir)) {
        for (const auto& entry : fs::recursive_directory_iterator(paths.envsDir)) {
            appCache.files.emplace_back(LgsFileMetadata(getNextFileID(), entry.path(), LGS_ENV_FILE));
        }
    }

    // Src files
    auto isValid = true;
    for (const auto& entry : fs::recursive_directory_iterator(paths.srcDir)) {
        if (!isLogosFile(entry)) continue;
        const auto fileName = entry.path().filename();
        if (fileExists(entry, appCache.files)) {
            errHandler.addError(E10007, {fileName});
            isValid = false;
            continue;
        }
        appCache.files.emplace_back(LgsFileMetadata(getNextFileID(), entry.path()));
    }

    return isValid;
}

bool LgsApp::parse() {
    // Code mode
    if (!lgsCode.empty()) {
        for (auto [path, code] : lgsCode) {
            loadSrcFile(code, path);
        }
        return errHandler.successful;
    }

    // File mode
    if (appConfigs.isFileMode) {
        const auto filePath = appCache.files.front().path;
        const auto fileCode = getFileText(filePath);
        loadSrcFile(fileCode, fs::canonical(filePath));
        return errHandler.successful;
    }

    // Project mode
    appCache.load();
    if (!loadEnvFiles()) return false;
    for (auto& fileMetadata : appCache.files) {
        if (fileMetadata.type != LGS_SRC_FILE) continue;
        threadPool.runTask([&fileMetadata, this] {
            const auto fileCode = getFileText(fileMetadata.path);
            const auto file = loadSrcFile(fileCode, fs::canonical(fileMetadata.path), fileMetadata.id);
            const auto hash = appCache.getHashByPath(file->absPath);
            fileMetadata.hash = file->hashFile();
            if (fileMetadata.hash != hash) {
                appCache.dirtyFiles.push_back(fileMetadata);
            }
        });
    }
    threadPool.wait();
    appCache.save();
    return errHandler.successful;
}


bool LgsApp::parseHeaders() {
    for (auto& fileMetadata : appCache.files) {
        if (fileMetadata.type != LGS_SRC_FILE) continue;
        threadPool.runTask([&fileMetadata, this] {
            const auto fileCode = getFileText(fileMetadata.path);
            loadSrcFileHeaders(fileCode, fs::canonical(fileMetadata.path), fileMetadata.id);
        });
    }
    threadPool.wait();
    if (errHandler.successful) appCache.save();
    return errHandler.successful;
}

void LgsApp::analyseEnvs() {
    if (!appConfigFile) return;
    for (const auto file : envFiles) {
        LgsSema semaAnalyser(file, globals);
        for (const auto varDec : file->varDecs) {
            varDec->setType(varDec->expr->type);
        }
    }
    for (const auto requiredEnv : appConfigFile->requiredEnvs) {
        for (const auto envFile : envFiles) {
            auto found = false;
            for (const auto varDec : envFile->varDecs) {
                if (varDec->name != requiredEnv->name) continue;
                if (!varDec->type || !requiredEnv->type) continue;
                if (!varDec->type->canCastTo(requiredEnv->type)) {
                    errHandler.addError(E10001, &varDec->location, envFile->absPath, {varDec->type->pname(), requiredEnv->type->pname()});
                }
                found = true;
                break;
            }
            if (found) continue;
            errHandler.addError(E10020, &requiredEnv->location, appConfigFile->absPath, {envFile->envName, requiredEnv->name, requiredEnv->type->pname()});
        }
    }
}

bool LgsApp::analyse() {
    loadBuiltins();
    analyseEnvs();
    LgsTypeResolver typeResolver(errHandler, globals);
    if (!typeResolver.resolveGlobals(srcFiles, threadPool)) return false;
    for (const auto file : srcFiles) {
        threadPool.runTask([this, file] {
            LgsSema semaAnalyser(file, globals);
            semaAnalyser.analyse();
            if (semaAnalyser.errHandler.successful) return;
            errHandler.mergeErrorsWithLock(semaAnalyser.errHandler);
        });
    }
    threadPool.wait();
    return errHandler.successful;
}

bool LgsApp::generate() {
    LgsLLVMGen::initLLVM();
    paths.execFilePath = paths.buildDir / appConfigs.name;
    for (const auto& file : srcFiles) {
        threadPool.runTask([this, file] {
            LgsCodeGen generator(*file, appConfigs, paths);
            const auto successful = generator.generate();
            if (!successful) {
                std::lock_guard lock(mtx);
                errHandler.setUnsuccessful();
            }
        });
    }
    threadPool.wait();
    if (lgsConfigs.devMode && lgsConfigs.printIR) {
        for (const auto& file : srcFiles) {
            std::lock_guard lock(mtx);
            file->cg.IRModule->print(llvm::outs(), nullptr);
            logInfo(LGS_MSG_LINE_SEPERATOR);
        }
    }
    return errHandler.successful;
}

bool LgsApp::link() {
    LgsLinker linker(appConfigs, paths, srcFiles);
    for (auto& [_, app] : globals.imports) {
        linker.externalLibs.push_back(app->paths.rootPath);
    }
    return linker.link();
}

LgsFile* LgsApp::loadSrcFile(const std::string& fileCode, const fs::path& filePath, size_t fileID) {
    if (fileID == 0) fileID = getNextFileID();
    LgsParser parser(fileID, filePath, paths, globals.symbolTable, fileCode);
    const auto file = parser.parseSrcFile(appConfigs.isTestRun);
    {
        std::lock_guard lock(mtx);
        if (file) srcFiles.push_back(file);
        if (!parser.errHandler.successful) {
            errHandler.mergeErrors(parser.errHandler);
        }
    }
    return file;
}

LgsFile* LgsApp::loadSrcFileHeaders(const std::string& fileCode, const fs::path& filePath, const size_t fileID) {
    LgsParser parser(fileID, filePath, paths, globals.symbolTable, fileCode);
    const auto file = parser.parseSrcFileHeaders();
    {
        std::lock_guard lock(mtx);
        if (file) srcFiles.push_back(file);
        if (!parser.errHandler.successful) {
            errHandler.mergeErrors(parser.errHandler);
        }
    }
    return file;
}

bool LgsApp::loadConfigFile() {
    const auto appFileID = getNextFileID();
    paths.appFilePath = fs::canonical(paths.appFilePath);
    const auto fileCode = getFileText(paths.appFilePath);
    LgsParser parser(appFileID, paths.appFilePath, paths, globals.symbolTable, fileCode);
    appConfigFile = parser.parseAppConfigFile();
    auto appConfigMetadata = appCache.files.front();
    assert(appConfigMetadata.type == LGS_APP_CONFIG_FILE);
    appConfigMetadata.hash = appConfigFile->hashFile();
    errHandler.mergeErrors(parser.errHandler);
    loadAppConfigs();
    return errHandler.successful;
}

bool LgsApp::loadEnvFiles() {
    if (appConfigs.isFileMode) return true;
    for (auto& fileMetadata : appCache.files) {
        if (fileMetadata.type != LGS_ENV_FILE) continue;
        const auto filePath = fileMetadata.path;
        if (!isLogosFile(filePath)) continue;
        threadPool.runTask([filePath, this, &fileMetadata] {
            const auto fileCode = getFileText(filePath);
            const auto fileID = getNextFileID();
            LgsParser parser(fileID, fs::canonical(filePath), paths, globals.symbolTable, fileCode);
            const auto envFile = parser.parseEnvFile();
            if (!envFile) return;
            fileMetadata.hash = envFile->hashFile();
            {
                std::lock_guard lock(mtx);
                envFiles.push_back(envFile);
            }
        });
    }
    return errHandler.successful;
}

void LgsApp::loadAppConfigs() {
    if (!errHandler.successful) return;
    for (const auto config : appConfigFile->configs) {
        const auto configNama = config->name;
        if (configNama == "name") {
            appConfigs.name = config->expr->asStrConst()->value;
        }
        if (configNama == "activeEnv") {
            appConfigs.activeEnv = config->expr->asStrConst()->value;
        }
        if (configNama == "library") {
            appConfigs.isLibrary = config->expr->asIntConst()->value;
        }
        if (configNama == "version") {
            auto value = config->expr->asStrConst()->value;
            int consumed = 0;
            auto [major, minor, micro] = appConfigs.version;
            const auto s = std::sscanf(value.c_str(), "%lu.%lu.%lu%n", &major, &minor, &micro, &consumed) == 3;
            if (!s || value[consumed] != '\0') {
                errHandler.addError(E10068, &config->location, appConfigFile->absPath, {value});
            }
        }
    }
}

bool LgsApp::loadDeps() {
    for (auto package : appConfigFile->packages) {
        const auto app = new LgsApp(paths.lgsPackagePath / "logos-test");
        if (!app->setup()) {
            errHandler.mergeErrorsWithLock(app->errHandler);
            return false;
        }
        if (!app->loadConfigFile()) {
            errHandler.mergeErrorsWithLock(app->errHandler);
            return false;
        }
        if (!app->parseHeaders()) {
            errHandler.mergeErrorsWithLock(app->errHandler);
            return false;
        }
        LgsTypeResolver typeResolver(app->errHandler, app->globals);
        if (!typeResolver.resolveGlobals(app->srcFiles, threadPool)) {
            errHandler.mergeErrorsWithLock(typeResolver.errHandler);
            return false;
        }
        globals.imports[app->appConfigs.name] = app;
    }
    return true;
}

void LgsApp::loadBuiltins() {
    globals.symbolTable.addSymbol(LgsSymbol(new LgsSystem(), false, true), &errHandler);
    globals.symbolTable.addSymbol(LgsSymbol(new LgsPrint(), false, true), &errHandler);
    globals.symbolTable.addSymbol(LgsSymbol(new LgsTest(), false, true), &errHandler);
    globals.symbolTable.addSymbol(LgsSymbol(new LgsReflect(), false, true), &errHandler);
}

size_t LgsApp::getNextFileID() {
    return nextFileID.fetch_add(1, std::memory_order_relaxed);
}

LgsApp::~LgsApp() {
    if (appConfigFile) {
        delete appConfigFile;
        appConfigFile = nullptr;
    }
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
    for (const auto& [_, app] : globals.imports) {
        delete app;
    }
    globals.imports.clear();
}
