#include "application/Logos.h"

#include <ANTLRInputStream.h>
#include <AntlrConverter.h>
#include <CodeGenerator.h>
#include <LogosLexer.h>
#include <LogosParser.h>
#include <ThreadPool.h>
#include <funcs/LogosPrint.h>

void Logos::run() {
    // Initial validation
    validateProject();

    // Parsing
    const auto files = parseFiles();

    // Analysis
    ProjectAnalyser projectAnalyser(files);
    if (!projectAnalyser.analyse()) return;
    const auto globalSymbols = getGlobalsSymbols(files);
    if (!analyse(files, globalSymbols)) return;

    // Code generation
    const auto mainFile = getMainFile(files);
    CodeGenerator codeGenerator(buildDir);
    codeGenerator.generateCode(mainFile, globalSymbols);

    // Linking
    LogosLinker linker(objectFile.c_str(), execFile.c_str());
    linker.link(modules);

    // Running
    system(execFile.c_str());
}

vector<LogosFile*> Logos::parseFiles() {
    ThreadPool threadPool;
    threadPool.start();
    vector<LogosFile*> files;
    parseTree(rootDir, files, threadPool);
    threadPool.wait();
    return files;
}

void Logos::parseTree(const string& path, vector<LogosFile*>& files, ThreadPool& threadPool) {
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

map<string, LogosSymbol> Logos::getGlobalsSymbols(const vector<LogosFile*>& files) {
    map<string, LogosSymbol> globalSymbols;
    globalSymbols[LOGOS_PRINT.logosName] = LogosSymbol(BUILTIN_FUNC, &LOGOS_PRINT);
    for (const auto& file : files) {
        if (const auto objFile = dynamic_cast<LogosObjectFile*>(file)) {
            const auto object = objFile->obj;
            globalSymbols[object->getName()] = LogosSymbol(OBJECT, object);
        } else if (const auto mainFile = dynamic_cast<LogosMainFile*>(file)) {
            for (const auto &func : mainFile->funcs) {
                globalSymbols[func->name] = LogosSymbol(FUNC_IMPL, func);
            }
        }
    }
    return globalSymbols;
}

LogosFile* Logos::parseFile(const directory_entry& fileEntry) const {
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

bool Logos::analyse(const vector<LogosFile*>& files, const map<string, LogosSymbol>& globalSymbols) {
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

bool Logos::isLogosFile(const directory_entry& filePath) {
    return filePath.is_regular_file() && filePath.path().extension().string() == LOGOS_EXTENSION;
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

void Logos::exitWithMessage(const string& errMsg) {
    cout << errMsg << '\n';
    exit(0);
}

LogosMainFile* Logos::getMainFile(const vector<LogosFile*>& files) {
    unordered_map<string, LogosFile*> filesMap;
    for (const auto& file : files) {
        if (file->name == LOGOS_MAIN_FILE) {
            return dynamic_cast<LogosMainFile*>(file);
        }
    }
    return nullptr;
}
