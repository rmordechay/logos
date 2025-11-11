#pragma once
#include "LgsAppCache.h"
#include "LgsAppConfigs.h"
#include "codegen/LgsLinker.h"
#include "LgsSymbolTable.h"
#include "utils/LgsErrHandler.h"
#include "LgsPaths.h"
#include "../tools/LgsLinter.h"
#include "analysis/LgsTypeResolver.h"
#include "data/LgsDefinitions.h"
#include "files/LgsFile.h"
#include "files/LgsFileMetadata.h"
#include "utils/ThreadPool.h"
#include <mutex>

class LgsAppConfigFile;
class LgsTestFile;
class LogosParser;
class LgsLLVMGen;
class LgsStrConst;
class LgsEnvFile;
class LgsObject;
class LgsFuncType;
class ThreadPool;
class LgsMainFile;
struct LgsBaseError;
struct LgsPaths;

inline std::mutex mtx;

class LgsApp final {
public:
    LgsPaths appPaths;
    LgsAppConfigs configs;
    LgsGlobals globals;
    LgsAppCache appCache;
    LgsErrHandler errHandler;
    LgsTypeResolver typeResolver;
    std::vector<LgsFile*> srcFiles;
    std::vector<LgsEnvFile*> envFiles;
    std::vector<LgsTestFile*> testFiles;
    std::atomic<FileID> nextFileID = 1;
    LgsAppConfigFile* appConfigFile = nullptr;
    std::unordered_map<std::string, std::string> lgsCode; // Used when passing code directly.

    explicit LgsApp(const fs::path& rootPath = ""): typeResolver(errHandler, globals) {
        appPaths.rootPath = rootPath;
    }

    bool compile();
    bool setup();
    bool parse();
    bool parseHeaders();
    bool analyse();
    bool generate();
    bool link();
    void loadSrcFile(LgsFileMetadata& metadata);
    void loadSrcFile(const std::string& fileCode, const fs::path& filePath = LGS_MAIN_FILE);
    bool loadConfigFile();
    bool loadEnvFiles();
    bool loadConfigs();
    bool loadDeps();
    void loadBuiltins();
    void createBuildDirs();
    bool validateEnvs();
    bool validateRequiredEnvs();
    void printErrors() const;
    void compareHash() const;
    size_t getNextFileID();
    bool initPaths(const fs::path& root);
    LgsMainFile* getMainFile() const;
    ~LgsApp();
};
