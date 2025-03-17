#include "logos/Logos.h"

#include "LgsLinker.h"

#include <ANTLRInputStream.h>
#include <AntlrConverter.h>
#include <CodeGenerator.h>
#include <LogosLexer.h>
#include <LogosParser.h>
#include <ThreadPool.h>
#include <funcs/LgsPrint.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/MC/TargetRegistry.h>

void Logos::run() {
    // Initial validation
    validateProject();

    // Parsing
    const auto files = parseFiles();

    // Project analysis
    ProjectAnalyser projectAnalyser(files);
    if (!projectAnalyser.analyse()) return;

    // Semantic analysis
    map<string, LgsSymbol> globalSymbols;
    addGlobalsSymbols(files, globalSymbols);
    if (!analyse(files, globalSymbols)) return;

    // Code generation
    generateCode(getMainFile(files), globalSymbols);

    // Linking
    const LgsLinker linker(objFilePath, execFilePath);
    linker.link(modules);
    cleanup(globalSymbols);

    // Running
    system(execFilePath.c_str());
}

vector<LgsFile*> Logos::parseFiles() {
    assert(rootDir != "" && "rootDir is empty");
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

void Logos::addGlobalsSymbols(const vector<LgsFile*>& files, map<string, LgsSymbol>& globalSymbols) {
    addBuiltinFuncs(globalSymbols);
    for (const auto& file : files) {
        if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
            const auto object = objFile->obj;
            globalSymbols[object->getName()] = LgsSymbol(OBJECT, object);
        } else if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
            for (const auto &func : mainFile->funcs) {
                globalSymbols[func->composedName] = LgsSymbol(FUNC, func);
            }
        }
    }
}

void Logos::addBuiltinFuncs(map<string, LgsSymbol>& globalSymbols) {
    const auto printIntFunc = new LgsPrint({new LgsParam("input", &LOGOS_INT)});
    const auto printFloatFunc = new LgsPrint({new LgsParam("input", &LOGOS_FLOAT)});
    const auto printStrFunc = new LgsPrint({new LgsParam("input", &LOGOS_STR)});
    const auto printCharFunc = new LgsPrint({new LgsParam("input", &LOGOS_CHAR)});
    globalSymbols[printIntFunc->composedName] = LgsSymbol(FUNC, printIntFunc);
    globalSymbols[printFloatFunc->composedName] = LgsSymbol(FUNC, printFloatFunc);
    globalSymbols[printStrFunc->composedName] = LgsSymbol(FUNC, printStrFunc);
    globalSymbols[printCharFunc->composedName] = LgsSymbol(FUNC, printCharFunc);
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

inline void initLLVM() {
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    InitializeAllTargetMCs();
    InitializeAllTargets();
    InitializeAllTargetInfos();
    string error;
    const auto targetTriple = sys::getDefaultTargetTriple();
    const auto target = TargetRegistry::lookupTarget(targetTriple, error);
    targetMachine = target->createTargetMachine(targetTriple, "generic", "", TargetOptions(), std::nullopt);
}

void Logos::generateCode(const LgsMainFile* mainFile, const map<string, LgsSymbol>& globalSymbols) const {
    create_directories(buildDir);
    initLLVM();
    CodeGenerator::generateModule(buildDir, mainFile, globalSymbols);
}

void Logos::validateProject() const {
    string srcDirPath;
    for (const auto& entry : directory_iterator(rootDir)) {
        auto fileName = entry.path().filename();
        if (entry.is_directory() && fileName == LOGOS_SRC_DIR) {
            srcDirPath = entry.path().string();
        }
    }
    if (srcDirPath.empty()) {
        cout << LOGOS_ERRORS.at(E10010) << '\n';
        exit(0);
    }
}

bool Logos::isLogosFile(const directory_entry& filePath) {
    return filePath.is_regular_file() && filePath.path().extension().string() == LOGOS_EXTENSION;
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

void Logos::cleanup(map<string, LgsSymbol> globalSymbols) const {
    for (const auto& [_, globalSymbol] : globalSymbols) {
        switch (globalSymbol.type) {
        case OBJECT:
            if (globalSymbol.object) delete globalSymbol.object;
            break;
        case FUNC:
            if (globalSymbol.func) delete globalSymbol.func;
            break;
        default:
            break;
        }
    }
}
