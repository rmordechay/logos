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
    LgsPaths paths;
    LgsGlobals globals;
    LgsAppCache appCache;
    LgsAppConfigs appConfigs;
    LgsErrHandler errHandler;
    std::vector<LgsFile*> srcFiles;
    std::vector<LgsEnvFile*> envFiles;
    std::vector<LgsTestFile*> testsFiles;
    LgsAppConfigFile* appConfigFile = nullptr;
    // Used when passing code directly.
    std::unordered_map<std::string, std::string> lgsCode;
    std::atomic<FileID> nextFileID = 1;

    LgsApp() = default;
    explicit LgsApp(const fs::path& rootPath) {
        assert(fs::exists(rootPath));
        paths.rootPath = fs::canonical(rootPath);
    }

    void compile();
    bool setup();
    bool parse();
    bool parseHeaders();
    void analyseEnvs();
    bool analyse();
    bool generate();
    bool link();
    LgsFile* loadSrcFile(const std::string& fileCode, const fs::path& filePath = LGS_MAIN_FILE, size_t fileID = 0);
    LgsFile* loadSrcFileHeaders(const std::string& fileCode, const fs::path& filePath, size_t fileID);
    bool loadConfigFile();
    bool loadEnvFiles();
    void loadAppConfigs();
    bool loadDeps();
    void loadBuiltins();
    size_t getNextFileID();
    ~LgsApp();
};
