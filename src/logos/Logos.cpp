#include "logos/Logos.h"
#include "LgsLinker.h"
#include "utils/ThreadPool.h"

#include <AntlrConverter.h>
#include <CodeGenerator.h>
#include <LogosLexer.h>
#include <unistd.h>

void Logos::run(char* argv[]) {
    // Project loading
    if (!project.loadProject()) exit(1);

    // Semantic analysis
    if (!analyse(project.files)) exit(1);

    // Code generation
    CodeGenerator::generate(project.mainFile);

    // Linking
    const LgsLinker linker(&paths);
    if (!linker.link(modules)) exit(1);

    // Running
    execv(paths.execFilePath.c_str(), argv);
}

bool Logos::analyse(const vector<LgsFile*>& files) {
    ThreadPool threadPool;
    threadPool.start();
    for (const auto& file : files) {
        threadPool.runTask([=, &file] {
            SemaAnalyser semaAnalyser(file);
            semaAnalyser.analyse();
            lock_guard lock(mtx);
            errors.insert(errors.end(), semaAnalyser.errHandler.errors.begin(), semaAnalyser.errHandler.errors.end());
        });
    }
    threadPool.wait();
    return errors.empty();
}

void Logos::initPaths(const path& rootDirPath) const {
    assert(rootDirPath != "");
    paths.rootDir = rootDirPath;
    paths.rootDirAbs = canonical(rootDirPath);
    paths.srcDir = paths.rootDir / LOGOS_SRC_DIR;
    paths.envsDir = paths.rootDir / LOGOS_ENVS_DIR;
    paths.buildDir = paths.rootDir / LOGOS_BUILD_DIR;
    paths.objFilePath = paths.buildDir / OBJECT_FILE;
    paths.execFilePath = paths.buildDir / EXECUTABLE_FILE;
    paths.appFilePath = paths.rootDir / LOGOS_APP_FILE_NAME LOGOS_FILE_EXTENSION;
}

LgsMainFile* Logos::getMainFile(const vector<LgsFile*>& files) const {
    for (const auto& file : files) {
        if (file->name == LOGOS_MAIN_FILE_NAME) {
            return dynamic_cast<LgsMainFile*>(file);
        }
    }
    return nullptr;
}
