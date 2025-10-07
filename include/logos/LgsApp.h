#pragma once
#include "LgsAppConfigs.h"
#include "codegen/LgsLinker.h"
#include "LgsSymbolTable.h"
#include "utils/LgsErrHandler.h"
#include "LgsPaths.h"
#include "utils/ThreadPool.h"

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
    LgsPaths paths;
    LgsAppConfigs appConfigs;
    LgsSymbolTable globals;
    LgsErrHandler errHandler;
    std::vector<LgsFile*> ast;
    std::vector<LgsTestFile*> testsFiles;
    std::vector<LgsEnvFile*> envFiles;
    std::atomic<size_t> nextFileID = 1;
    std::vector<char*> appArgs;
    ThreadPool threadPool;

    explicit LgsApp(const fs::path& rootPath = "") {
        paths.rootPath = rootPath;
    }
    void run();
    void runTests();
    bool setup();
    bool parse();
    bool analyse();
    bool generate();
    bool link();
    void execute();
    void loadBuiltins();
    void loadSrcFile(const std::string& code, const fs::path& filePath = "");
    bool loadAppFile();
    void loadEnvFiles();
    void initBuild();
    void writeIRFiles();
    void exitWithErrors() const;
    LgsFile* getFileByID(size_t fileID) const;
    void freeApp();
    ~LgsApp();
};
