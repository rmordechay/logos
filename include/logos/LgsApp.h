#pragma once
#include "LgsSymbolTable.h"
#include "utils/LgsErrHandler.h"
#include "LgsPaths.h"
#include "LogosParser.h"
#include "files/LgsAppFile.h"
#include "lgsc/LgsCLang.h"
#include "utils/ThreadPool.h"

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

class LgsApp final {
public:
    LgsPaths paths;
    LgsSymbolTable globals;
    LgsErrHandler errHandler;
    std::vector<LgsFile*> ast;
    LgsAppFile* appFile = nullptr;
    std::vector<LgsEnvFile*> envFiles;
    std::atomic<size_t> nextFileID = 0;
    std::vector<char*> args;
    ThreadPool threadPool;

    explicit LgsApp(const fs::path& rootDirPath = "") {
        paths.initPaths(rootDirPath);
    }

    void execute();
    void run();
    bool validate();
    bool parse();
    bool analyse();
    bool generate();
    bool link() const;
    void initBuild();
    void parseSrcFile(const std::string& codeText, fs::path filePath = "");
    bool parseAppFile();
    void loadEnvFiles();
    void loadBuiltins();
    void parseEnvFile(fs::path fileEntry);
    bool resolveGlobalTypes();
    void setEnvVars();
    void writeIRFiles();
    bool checkParserErrors(LogosParser* parser);
    ~LgsApp();
};

