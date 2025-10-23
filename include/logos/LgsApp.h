#pragma once
#include "LgsAppConfigs.h"
#include "codegen/LgsLinker.h"
#include "LgsSymbolTable.h"
#include "utils/LgsErrHandler.h"
#include "LgsPaths.h"
#include "analysis/LgsLinter.h"
#include "files/LgsFile.h"
#include "files/LgsFileMetadata.h"
#include "parser/LgsJsonParser.h"
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
    LgsSymbolTable globals;
    LgsAppMetadata metadata;
    LgsAppConfigs appConfigs;
    LgsErrHandler errHandler;
    std::vector<LgsFile*> srcFiles;
    std::vector<LgsEnvFile*> envFiles;
    std::vector<LgsTestFile*> testsFiles;
    std::map<FileID, fs::path> filePaths;
    std::atomic<FileID> nextFileID = 1;
    ThreadPool threadPool;

    void compile();
    bool setup();
    bool parse();
    bool analyse();
    bool generate();
    bool link();
    void loadBuiltins();
    void loadSrcFile(const std::string& code, const std::string& filePath, size_t fileID = 0);
    bool loadAppConfigFile();
    void loadEnvFiles();
    void initBuild();
    void writeIRFiles();
    void loadAppConfigs(const LgsAppConfigFile* configFile);
    size_t getNextFileID();
    ~LgsApp();
};
