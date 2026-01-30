#pragma once
#include "LgsAppCache.h"
#include "LgsAppConfigs.h"
#include "LgsPaths.h"

class LgsAppConfigFile;
class LgsTestFile;
class LogosParser;
class LgsCodeGen;
class LgsStrConst;
class LgsEnvFile;
class LgsObject;
class LgsFuncType;
class ThreadPool;
class LgsMainFile;
struct LgsBaseMsg;
struct LgsPaths;

inline std::mutex mtx;

class LgsApp final {
public:
    LgsAppConfigs configs;
    LgsAppCache appCache;
    LgsSymbolTable globals;
    LgsErrHandler errHandler;
    LgsCodeGen rttTypeModule;
    std::vector<LgsFile*> srcFiles;
    std::vector<LgsFile*> genericFiles;
    std::vector<LgsEnvFile*> envFiles;
    std::vector<LgsTestFile*> testFiles;
    LgsAppConfigFile* appConfigFile = nullptr;
    std::unordered_map<std::string, std::string> lgsCode; // Used when passing code directly.
    LgsPaths paths;

    explicit LgsApp(const fs::path& rootPath = "") {
        paths.rootPath = rootPath;
    }

    bool compile();
    bool setup();
    bool parse();
    bool parseHeaders();
    void parseCImports();
    bool analyse();
    bool generate();
    bool link();
    void loadSrcFile(LgsFileMetadata& metadata);
    void loadSrcFile(const std::string& fileCode, const fs::path& filePath = LGS_MAIN_FILE);
    bool loadConfigFile();
    bool loadEnvFiles();
    bool loadConfigs();
    bool loadDeps() const;
    void loadBuiltins();
    bool resolveGlobals();
    bool generateRTTTypes();
    bool generateGenerics();
    void createBuildDirs();
    bool validateEnvs();
    bool validateRequiredEnvs();
    void compareHash() const;
    void printIR() const;
    void initPaths(const fs::path& root);
    LgsMainFile* getMainFile() const;
    ~LgsApp();
};
