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
#include "logos/LgsConfigs.h"
#include "files/LgsTestFile.h"
#include "lgsc/LgsCLang.h"
#include "parser/LgsParser.h"
#include "utils/LgsUtils.h"
#include <iostream>

inline ThreadPool threadPool;

bool LgsApp::compile() {
    if (!setup()) return false;
    if (!loadConfigs()) return false;
    // if (!loadDeps()) return false;
    if (!parse()) return false;
    if (!analyse()) return false;
    if (!generate()) return false;
    if (!link()) return false;
    return true;
}

bool LgsApp::setup() {
    if (lgsCode.empty() && (paths.rootPath == "" || !fs::exists(paths.rootPath))) {
        errHandler.addError(E10086, {(paths.rootPath == "" ? LGS_EMPTY_STR : paths.rootPath)});
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
    if (isLogosFile(paths.rootPath)) {
        configs.appMode = FILE_MODE;
        // rootPath is replaced with temp dir and the file path is stored in metadata
        const auto filePath = paths.rootPath;
        const auto rootPath = fs::temp_directory_path();
        initPaths(rootPath);
        appCache.addFileMetadata(getNextFileID(), filePath, LGS_SRC_FILE);
        return true;
    }

    // Project mode
    configs.appMode = PROJECT_MODE;
    initPaths(paths.rootPath);
    if (!is_directory(paths.rootPath) || !is_directory(paths.srcDir) || !fs::exists(paths.appConfigFile)) {
        errHandler.addError(E10010);
        return false;
    }

    // Env files
    if (fs::exists(paths.envsDir)) {
        for (const auto& entry : fs::recursive_directory_iterator(paths.envsDir)) {
            appCache.addFileMetadata(getNextFileID(), entry.path(), LGS_ENV_FILE);
        }
    }

    // Src files
    auto isValid = true;
    appCache.cacheFile = paths.cacheFile;
    for (const auto& entry : fs::recursive_directory_iterator(paths.srcDir)) {
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

    LgsCLang clang(paths.cLibHeadersDir);
    for (const auto cImport : globals.cImports) {
        auto headerName = cImport->value;
        if (globals.cLibHeaders.contains(headerName)) continue;
        const auto headerPath = paths.cLibHeadersDir / headerName;
        const auto cCode = getFileText(headerPath);
        if (cCode.empty()) {
            errHandler.addError(E10047, {LGS_C, cCode});
            continue;
        }
        LgsCLangParser parser;
        clang.parseFile(parser, cCode);
        globals.cLibHeaders[headerName] = parser.table;
    }
    return errHandler.successful;
}

bool LgsApp::parseHeaders() {
    for (auto& fileMetadata : appCache.files) {
        if (fileMetadata.type != LGS_SRC_FILE) continue;
        threadPool.runTask([&fileMetadata, this] {
            const auto fileCode = getFileText(fileMetadata.path);
            LgsParser parser(fileMetadata, paths, globals, true);
            parser.parseSrcFileHeaders();
        });
    }
    threadPool.wait();
    return errHandler.successful;
}

bool LgsApp::analyse() {
    loadBuiltins();
    if (!validateEnvs()) return false;
    if (!typeResolver.resolveGlobals(srcFiles, threadPool)) return false;
    for (const auto file : srcFiles) {
        threadPool.runTask([this, file] {
            LgsSema sema(configs, file, globals);
            sema.analyse();
            if (sema.errHandler.successful) return;
            errHandler.mergeErrorsWithLock(sema.errHandler);
        });
    }
    threadPool.wait();
    return errHandler.successful;
}

bool LgsApp::generate() {
    createBuildDirs();
    LgsLLVMGen::initLLVM();
    paths.execFile = paths.buildDir / (configs.name == "" ? LGS_DEFAULT_EXEC_FILE : configs.name);
    // Main file is generated first non-concurrently
    const auto mainFile = getMainFile();
    LgsCodeGen mainCodeGen(*mainFile, configs, globals, paths);
    if (!mainCodeGen.generate()) {
        errHandler.setUnsuccessful();
        printIR();
        return false;
    }

    for (const auto& file : srcFiles) {
        if (file->isMain()) continue;
        threadPool.runTask([this, file] {
            LgsCodeGen fileCodeCode(*file, configs, globals, paths);
            const auto successful = fileCodeCode.generate();
            if (!successful) {
                std::lock_guard lock(mtx);
                errHandler.setUnsuccessful();
            }
        });
    }
    threadPool.wait();
    printIR();
    return errHandler.successful;
}

bool LgsApp::link() {
    LgsLinker linker(configs, paths, srcFiles);
    for (auto& [_, app] : globals.table.imports) {
        linker.externalLibs.push_back(app->paths.rootPath);
    }
    return linker.link();
}

void LgsApp::loadSrcFile(LgsFileMetadata& metadata) {
    if (metadata.id == 0) metadata.id = getNextFileID();
    const auto fileCode = getFileText(metadata.path);
    LgsParser parser(metadata, paths, globals);
    const auto file = parser.parseSrcFile(configs.isTestRun);
    {
        std::lock_guard lock(mtx);
        if (!parser.errHandler.successful) return errHandler.mergeErrors(parser.errHandler);
        if (!file) return;
        srcFiles.push_back(file);
        mergeCImports(parser);
    }
}

void LgsApp::loadSrcFile(const std::string& fileCode, const fs::path& filePath) {
    LgsFileMetadata metadata(getNextFileID(), filePath);
    LgsParser parser(metadata, paths, globals);
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

bool LgsApp::loadConfigFile() {
    if (configs.appMode != PROJECT_MODE && configs.appMode != PKG_MANAGER_MODE) return true;
    if (paths.appConfigFile == "") {
        errHandler.addError(E10086, {LGS_EMPTY_STR});
        return false;
    }
    if (!fs::exists(paths.appConfigFile)) {
        errHandler.addError(E10086, {paths.appConfigFile});
        return false;
    }
    LgsFileMetadata metadata(getNextFileID(), paths.appConfigFile, LGS_APP_CONFIG_FILE);
    LgsParser parser(metadata, paths, globals);
    appConfigFile = parser.parseAppConfigFile();
    if (!parser.errHandler.successful) {
        errHandler.mergeErrors(parser.errHandler);
    }
    return errHandler.successful;
}

bool LgsApp::loadEnvFiles() {
    assert(configs.appMode == PROJECT_MODE);
    for (auto& metadata : appCache.files) {
        if (metadata.type != LGS_ENV_FILE) continue;
        const auto filePath = metadata.path;
        if (!isLogosFile(filePath)) continue;
        threadPool.runTask([this, &metadata] {
            LgsParser parser(metadata, paths, globals);
            const auto envFile = parser.parseEnvFile();
            if (!envFile) return;
            metadata.hash = envFile->hashFile();
            {
                std::lock_guard lock(mtx);
                envFiles.push_back(envFile);
                if (!parser.errHandler.successful) {
                    errHandler.mergeErrors(parser.errHandler);
                }
            }
        });
    }
    threadPool.wait();
    return errHandler.successful;
}

bool LgsApp::loadConfigs() {
    assert(errHandler.successful);
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
    //     LgsTypeResolver typeResolver(app->errHandler, app->globals.symbolTable);
    //     if (!typeResolver.resolveGlobals(app->srcFiles, threadPool)) {
    //         errHandler.mergeErrorsWithLock(typeResolver.errHandler);
    //         return false;
    //     }
    //     globals.symbolTable.imports[app->configs.name] = app;
    // }
    return true;
}

void LgsApp::loadBuiltins() {
    globals.table.addSymbol(LgsSymbol(new LgsSystem(), true, false), &errHandler);
    globals.table.addSymbol(LgsSymbol(new LgsPrint(), true, false), &errHandler);
    globals.table.addSymbol(LgsSymbol(new LgsTest(), true, false), &errHandler);
    globals.table.addSymbol(LgsSymbol(new LgsReflect(), true, false), &errHandler);
}

void LgsApp::mergeCImports(const LgsParser& parser) {
    for (auto localImport : parser.cImports) {
        auto it = std::ranges::find_if(globals.cImports, [localImport](const LgsStrConst* g) {
            return g->value == localImport->value;
        });
        if (it == std::ranges::end(globals.cImports)) {
            globals.cImports.push_back(localImport);
        } else {
            freeExpr(localImport);
        }
    }
}

void LgsApp::createBuildDirs() {
    if (!fs::exists(paths.buildDir)) {
        createDir(paths.buildDir);
    }
    if (!fs::exists(paths.buildDirObjs)) {
        createDir(paths.buildDirObjs);
    }
    if (lgsConfigs.isDevMode && lgsConfigs.writeIRFiles && !fs::exists(paths.buildDirIR)) {
        createDir(paths.buildDirIR);
    }
}

bool LgsApp::validateEnvs() {
    if (configs.appMode != PROJECT_MODE) return true;
    for (const auto file : envFiles) {
        LgsSema semaAnalyser(configs, file, globals);
        for (const auto varDec : file->varDecs) {
            varDec->setType(varDec->expr->type);
        }
    }
    return validateRequiredEnvs();
}

bool LgsApp::validateRequiredEnvs() {
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
            errHandler.addError(E10020, &requiredEnv->location, appConfigFile->path, {envFile->name, requiredEnv->name, requiredEnv->type->pname()});
        }
    }
    return errHandler.successful;
}

void LgsApp::printErrors() const {
    for (size_t i = 0; i < errHandler.errors.size(); ++i) {
        const auto err = errHandler.errors[i];
        const auto column = err.location.columnStart;
        const auto line = err.location.lineStart;
        auto lineStr = getLine(err.filePath, line);
        const auto firstNonSpace = std::ranges::find_if(lineStr, [](const unsigned char c) { return !std::isspace(c); });
        const auto trimmedCount = std::distance(lineStr.begin(), firstNonSpace);
        if (err.filePath != "") {
            auto errMsg = trim(lineStr);
            int indent = column - trimmedCount - 2;
            if (indent < 0) {
                indent = 0;
            }
            errMsg += '\n' + std::string(indent, '~');
            errMsg += '^';
            int rest = lineStr.size() - column + 1;
            if (rest > 0) {
                errMsg += std::string(rest, '~');
            }
            errMsg += '\n' + err.msg;
            const auto path = "\n   at: " + getFullPath(err.location, err.filePath);
            logError(errMsg, path);
        } else {
            logError(err.msg);
        }
        if (i != errHandler.errors.size() - 1) logInfo(LGS_MSG_LINE_SEPERATOR);
    }
    if (!errHandler.errors.empty()) logInfo("\n");
}

void LgsApp::compareHash() const {
    for (const auto& file : srcFiles) {
        const auto oldHash = appCache.getHashByPath(file->path);
        const auto newHash = file->hashFile();
        if (newHash == oldHash) continue;
        assert(0);
    }
}

size_t LgsApp::getNextFileID() {
    return nextFileID.fetch_add(1, std::memory_order_relaxed);
}

void LgsApp::printIR() const {
    if (!lgsConfigs.isDevMode || !lgsConfigs.printIR) return;
    std::lock_guard lock(mtx);
    for (const auto& file : srcFiles) {
        if (!file->cg.IRModule) continue;
        file->cg.IRModule->print(llvm::outs(), nullptr);
        logInfo(LGS_MSG_LINE_SEPERATOR);
    }
}

void LgsApp::initPaths(const fs::path& root) {
    assert(root != "");
    paths.rootPath = root;
    paths.srcDir = paths.rootPath / LGS_SRC_DIR;
    paths.envsDir = paths.rootPath / LGS_ENVS_DIR;
    paths.buildDir = paths.rootPath / LGS_BUILD_DIR;
    paths.appConfigFile = paths.rootPath / LGS_APP_FILE_NAME;
    paths.buildDirIR = paths.buildDir / LGS_BUILD_IR_DIR;
    paths.buildDirObjs = paths.buildDir / LGS_BUILD_OBJECTS_DIR;
    paths.cacheFile = paths.buildDir / LGS_FILES_CACHE_FILE;
    paths.findLgsRootDir();
    paths.findCLibHeaders();
}

LgsMainFile* LgsApp::getMainFile() const {
    for (const auto srcFile : srcFiles) {
        if (srcFile->isMain()) return dynamic_cast<LgsMainFile*>(srcFile);
    }
    return nullptr;
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
    for (const auto& [_, app] : globals.table.imports) {
        delete app;
    }
    globals.table.imports.clear();
}
