#pragma once
#include "LgsAppCache.h"
#include "LgsAppConfigs.h"
#include "LgsDefinitions.h"
#include "LgsPaths.h"
#include "errors/LgsErrHandler.h"

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
    LgsPaths paths;
    LgsAppConfigs configs;
    LgsAppCache appCache;
    LgsSymbolTable globals;
    LgsErrHandler errHandler;
    std::vector<LgsFile*> srcFiles;
    std::vector<LgsFile*> genericFiles;
    std::vector<LgsEnvFile*> envFiles;
    std::vector<LgsTestFile*> testFiles;
    std::vector<LgsApp*> importApps;
    LgsAppConfigFile* appConfigFile = nullptr;
    std::string lgsCode; // Used when passing code directly.
    LgsFile rttFile{"rtt", CG_MODE_RTTYPES};

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
    bool loadConfigs();
    void loadSrcFile(const std::string& fileCode, const fs::path& filePath);
    bool loadConfigFile();
    bool loadEnvFiles();
    void loadBuiltins();
    bool resolveGlobals();
    bool generateRTTTypes();
    bool generateGenerics();
    void createBuildDirs();
    bool validateProject();
    bool validateEnvsFiles();
    bool validateRequiredEnvs();
    bool resolveImports();
    void printIR() const;
    void initPaths(const fs::path& root);
    LgsMainFile* getMainFile() const;
    ~LgsApp();
};
