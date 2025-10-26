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
#include "files/LgsTestFile.h"
#include "parser/LgsParser.h"
#include "utils/LgsUtils.h"

void LgsApp::compile() {
    if (!setup()) errHandler.exitWithErrors();
    if (!parse()) errHandler.exitWithErrors();
    if (!analyse()) errHandler.exitWithErrors();
    if (!generate()) errHandler.exitWithErrors();
    if (!link()) errHandler.exitWithErrors();
}

bool LgsApp::setup() {
    if (paths.rootPath == "" && lgsCode.empty()) {
        errHandler.addError(E10086, nullptr, {paths.rootPath});
        return false;
    }

    // Code mode
    if (!lgsCode.empty()) {
        paths.rootPath = fs::temp_directory_path();
        paths.initPaths();
        return true;
    }

    // File mode
    if (isLogosFile(paths.rootPath)) {
        appConfigs.isFileMode = true;
        const auto filePath = paths.rootPath;
        paths.rootPath = fs::temp_directory_path();
        paths.initPaths();
        appMetadata.files.emplace_back(LgsFileMetadata(getNextFileID(), filePath));
        return true;
    }

    // Project mode
    paths.initPaths();
    if (!is_directory(paths.rootPath) || !is_directory(paths.srcDir) || !fs::exists(paths.appFilePath)) {
        errHandler.addError(E10010, nullptr);
        return false;
    }
    appMetadata.cacheFilePath = paths.cacheFile;

    // App config file
    appMetadata.files.emplace_back(LgsFileMetadata(
        getNextFileID(),
        paths.appFilePath,
        LGS_APP_CONFIG_FILE
    ));

    // Env files
    for (const auto& entry : fs::recursive_directory_iterator(paths.envsDir)) {
        appMetadata.files.emplace_back(LgsFileMetadata(
            getNextFileID(),
            entry.path(),
            LGS_ENV_FILE
        ));
    }

    // Src files
    auto isValid = true;
    for (const auto& entry : fs::recursive_directory_iterator(paths.srcDir)) {
        if (!isLogosFile(entry)) continue;
        const auto fileName = entry.path().filename();
        if (fileExists(entry, appMetadata.files)) {
            errHandler.addError(E10007, nullptr, {fileName});
            isValid = false;
            continue;
        }
        appMetadata.files.emplace_back(LgsFileMetadata(getNextFileID(), entry.path()));
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
        const auto filePath = appMetadata.files.front().path;
        const auto fileCode = getFileText(filePath);
        loadSrcFile(fileCode, filePath);
        return errHandler.successful;
    }
    // Project mode
    appMetadata.load();
    if (!loadAppConfigFile()) return false;
    if (!loadEnvFiles()) return false;
    for (auto& fileMetadata : appMetadata.files) {
        if (fileMetadata.type != LGS_SRC_FILE) continue;
        threadPool.runTask([&fileMetadata, this] {
            const auto fileCode = getFileText(fileMetadata.path);
            const auto file = loadSrcFile(fileCode, fileMetadata.path, fileMetadata.id);
            const auto hash = appMetadata.getHashByPath(file->absPath);
            fileMetadata.hash = file->hashFile();
            if (fileMetadata.hash != hash) {
                appMetadata.dirtyFiles.push_back(fileMetadata);
            }
        });
    }
    threadPool.wait();
    if (errHandler.successful) appMetadata.save();
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
    LgsLLVMGen::initLLVM();
    passBuilder.init();
    paths.execFilePath = paths.buildDir / appConfigs.name;
    for (const auto& file : srcFiles) {
        threadPool.runTask([this, file] {
            LgsCodeGen generator(*file, appConfigs, passBuilder, paths);
            generator.generate();
        });
    }
    threadPool.wait();
    return errHandler.successful;
}

bool LgsApp::link() {
    const LgsLinker linker(appConfigs, paths, srcFiles);
    return linker.link();
}

void LgsApp::loadBuiltins() {
    globals.addSymbol(LgsSymbol(new LgsSystem(), false, true), &errHandler);
    globals.addSymbol(LgsSymbol(new LgsPrint(), false, true), &errHandler);
    globals.addSymbol(LgsSymbol(new LgsTest(), false, true), &errHandler);
    globals.addSymbol(LgsSymbol(new LgsReflect(), false, true), &errHandler);
}

bool LgsApp::loadAppConfigFile() {
    const auto appFileID = getNextFileID();
    const auto fileCode = getFileText(paths.appFilePath);
    LgsParser parser(appFileID, paths.appFilePath, paths, globals, fileCode);
    const auto configFile = parser.parseAppConfigFile();
    auto appConfigMetadata = appMetadata.files.front();
    assert(appConfigMetadata.type == LGS_APP_CONFIG_FILE);
    appConfigMetadata.hash = configFile->hashFile();
    errHandler.mergeErrors(parser.errHandler);
    loadAppConfigs(configFile);
    return errHandler.successful;
}

LgsFile* LgsApp::loadSrcFile(const std::string& fileCode, const fs::path& filePath, size_t fileID) {
    if (fileID == 0) fileID = getNextFileID();
    LgsParser parser(fileID, filePath, paths, globals, fileCode);
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

bool LgsApp::loadEnvFiles() {
    if (appConfigs.isFileMode) return true;
    for (auto& fileMetadata : appMetadata.files) {
        if (fileMetadata.type != LGS_ENV_FILE) continue;
        const auto filePath = fileMetadata.path;
        if (!isLogosFile(filePath)) continue;
        threadPool.runTask([filePath, this, &fileMetadata] {
            const auto fileCode = getFileText(filePath);
            const auto fileID = getNextFileID();
            LgsParser parser(fileID, filePath, paths, globals, fileCode);
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
                errHandler.addError(E10068, &config->location, configFile->absPath, {value});
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
