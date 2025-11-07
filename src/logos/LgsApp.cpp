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
#include "../../include/logos/LgsConfigs.h"
#include "files/LgsTestFile.h"
#include "parser/LgsParser.h"
#include "utils/LgsUtils.h"
#include <iostream>

inline ThreadPool threadPool;

void LgsApp::compile() {
    if (!setup()) errHandler.exitWithErrors();
    if (!loadConfigs()) errHandler.exitWithErrors();
    // if (!loadDeps()) errHandler.exitWithErrors();
    if (!parse()) errHandler.exitWithErrors();
    if (!analyse()) errHandler.exitWithErrors();
    if (!generate()) errHandler.exitWithErrors();
    if (!link()) errHandler.exitWithErrors();
}

bool LgsApp::setup() {
    if (lgsCode.empty() && (appPaths.rootPath == "" || !fs::exists(appPaths.rootPath))) {
        errHandler.addError(E10086, {(appPaths.rootPath == "" ? LGS_EMPTY_STRING_LITERAL : appPaths.rootPath)});
        return false;
    }

    // Code mode
    if (!lgsCode.empty()) {
        configs.appMode = CODE_MODE;
        const auto now = std::chrono::system_clock::now().time_since_epoch().count();
        const auto dirName = "lgs_" + std::to_string(now);
        auto fullPath = fs::temp_directory_path() / dirName;
        createDir(fullPath);
        initPaths(fullPath);
        return true;
    }

    // File mode
    if (isLogosFile(appPaths.rootPath)) {
        configs.appMode = FILE_MODE;
        // rootPath is replaced with temp dir and the file path is stored in metadata
        const auto filePath = appPaths.rootPath;
        const auto rootPath = fs::temp_directory_path();
        initPaths(rootPath);
        appCache.addFileMetadata(getNextFileID(), filePath, LGS_SRC_FILE);
        return true;
    }

    // Project mode
    configs.appMode = PROJECT_MODE;
    initPaths(appPaths.rootPath);
    if (!is_directory(appPaths.rootPath) || !is_directory(appPaths.srcDir) || !fs::exists(appPaths.appConfigFile)) {
        errHandler.addError(E10010);
        return false;
    }

    // Env files
    if (fs::exists(appPaths.envsDir)) {
        for (const auto& entry : fs::recursive_directory_iterator(appPaths.envsDir)) {
            appCache.addFileMetadata(getNextFileID(), entry.path(), LGS_ENV_FILE);
        }
    }

    // Src files
    auto isValid = true;
    appCache.cacheFile = appPaths.cacheFile;
    for (const auto& entry : fs::recursive_directory_iterator(appPaths.srcDir)) {
        if (!isLogosFile(entry)) continue;
        const auto fileName = entry.path().filename();
        if (appCache.fileExists(entry)) {
            errHandler.addError(E10007, {fileName});
            isValid = false;
            continue;
        }
        appCache.addFileMetadata(getNextFileID(), entry.path(), LGS_SRC_FILE);
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
    if (configs.appMode == FILE_MODE) {
        auto metadata = appCache.files.front();
        loadSrcFile(metadata);
        return errHandler.successful;
    }

    // Project mode
    if (!loadEnvFiles()) return false;
    for (auto& fileMetadata : appCache.files) {
        if (fileMetadata.type != LGS_SRC_FILE) continue;
        threadPool.runTask([&fileMetadata, this] {
            loadSrcFile(fileMetadata);
        });
    }
    threadPool.wait();
    return errHandler.successful;
}

bool LgsApp::parseHeaders() {
    for (auto& fileMetadata : appCache.files) {
        if (fileMetadata.type != LGS_SRC_FILE) continue;
        threadPool.runTask([&fileMetadata, this] {
            const auto fileCode = getFileText(fileMetadata.path);
            LgsParser parser(fileMetadata, appPaths, globals, true);
            parser.parseSrcFileHeaders();
        });
    }
    threadPool.wait();
    return errHandler.successful;
}

void LgsApp::analyseEnvs() {
    if (!appConfigFile) return;
    for (const auto file : envFiles) {
        LgsSema semaAnalyser(configs, file, globals);
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
                    errHandler.addError(E10001, &varDec->location, envFile->path, {varDec->type->pname(), requiredEnv->type->pname()});
                }
                found = true;
                break;
            }
            if (found) continue;
            errHandler.addError(E10020, &requiredEnv->location, appConfigFile->path, {envFile->envName, requiredEnv->name, requiredEnv->type->pname()});
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
            LgsSema semaAnalyser(configs, file, globals);
            semaAnalyser.analyse();
            if (semaAnalyser.errHandler.successful) return;
            errHandler.mergeErrorsWithLock(semaAnalyser.errHandler);
        });
    }
    threadPool.wait();
    return errHandler.successful;
}

