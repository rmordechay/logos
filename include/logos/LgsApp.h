#pragma once
#include "LgsSymbolTable.h"
#include "utils/LgsErrHandler.h"
#include "LgsPaths.h"
#include "LogosParser.h"
#include "files/LgsAppInfo.h"
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
    LgsAppInfo appInfo;
    LgsSymbolTable globals;
    LgsErrHandler errHandler;
    std::vector<LgsFile*> ast;
    std::vector<LgsEnvFile*> envFiles;
    std::vector<char*> args;
    ThreadPool threadPool;
    LgsPaths paths;

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
    void exitWithErrors() const;
    bool checkParserErrors(LogosParser* parser);
    ~LgsApp();
};
