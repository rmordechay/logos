#pragma once
#include "LgsAppConfigs.h"
#include "codegen/LgsLinker.h"
#include "LgsSymbolTable.h"
#include "utils/LgsErrHandler.h"
#include "LgsPaths.h"
#include "utils/ThreadPool.h"
#include <llvm/Passes/OptimizationLevel.h>

class LgsTestFile;
class LgsAppFile;
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
    LgsPaths paths;
    LgsAppConfigs configs;
    LgsSymbolTable globals;
    LgsErrHandler errHandler;
    std::vector<LgsFile*> ast;
    std::vector<LgsTestFile*> tests;
    std::vector<LgsEnvFile*> envFiles;
    std::atomic<size_t> nextFileID = 1;
    std::vector<char*> appArgs;
    ThreadPool threadPool;
    bool isFileMode = false;

    explicit LgsApp(const fs::path& rootOrFile = "") {
        paths.rootDir = rootOrFile;
    }
    void run();
    bool setup();
    bool parse();
    bool analyse();
    bool generate();
    bool link();
    void execute();
    void loadBuiltins();
    void loadEnvFiles();
    bool parseAppFile();
    void parseEnvFile(const fs::path& filePath);
    void parseSrcFile(const std::string& code, const fs::path& filePath = "");
    void initBuild();
    void writeIRFiles();
    void exitWithErrors() const;
    LgsFile* getFileByID(size_t fileID) const;
    void freeApp();
};
