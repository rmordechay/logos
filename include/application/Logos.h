#ifndef PROJECT_H
#define PROJECT_H

#include "ProjectAnalyser.h"

#include <string>
#include <thread>
#include <filesystem>
#include "SemaAnalyser.h"
#include <LgsLinker.h>

class ThreadPool;
using namespace filesystem;
using namespace std;
using namespace antlr4;
using namespace llvm;

inline path rootDir;
inline path srcDir;
inline path buildDir;
inline path objectFile;
inline path execFile;

class Logos {
public:
    mutex mtx;
    path rootPath;

    explicit Logos(const path& rootPath) : rootPath(rootPath) {}
    void run();
    void initProject() const;
    void initPaths() const;
    void validateProject() const;
    vector<LgsFile*> parseFiles();
    LgsFile* parseFile(const directory_entry&) const;
    void parseTree(const string& path, vector<LgsFile*>& files, ThreadPool& threadPool);
    bool analyse(const vector<LgsFile*>& files, const map<string, LgsSymbol>& globalSymbols);
    static LgsMainFile* getMainFile(const vector<LgsFile*>& files);
    static void setGlobalsSymbols(const vector<LgsFile*>& files, map<string, LgsSymbol>& globalSymbols);
    static bool isLogosFile(const directory_entry& filePath);
    static void exitWithMessage(const string& errMsg);
    ~Logos() = default;
};

#endif // PROJECT_H
