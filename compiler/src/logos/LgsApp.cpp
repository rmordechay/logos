#include "logos/LgsApp.h"
#include <llvm/IR/Module.h>
#include "analysis/LgsSema.h"
#include "builtins/LgsTest.h"
#include "logos/LgsPaths.h"
#include "utils/ThreadPool.h"
#include "builtins/LgsPrint.h"
#include "builtins/LgsSys.h"
#include "files/LgsEnvFile.h"
#include "codegen/LgsCodeGen.h"
#include "codegen/LgsLinker.h"
#include "LgsConfigs.h"
#include "files/LgsTestFile.h"
#include "parser/LgsParser.h"
#include "LgsUtils.h"
#include "errors/LgsErrors.h"
#include "files/LgsAppConfigFile.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "types/iterables/LgsVec.h"
#include "types/primitives/LgsByte.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsUInt.h"
#include "types/primitives/LgsULong.h"
#include <llvm/Target/TargetMachine.h>

inline ThreadPool threadPool;

bool LgsApp::compile() {
    if (!setup()) return false;
    if (!loadConfigs()) return false;
    if (!loadDeps()) return false;
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
        appCache.addFileMetadata(filePath, LGS_SRC_FILE);
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
            appCache.addFileMetadata(entry.path(), LGS_ENV_FILE);
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
        appCache.addFileMetadata(entry.path(), LGS_SRC_FILE);
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
    for (auto& metadata : appCache.files) {
        if (metadata.type != LGS_SRC_FILE) continue;
        threadPool.runTask([&metadata, this] {
            loadSrcFile(metadata);
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
            LgsParser parser(&fileMetadata, paths, globals, true);
            parser.parseSrcFileHeaders();
        });
    }
    threadPool.wait();
    return errHandler.successful;
}

bool LgsApp::analyse() {
    loadBuiltins();
    if (!validateEnvs()) return false;
    if (!resolveGlobals()) return false;
    for (const auto file : srcFiles) {
        threadPool.runTask([this, file] {
            LgsSema sema(configs, file, globals);
            sema.analyse();
            if (sema.errHandler.successful) return;
            errHandler.mergeErrorsWithLock(sema.errHandler, mtx);
        });
    }
    threadPool.wait();
    return errHandler.successful;
}

