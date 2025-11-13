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
#include "parser/LgsParser.h"
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
struct LgsBaseMsg;
struct LgsPaths;

inline std::mutex mtx;

class LgsApp final {
public:
    LgsPaths paths;
    LgsGlobals globals;
    LgsAppCache appCache;
    LgsAppConfigs configs;
    LgsErrHandler errHandler;
    LgsTypeResolver typeResolver;
    std::vector<LgsFile*> srcFiles;
    std::vector<LgsEnvFile*> envFiles;
    std::vector<LgsTestFile*> testFiles;
    LgsAppConfigFile* appConfigFile = nullptr;
    std::unordered_map<std::string, std::string> lgsCode; // Used when passing code directly.

    explicit LgsApp(const fs::path& rootPath = ""): typeResolver(errHandler, globals) {
        paths.rootPath = rootPath;
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
    void importCFiles();
    void createBuildDirs();
    bool validateEnvs();
    bool validateRequiredEnvs();
    void compareHash() const;
    void printIR() const;
    void initPaths(const fs::path& root);
    void mergeCImports(const LgsParser& parser);
    LgsMainFile* getMainFile() const;
    ~LgsApp();
};
