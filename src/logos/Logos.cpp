#include "logos/Logos.h"

#include "LgsGlobals.h"
#include "LgsLinker.h"
#include <ANTLRInputStream.h>
#include <AntlrConverter.h>
#include <CodeGenerator.h>
#include <LogosLexer.h>
#include <ThreadPool.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/MC/TargetRegistry.h>

void Logos::run() {
    // Project loading
    LgsProject project(&paths);
    if (!project.loadProject()) return;

    // Semantic analysis
    if (!analyse(project.files)) return;

    // Code generation
    generateCode(project.mainFile);

    // Linking
    const LgsLinker linker(paths.objFilePath, paths.execFilePath);
    if (!linker.link(modules)) return;

    // Running
    system(paths.execFilePath.c_str());
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

LgsMainFile* Logos::getMainFile(const vector<LgsFile*>& files) const {
    for (const auto& file : files) {
        if (file->name == LOGOS_MAIN_FILE_NAME) {
            return dynamic_cast<LgsMainFile*>(file);
        }
    }
    return nullptr;
}
