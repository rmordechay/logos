#include "logos/Logos.h"
#include "LgsLinker.h"
#include "Platform.h"
#include "SemaAnalyser.h"
#include "utils/ThreadPool.h"
#include <AntlrConverter.h>
#include <CodeGenerator.h>
#include <unistd.h>
#include "LgsC.h"

void Logos::run() {
    // Project loading
    if (!project.loadProject(args)) exit(1);

    // Semantic analysis
    SemaAnalyser::analyseFiles(&project, errors);
    if (!errors.empty()) exit(1);

    // Code generation
    CodeGenerator::generate(project.mainFile);

    // Linking
    const LgsLinker linker;
    if (!linker.link()) exit(1);

    // Running
    execv(paths.execFilePath.c_str(), args.data());
}

void Logos::initPaths(const path& rootDirPath) const {
    assert(rootDirPath != "");
    paths.rootDir = rootDirPath;
    paths.rootDirAbs = canonical(rootDirPath);
    paths.srcDir = paths.rootDir / LOGOS_SRC_DIR;
    paths.envsDir = paths.rootDir / LOGOS_ENVS_DIR;
    paths.buildDir = paths.rootDir / LOGOS_BUILD_DIR;
    paths.objFilePath = paths.buildDir / LOGOS_OBJECT_FILE;
    paths.execFilePath = paths.buildDir / LOGOS_EXECUTABLE_FILE;
    paths.appFilePath = paths.rootDir / LOGOS_APP_FILE_NAME LOGOS_FILE_EXTENSION;
}