bool LgsApp::generate() {
    createBuildDirs();
    LgsLLVMGen::initLLVM();
    appPaths.execFile = appPaths.buildDir / (configs.name == "" ? LGS_DEFAULT_EXEC_FILE : configs.name);
    for (const auto& file : srcFiles) {
        threadPool.runTask([this, file] {
            LgsCodeGen generator(*file, configs, appPaths);
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
    LgsLinker linker(configs, appPaths, srcFiles);
    for (auto& [_, app] : globals.imports) {
        linker.externalLibs.push_back(app->appPaths.rootPath);
    }
    return linker.link();
}

void LgsApp::loadSrcFile(const std::string& fileCode, const fs::path& filePath) {
    const auto fileID = getNextFileID();
    LgsFileMetadata metadata(fileID, filePath);
    LgsParser parser(metadata, appPaths, globals);
    parser.code = fileCode;
    const auto file = parser.parseSrcFile(configs.isTestRun);
    {
        std::lock_guard lock(mtx);
        if (file) srcFiles.push_back(file);
        if (!parser.errHandler.successful) {
            errHandler.mergeErrors(parser.errHandler);
        }
    }
}

void LgsApp::loadSrcFile(LgsFileMetadata& metadata) {
    if (metadata.id == 0) metadata.id = getNextFileID();
    const auto fileCode = getFileText(metadata.path);
    LgsParser parser(metadata, appPaths, globals);
    const auto file = parser.parseSrcFile(configs.isTestRun);
    {
        std::lock_guard lock(mtx);
        if (file) srcFiles.push_back(file);
        if (!parser.errHandler.successful) {
            errHandler.mergeErrors(parser.errHandler);
        }
    }
}

bool LgsApp::loadConfigFile() {
    if (configs.appMode != PROJECT_MODE && configs.appMode != PKG_MANAGER_MODE) return true;
    if (appPaths.appConfigFile == "") {
        errHandler.addError(E10086, {LGS_EMPTY_STRING_LITERAL});
        return false;
    }
    if (!fs::exists(appPaths.appConfigFile)) {
        errHandler.addError(E10086, {appPaths.appConfigFile});
        return false;
    }
    LgsFileMetadata metadata(getNextFileID(), appPaths.appConfigFile, LGS_APP_CONFIG_FILE);
    LgsParser parser(metadata, appPaths, globals);
    appConfigFile = parser.parseAppConfigFile();
    return errHandler.successful;
}

bool LgsApp::loadEnvFiles() {
    assert(configs.appMode == PROJECT_MODE);
    for (auto& metadata : appCache.files) {
        if (metadata.type != LGS_ENV_FILE) continue;
        const auto filePath = metadata.path;
        if (!isLogosFile(filePath)) continue;
        threadPool.runTask([this, &metadata] {
            LgsParser parser(metadata, appPaths, globals);
            const auto envFile = parser.parseEnvFile();
            if (!envFile) return;
            metadata.hash = envFile->hashFile();
            {
                std::lock_guard lock(mtx);
                envFiles.push_back(envFile);
            }
        });
    }
    threadPool.wait();
    return errHandler.successful;
}

bool LgsApp::loadConfigs() {
    if (!errHandler.successful) return false;
    if (configs.appMode != PROJECT_MODE) return true;
    if (!loadConfigFile()) return false;
    for (const auto config : appConfigFile->configs) {
        const auto configNama = config->name;
        if (configNama == "name") {
            configs.name = config->expr->asStrConst()->value;
        }
        if (configNama == "activeEnv") {
            configs.activeEnv = config->expr->asStrConst()->value;
        }
        if (configNama == "library") {
            configs.isLibrary = config->expr->asIntConst()->value;
        }
        if (configNama == "version") {
            auto value = config->expr->asStrConst()->value;
            if (!configs.version.setVersion(value)) {
                errHandler.addError(E10068, &config->location, appConfigFile->path, {value});
                return false;
            }
        }
    }
    return true;
}

void LgsApp::compareHash() const {
    for (const auto& file : srcFiles) {
        const auto oldHash = appCache.getHashByPath(file->path);
        const auto newHash = file->hashFile();
        if (newHash == oldHash) continue;
        assert(0);
    }
}

bool LgsApp::loadDeps() {
    // for (auto package : appConfigFile->packages) {
    //     const auto app = new LgsApp(path);
    //     if (!app->setup()) {
    //         errHandler.mergeErrorsWithLock(app->errHandler);
    //         return false;
    //     }
    //     if (!app->loadConfigs()) {
    //         errHandler.mergeErrorsWithLock(app->errHandler);
    //         return false;
    //     }
    //     if (!app->parseHeaders()) {
    //         errHandler.mergeErrorsWithLock(app->errHandler);
    //         return false;
    //     }
    //     LgsTypeResolver typeResolver(app->errHandler, app->globals);
    //     if (!typeResolver.resolveGlobals(app->srcFiles, threadPool)) {
    //         errHandler.mergeErrorsWithLock(typeResolver.errHandler);
    //         return false;
    //     }
    //     globals.imports[app->configs.name] = app;
    // }
    return true;
}

void LgsApp::loadBuiltins() {
    globals.addSymbol(LgsSymbol(new LgsSystem(), true, false), &errHandler);
    globals.addSymbol(LgsSymbol(new LgsPrint(), true, false), &errHandler);
    globals.addSymbol(LgsSymbol(new LgsTest(), true, false), &errHandler);
    globals.addSymbol(LgsSymbol(new LgsReflect(), true, false), &errHandler);
}

size_t LgsApp::getNextFileID() {
    return nextFileID.fetch_add(1, std::memory_order_relaxed);
}

void LgsApp::createBuildDirs() {
    if (!fs::exists(appPaths.buildDir)) {
        createDir(appPaths.buildDir);
    }
    if (!fs::exists(appPaths.buildDirObjs)) {
        createDir(appPaths.buildDirObjs);
    }
    if (lgsConfigs.devMode && lgsConfigs.writeIRFiles && !fs::exists(appPaths.buildDirIR)) {
        createDir(appPaths.buildDirIR);
    }
}

bool LgsApp::initPaths(const fs::path& root) {
    assert(root != "");
    appPaths.rootPath = root;
    appPaths.srcDir = appPaths.rootPath / LGS_SRC_DIR;
    appPaths.envsDir = appPaths.rootPath / LGS_ENVS_DIR;
    appPaths.buildDir = appPaths.rootPath / LGS_BUILD_DIR;
    appPaths.appConfigFile = appPaths.rootPath / LGS_APP_FILE_NAME;
    appPaths.buildDirIR = appPaths.buildDir / LGS_BUILD_IR_DIR;
    appPaths.buildDirObjs = appPaths.buildDir / LGS_BUILD_OBJECTS_DIR;
    appPaths.cacheFile = appPaths.buildDir / LGS_FILES_CACHE_FILE;
    if (!appPaths.findLgsRuntime()) return false;
    if (!appPaths.findCLibRoot()) return false;
    if (!appPaths.findCLibHeaders()) return false;
    if (!appPaths.findLgsRootDir()) return false;
    return true;
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
    for (const auto testFile : testFiles) {
        delete testFile;
    }
    testFiles.clear();
    for (const auto& [_, app] : globals.imports) {
        delete app;
    }
    globals.imports.clear();
}
