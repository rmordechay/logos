#pragma once
#include "LgsAppCache.h"
#include "LgsAppConfigs.h"
#include "codegen/LgsLinker.h"
#include "LgsSymbolTable.h"
#include "utils/LgsErrHandler.h"
#include "LgsPaths.h"
#include "analysis/LgsLinter.h"
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
    LgsAppCache appCache;
    LgsSymbolTable globals;
    LgsAppConfigs configs;
    LgsErrHandler errHandler;
    std::vector<LgsFile*> srcFiles;
    std::vector<LgsEnvFile*> envFiles;
    std::vector<LgsTestFile*> testFiles;
    LgsAppConfigFile* appConfigFile = nullptr;
    std::atomic<FileID> nextFileID = 1;
    // Used when passing code directly.
    std::unordered_map<std::string, std::string> lgsCode;

    explicit LgsApp(const fs::path& rootPath = "") {
        appPaths.rootPath = rootPath;
    }

    bool compile();
    bool setup();
    bool parse();
    bool parseHeaders();
    void analyseEnvs();
    bool analyse();
    bool generate();
    bool link();
    void loadSrcFile(const std::string& fileCode, const fs::path& filePath = LGS_MAIN_FILE);
    void loadSrcFile(LgsFileMetadata& metadata);
    bool loadConfigFile();
    bool loadEnvFiles();
    bool loadConfigs();
    void compareHash() const;
    bool loadDeps();
    void loadBuiltins();
    size_t getNextFileID();
    void createBuildDirs();
    bool initPaths(const fs::path& root);
    ~LgsApp();
};
