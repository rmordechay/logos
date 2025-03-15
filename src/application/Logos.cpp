#include "application/Logos.h"

#include <ANTLRInputStream.h>
#include <AntlrConverter.h>
#include <CodeGenerator.h>
#include <LogosLexer.h>
#include <LogosParser.h>
#include <ThreadPool.h>
#include <funcs/LgsPrint.h>

void Logos::run() {
    // Initial
    initProject();

    // Parsing
    const auto files = parseFiles();

    // Analysis
    ProjectAnalyser projectAnalyser(files);
    if (!projectAnalyser.analyse()) return;
    const auto globalSymbols = getGlobalsSymbols(files);
    if (!analyse(files, globalSymbols)) return;

    // Code generation
    const auto mainFile = getMainFile(files);
    CodeGenerator::generateCode(mainFile, globalSymbols);

    // Linking
    LgsLinker::link(modules);

    // Running
    system(execFile.c_str());
}

vector<LgsFile*> Logos::parseFiles() {
    ThreadPool threadPool;
    threadPool.start();
    vector<LgsFile*> files;
    parseTree(rootDir, files, threadPool);
    threadPool.wait();
    return files;
}

void Logos::parseTree(const string& path, vector<LgsFile*>& files, ThreadPool& threadPool) {
    for (const auto& entry : directory_iterator(path)) {
        if (isLogosFile(entry)) {
            threadPool.runTask([entry, &files, this] {
                const auto file = parseFile(entry);
                {
                    lock_guard lock(mtx);
                    files.emplace_back(file);
                }
            });
        } else if (is_directory(entry.status())) {
            parseTree(entry.path(), files, threadPool);
        }
    }
}

map<string, LgsSymbol> Logos::getGlobalsSymbols(const vector<LgsFile*>& files) {
    map<string, LgsSymbol> globalSymbols;
    globalSymbols[LOGOS_PRINT.logosName] = LgsSymbol(BUILTIN_FUNC, &LOGOS_PRINT);
    for (const auto& file : files) {
        if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
            const auto object = objFile->obj;
            globalSymbols[object->getName()] = LgsSymbol(OBJECT, object);
        } else if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
            for (const auto &func : mainFile->funcs) {
                globalSymbols[func->name] = LgsSymbol(FUNC_IMPL, func);
            }
        }
    }
    return globalSymbols;
}

LgsFile* Logos::parseFile(const directory_entry& fileEntry) const {
    auto absFilePath = canonical(fileEntry).string();
    ifstream file(absFilePath);
    stringstream fileContents;
    fileContents << file.rdbuf();
    auto codeText = fileContents.str();

    auto input = ANTLRInputStream(codeText);
    auto lexer = LogosLexer(&input);
    auto tokens = CommonTokenStream(&lexer);
    auto parser = LogosParser(&tokens);
    auto parsedFile = parser.logosFile();

    auto logosFile = AntlerConverter::getLogosFile(parsedFile, absFilePath);
    logosFile->relPath = relative(absFilePath, rootDir).lexically_relative(LOGOS_SRC_DIR);
    return logosFile;
}

bool Logos::analyse(const vector<LgsFile*>& files, const map<string, LgsSymbol>& globalSymbols) {
    ThreadPool threadPool;
    threadPool.start();
    vector<bool> semaSuccess;
    for (const auto& file : files) {
        threadPool.runTask([=, &file, &semaSuccess, &globalSymbols] {
            SemaAnalyser semaAnalyser(file);
            semaAnalyser.logosStack.globalSymbols = globalSymbols;
            semaAnalyser.analyse();
            {
                lock_guard lock(mtx);
                semaSuccess.push_back(semaAnalyser.successful);
            }
        });
    }
    threadPool.wait();
    return std::find(semaSuccess.begin(), semaSuccess.end(), false) == semaSuccess.end();
}

void Logos::validateProject() const {
    string srcDir;
    for (const auto& entry : directory_iterator(rootDir)) {
        auto fileName = entry.path().filename();
        if (entry.is_directory() && fileName == LOGOS_SRC_DIR) {
            srcDir = entry.path().string();
        }
    }
    if (srcDir.empty()) {
        exitWithMessage(LOGOS_ERRORS.at(E10010));
    }
}

void Logos::initProject() const {
    initPaths();
    validateProject();
}

void Logos::initPaths() const {
    rootDir = rootPath;
    srcDir = rootPath / LOGOS_SRC_DIR;
    buildDir = rootPath / LOGOS_BUILD_DIR;
    objectFile = buildDir / OBJECT_FILE;
    execFile = buildDir / EXECUTABLE_FILE;
}

bool Logos::isLogosFile(const directory_entry& filePath) {
    return filePath.is_regular_file() && filePath.path().extension().string() == LOGOS_EXTENSION;
}

void Logos::exitWithMessage(const string& errMsg) {
    cout << errMsg << '\n';
    exit(0);
}

LgsMainFile* Logos::getMainFile(const vector<LgsFile*>& files) {
    unordered_map<string, LgsFile*> filesMap;
    for (const auto& file : files) {
        if (file->name == LOGOS_MAIN_FILE) {
            return dynamic_cast<LgsMainFile*>(file);
        }
    }
    return nullptr;
}
