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
    SemaAnalyser::analyseFiles(project.files, errors);
    if (!errors.empty()) exit(1);

    // Code generation
    CodeGenerator::generate(project.mainFile);

    // Linking
    const LgsLinker linker(&paths);
    if (!linker.link()) exit(1);

    // Running
    execv(paths.execFilePath.c_str(), argv);
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
