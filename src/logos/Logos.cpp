#include "logos/Logos.h"

#include "LgsEnvFile.h"
#include "LgsGlobals.h"
#include "LgsLinker.h"
#include "builtin/LgsSys.h"

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
    // Project analysis
    const ProjectAnalyser projectAnalyser(&paths);
    if (!projectAnalyser.analyseStructure()) return;

    // Parsing
    const auto files = parseFiles();
    const auto envFiles = parseEnvs();

    // Semantic analysis
    loadBuiltins(envFiles);
    if (!analyse(files)) return;

    // Code generation
    generateCode(getMainFile(files));

    // Linking
    const LgsLinker linker(paths.objFilePath, paths.execFilePath);
    if (!linker.link(modules)) return;

    // Running
    system(paths.execFilePath.c_str());
}

vector<LgsFile*> Logos::parseFiles() {
    ThreadPool threadPool;
    threadPool.start();
    vector<LgsFile*> files;
    parseTree(paths.srcDir, files, threadPool);
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
    lgsFile->relPath = relative(absFilePath, paths.rootDir).lexically_relative(LOGOS_SRC_DIR);
    return lgsFile;
}

LgsFile* Logos::parseFile(const string& codeText, path absFilePath) const {
    ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    return AntlerConverter::getLogosFile(parser.logosFile(), absFilePath);
}

vector<LgsEnv*> Logos::parseEnvs() {
    ThreadPool threadPool;
    threadPool.start();
    vector<LgsEnv*> files;
    for (const auto& entry : directory_iterator(paths.envsDir)) {
        if (!isLogosFile(entry)) continue;
        threadPool.runTask([entry, &files, this] {
            const auto file = parseEnv(entry);
            {
                lock_guard lock(mtx);
                files.emplace_back(file);
            }
        });
    }
    threadPool.wait();
    return files;
}

string Logos::getFileText(path fileEntry) const {
    ifstream file(canonical(fileEntry));
    stringstream fileContents;
    fileContents << file.rdbuf();
    return fileContents.str();
}

LgsEnv* Logos::parseEnv(path fileEntry) const {
    auto absFilePath = canonical(fileEntry);
    auto codeText = getFileText(fileEntry);
    ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    return AntlerConverter::getLogosEnv(parser.logosEnvFile(), absFilePath);
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

void Logos::loadBuiltins(const vector<LgsEnv*>& envFiles) const {
    globals.funcs[LgsPrint::name] = {
        new LgsPrint({new LgsParam(new LgsInt())}),
        new LgsPrint({new LgsParam(new LgsFloat())}),
        new LgsPrint({new LgsParam(new LgsStr())}),
        new LgsPrint({new LgsParam(new LgsChar())}),
        new LgsPrint({new LgsParam(new LgsBool())}),
    };
    globals.symbols[LgsSys::name] = LgsSymbol(new LgsSys());
}

void Logos::initPaths(const path& rootDirPath) {
    paths.rootDir = rootDirPath;
    paths.srcDir = paths.rootDir / LOGOS_SRC_DIR;
    paths.envsDir = paths.rootDir / LOGOS_ENVS_DIR;
    paths.buildDir = paths.rootDir / LOGOS_BUILD_DIR;
    paths.objFilePath = paths.buildDir / LOGOS_BUILD_DIR;
    paths.execFilePath = paths.buildDir / LOGOS_BUILD_DIR;
    assert(paths.rootDir != "");
}

inline void Logos::initLLVM() const {
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
    create_directories(paths.buildDir);
    CodeGenerator::generateModule(paths.buildDir, mainFile);
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
