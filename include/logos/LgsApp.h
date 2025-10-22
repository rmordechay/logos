#pragma once
#include "LgsAppConfigs.h"
#include "codegen/LgsLinker.h"
#include "LgsSymbolTable.h"
#include "utils/LgsErrHandler.h"
#include "LgsPaths.h"
#include "analysis/LgsLinter.h"
#include "parser/LgsJsonParser.h"
#include "utils/ThreadPool.h"
#include <mutex>

class LgsConfigFile;
class LgsTestFile;
class LogosParser;
class LgsLLVMGen;
class LgsStrConst;
class LgsFile;
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
    LgsAppConfigs appConfigs;
    LgsSymbolTable globals;
    LgsErrHandler errHandler;
    std::vector<LgsFile*> srcFiles;
    std::vector<LgsEnvFile*> envFiles;
    std::vector<LgsTestFile*> testsFiles;
    std::map<size_t, fs::path> filePaths;
    LgsConfigFile* configFile = nullptr;
    std::atomic<size_t> nextFileID = 1;
    std::vector<char*> mainArgs;
    ThreadPool threadPool;
    LgsLinter linter;
    LgsPaths paths;

    void run();
    bool setup();
    bool parse();
    bool analyse();
    bool generate();
    bool link();
    void execute();
    void loadBuiltins();
    void loadSrcFile(const std::string& code, const fs::path& filePath = "");
    bool loadConfigFile();
    void loadEnvFiles();
    void initBuild();
    void writeIRFiles();
    void exitWithErrors() const;
    void loadConfigs();
    void printConfigs() const;
    ~LgsApp();
};