bool LgsApp::generate() {
    createBuildDirs();
    LgsCgModule::initLLVM();
    if (!generateRTTTypes()) return false;
    if (!generateGenerics()) return false;

    // Main file is generated first non-concurrently
    const auto mainFile = getMainFile();
    assert(mainFile);
    LgsCodeGen mainCodeGen(mainFile, configs, globals, paths);
    if (!mainCodeGen.generate()) {
        errHandler.setUnsuccessful();
        printIR();
        return false;
    }
    for (const auto& file : srcFiles) {
        if (file->isMain()) continue;
        threadPool.runTask([this, file] {
            LgsCodeGen fileCodeCode(file, configs, globals, paths);
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
    paths.execFile = paths.buildDir / (configs.name != "" ? configs.name : LGS_DEFAULT_EXEC_FILE);
    std::vector<LgsFile*> files;
    files.reserve(srcFiles.size() + genericFiles.size());
    files.insert(files.end(), srcFiles.begin(), srcFiles.end());
    files.insert(files.end(), genericFiles.begin(), genericFiles.end());
    const LgsLinker linker(configs, paths, files);
    for (const auto& path : paths.userCLibs) {
        if (fs::exists(path)) continue;
        errHandler.addError(E10107, {path});
    }
    if (!errHandler.successful) return false;
    return linker.link();
}

void LgsApp::loadSrcFile(LgsFileMetadata& metadata) {
    const auto fileCode = getFileText(metadata.path);
    LgsParser parser(&metadata, paths, globals);
    const auto file = parser.parseSrcFile(configs.isTestRun);
    {
        std::lock_guard lock(mtx);
        if (!parser.errHandler.successful) return errHandler.mergeErrors(parser.errHandler);
        if (!file) return;
        srcFiles.push_back(file);
    }
}

void LgsApp::loadSrcFile(const std::string& fileCode, const fs::path& filePath) {
    LgsFileMetadata metadata(filePath);
    LgsParser parser(&metadata, paths, globals);
    parser.code = fileCode;
    const auto file = parser.parseSrcFile(configs.isTestRun);
    {
        std::lock_guard lock(mtx);
        if (file) srcFiles.push_back(file);
        if (parser.errHandler.successful) return;
        errHandler.mergeErrors(parser.errHandler);
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
    LgsFileMetadata metadata(paths.appConfigFile, LGS_APP_CONFIG_FILE);
    LgsParser parser(&metadata, paths, globals);
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
            LgsParser parser(&metadata, paths, globals);
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

bool LgsApp::loadDeps() const {
    return errHandler.successful;
}

void LgsApp::loadBuiltins() {
    globals.table.addSymbol(LgsSymbol(new LgsSys(), true, false), &errHandler);
    globals.table.addSymbol(LgsSymbol(new LgsPrint(), true, false), &errHandler);
    globals.table.addSymbol(LgsSymbol(new LgsTest(), true, false), &errHandler);
    globals.table.addSymbol(LgsSymbol(new LgsVarDec("_LINUX", &LGS_BOOL, new LgsIntConst(&LGS_BOOL, lgsConfigs.os == LINUX)), true, false), &errHandler);
    globals.table.addSymbol(LgsSymbol(new LgsVarDec("_MACOS", &LGS_BOOL, new LgsIntConst(&LGS_BOOL, lgsConfigs.os == MAC_OS)), true, false), &errHandler);
    globals.table.addSymbol(LgsSymbol(new LgsVarDec("_WINDOWS", &LGS_BOOL, new LgsIntConst(&LGS_BOOL, lgsConfigs.os == WINDOWS)), true, false), &errHandler);
    globals.table.rttTypes = {
        &LGS_STR, &LGS_CHAR, &LGS_BYTE, &LGS_BOOL, &LGS_INT, &LGS_UINT, &LGS_ULONG,
        &LGS_SHORT, &LGS_LONG, &LGS_SIZE, &LGS_FLOAT, &LGS_DOUBLE, &LGS_NULLABLE, &LGS_VOID
    };
}

bool LgsApp::resolveGlobals() {
    std::atomic successful = true;
    for (const auto& file : srcFiles) {
        threadPool.runTask([&] {
            LgsTypeResolver typeResolver(file, errHandler, globals);
            if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
                typeResolver.resolveMainFile(mainFile);
            } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
                typeResolver.resolveObj(objFile->obj);
            } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
                typeResolver.resolveInterface(interfaceFile->interface);
            }
            if (!errHandler.successful) {
                successful.store(false, std::memory_order_relaxed);
            }
        });
    }
    threadPool.wait();
    errHandler.successful = successful;
    return successful;
}

/**
 *  The runtime types are set in the semantic analysis
 */
bool LgsApp::generateRTTTypes() {
    rttTypeModule.setupModule("rttypes");
    rttTypeModule.mode = CG_MODE_RTTYPES;

    // Globals
    for (const auto type : globals.table.rttTypes) {
        type->getRTType(rttTypeModule);
    }
    for (auto [symbolName, symbol] : globals.table.symbols) {
        if (symbol.symbolType != OBJECT) continue;
        symbol.object->getRTType(rttTypeModule);
        for (const auto innerObj : symbol.object->objects) {
            innerObj->getRTType(rttTypeModule);
        }
    }

    // Source files
    for (const auto srcFile : srcFiles) {
        for (const auto type : srcFile->symbolTable.rttTypes) {
            type->getRTType(rttTypeModule);
        }
        if (const auto mainFile = dynamic_cast<LgsMainFile*>(srcFile)) {
            for (const auto object : mainFile->objects) {
                object->getRTType(rttTypeModule);
                for (const auto innerObj : object->objects) {
                    innerObj->getRTType(rttTypeModule);
                }
            }
        }
    }
    return rttTypeModule.writeIRModule(paths, 3);
}

bool LgsApp::generateGenerics() {
    std::unordered_map<std::string, LgsType*> generics;
    for (const auto srcFile : srcFiles) {
        generics.merge(srcFile->symbolTable.generics2);
    }
    if (generics.empty()) return true;
    const auto file = new LgsFile("generics");
    file->cg.setupModule("generics");
    file->cg.mode = CG_MODE_GENERICS;
    const LgsCodeGen cg(file, configs, globals, paths);
    for (auto& [_, generic] : generics) {
        if (const auto dArr = generic->asDArray()) {
            dArr->generateAddFunc(cg.cg);
            dArr->generateContainsFunc(cg.cg);
        } else if (const auto map = generic->asMap()) {
            map->generateGetFunc(cg.cg);
            map->generateAddFunc(cg.cg);
        } else if (const auto func = generic->asFuncType()) {
            if (func->name == MAP_FUNC) {
                cg.generateMapFunc(func);
            } else if (func->name == FILTER_FUNC) {
                cg.generateFilterFunc(func);
            } else if (func->name == FOREACH_FUNC) {
                cg.generateForeachFunc(func);
            } else {
                assert(0);
            }
        } else {
            assert(0);
        }
    }
    genericFiles.push_back(file);
    return file->cg.writeIRModule(paths, configs.optLevel);
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

void LgsApp::compareHash() const {
    for (const auto& file : srcFiles) {
        const auto oldHash = appCache.getHashByPath(file->path);
        const auto newHash = file->hashFile();
        if (newHash == oldHash) continue;
        assert(0);
    }
}

void LgsApp::printIR() const {
    if (!lgsConfigs.isDevMode || !lgsConfigs.printIR) return;
    rttTypeModule.IRModule->print(outs(), nullptr);
    logInfo(LGS_MSG_LINE_SEPERATOR);
    for (const auto& file : genericFiles) {
        if (!file->cg.IRModule) continue;
        file->cg.IRModule->print(outs(), nullptr);
        logInfo(LGS_MSG_LINE_SEPERATOR);
    }
    for (const auto& file : srcFiles) {
        if (!file->cg.IRModule) continue;
        file->cg.IRModule->print(outs(), nullptr);
        logInfo(LGS_MSG_LINE_SEPERATOR);
    }
}

void LgsApp::initPaths(const fs::path& root) {
    assert(root != "" && fs::exists(root));
    paths.rootPath = fs::canonical(root);
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
    for (const auto file : genericFiles) {
        delete file;
    }
    genericFiles.clear();
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
