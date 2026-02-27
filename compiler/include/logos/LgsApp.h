#pragma once
#include <filesystem>
#include <mutex>
#include <string>
#include <vector>

#include "LgsAppCache.h"
#include "LgsAppConfigs.h"
#include "LgsPaths.h"
#include "errors/LgsErrHandler.h"
#include "LgsSymbolTable.h"
#include "codegen/LgsCodeGen.h"
#include "files/LgsFile.h"

class LgsAppFile;
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
    std::vector<LgsEnvFile*> envFiles;
    std::vector<LgsFile*> genericFiles;
    LgsFile rttFile{"rtt", CG_MODE_RTT};
    LgsAppFile* appFile = nullptr;
    std::vector<LgsApp*> importApps;
    std::string lgsCode; // Used when passing code directly

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
    void loadSrcFile(const fs::path& filePath);
    void loadSrcFile(const std::string& code, const fs::path& filePath);
    bool loadAppFile();
    bool loadEnvFiles();
    void loadBuiltins();
    bool resolveGlobals();
    bool generateMainFile();
    bool generateRTTTypes();
    bool generateGenerics();
    void createBuildDirs();
    bool validateProject();
    bool validateEnvsFiles();
    bool validateRequiredEnvs();
    bool resolvePackages();
    void printIR() const;
    void initPaths(const fs::path& root);
    LgsMainFile* getMainFile() const;
    ~LgsApp();
};
