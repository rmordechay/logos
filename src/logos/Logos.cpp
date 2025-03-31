#include "logos/Logos.h"

#include "LgsGlobals.h"
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
    loadBuiltinFuncs();
    if (!analyse(files)) return;

    // Code generation
    generateCode(getMainFile(files));

    // Linking
    const LgsLinker linker(objFilePath, execFilePath);
    linker.link(modules);

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
    auto absFilePath = canonical(fileEntry);
    ifstream file(absFilePath);
    stringstream fileContents;
    fileContents << file.rdbuf();
    auto codeText = fileContents.str();
    auto lgsFile = parseFile(codeText, absFilePath);
    lgsFile->relPath = relative(absFilePath, rootDir).lexically_relative(LOGOS_SRC_DIR);
    return lgsFile;
}

LgsFile* Logos::parseFile(const string& codeText, path absFilePath) const {
    ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    return AntlerConverter::getLogosFile(parser.logosFile(), absFilePath);
}

bool Logos::analyse(const vector<LgsFile*>& files) {
    ThreadPool threadPool;
    threadPool.start();
    for (const auto& file : files) {
        threadPool.runTask([=, &file] {
            SemaAnalyser semaAnalyser(file);
            semaAnalyser.analyse();
            {
                lock_guard lock(mtx);
                errors.insert(errors.end(), semaAnalyser.errors.begin(), semaAnalyser.errors.end());
            }
        });
    }
    threadPool.wait();
    return errors.empty();
}

void Logos::loadBuiltinFuncs() const {
    globals.funcs[LgsPrint::name] = {
        new LgsPrint({new LgsParam(new LgsInt())}),
        new LgsPrint({new LgsParam(new LgsFloat())}),
        new LgsPrint({new LgsParam(new LgsStr())}),
        new LgsPrint({new LgsParam(new LgsChar())}),
        new LgsPrint({new LgsParam(new LgsBool())}),
    };
}

inline void initLLVM() {
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    InitializeAllTargetMCs();
    InitializeAllTargets();
    InitializeAllTargetInfos();
    string error;
    const auto target = TargetRegistry::lookupTarget(targetTriple, error);
    targetMachine = target->createTargetMachine(targetTriple, "generic", "", TargetOptions(), std::nullopt);
}

void Logos::generateCode(const LgsMainFile* mainFile) const {
    initLLVM();
    create_directories(buildDir);
    CodeGenerator::generateModule(buildDir, mainFile);
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
        cout << E10010.msg << '\n';
        exit(0);
    }
}

bool Logos::isLogosFile(const directory_entry& filePath) const {
    return filePath.is_regular_file() && filePath.path().extension().string() == LOGOS_EXTENSION;
}

LgsMainFile* Logos::getMainFile(const vector<LgsFile*>& files) const {
    unordered_map<string, LgsFile*> filesMap;
    for (const auto& file : files) {
        if (file->name == LOGOS_MAIN_FILE) {
            return dynamic_cast<LgsMainFile*>(file);
        }
    }
    return nullptr;
}
