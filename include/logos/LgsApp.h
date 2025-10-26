#pragma once
#include "LgsAppMetadata.h"
#include "LgsAppConfigs.h"
#include "codegen/LgsLinker.h"
#include "LgsSymbolTable.h"
#include "utils/LgsErrHandler.h"
#include "LgsPaths.h"
#include "analysis/LgsLinter.h"
#include "analysis/LgsTypeResolver.h"
#include "codegen/LgsLLVMPassBuilder.h"
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
    LgsSymbolTable globals;
    LgsAppMetadata appMetadata;
    LgsAppConfigs appConfigs;
    LgsErrHandler errHandler;
    std::vector<LgsFile*> srcFiles;
    std::vector<LgsEnvFile*> envFiles;
    std::vector<LgsTestFile*> testsFiles;
    std::map<FileID, fs::path> filePaths;
    std::atomic<FileID> nextFileID = 1;
    LgsLLVMPassBuilder passBuilder;
    ThreadPool threadPool;
    // Used when passing code directly.
    std::string code = "";

    LgsApp() = default;
    explicit LgsApp(const std::string& code) : code(code) {}
    void compile();
    bool setup();
    bool parse();
    bool analyse();
    bool generate();
    bool link();
    void loadBuiltins();
    LgsFile* loadSrcFile(const std::string& fileCode, const fs::path& filePath = LGS_MAIN_FILE, size_t fileID = 0);
    bool loadAppConfigFile();
    bool loadEnvFiles();
    void loadAppConfigs(const LgsAppConfigFile* configFile);
    size_t getNextFileID();
    ~LgsApp();
};
