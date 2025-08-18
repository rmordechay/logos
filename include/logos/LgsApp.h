#pragma once
#include "LgsSymbolTable.h"
#include "utils/LgsErrHandler.h"
#include "LgsPaths.h"
#include "utils/ThreadPool.h"

#include <llvm/Passes/OptimizationLevel.h>

class LgsAppFile;
class LogosParser;
class LgsCodeGen;
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

enum LgsLogLevel {
    INFO,
    DEBUG,
    ERROR,
};

struct LgsAppConfigs {
    std::string name = "app";
    uint8_t optLevel = 2;
    bool debugMode = false;
    LgsLogLevel logLevel = INFO;
    std::string activeEnv = "Pro";
    struct { int major; int minor; int micro; } version{1, 0, 0};
};

class LgsApp final {
public:
    LgsPaths paths;
    LgsAppConfigs configs;
    LgsSymbolTable globals;
    LgsErrHandler errHandler;
    std::vector<LgsFile*> ast;
    std::vector<LgsEnvFile*> envFiles;
    std::atomic<size_t> nextFileID = 0;
    std::vector<char*> appArgs;
    ThreadPool threadPool;

    explicit LgsApp(const fs::path& rootOrFile = "") {
        paths.initPaths(rootOrFile);
    }

    void run();
    void validate();
    void parse();
    void analyse();
    void generate();
    void link();
    void execute();
    void loadBuiltins();
    void loadEnvFiles();
    void setEnvVariables();
    bool parseAppFile();
    void parseEnvFile(fs::path fileEntry);
    void parseSrcFile(const std::string& codeText, fs::path filePath = "");
    void initBuild();
    void writeIRFiles();
    void exitWithErrors() const;
    bool checkParserErrors(LogosParser* parser);
    void freeApp();
};
