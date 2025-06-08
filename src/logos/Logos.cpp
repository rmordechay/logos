#include "logos/Logos.h"
#include "codegen/LgsLinker.h"

#include "analysis/SemaAnalyser.h"
#include "utils/ThreadPool.h"
#include <analysis/AntlrConverter.h>
#include "codegen/CodeGenerator.h"
#include "logos/Platform.h"

#include <unistd.h>

void Logos::run() {
    // Load project and parse files
    if (!project.loadProject()) exit(1);

    // Semantic analysis
    SemaAnalyser::analyseFiles(project);
    if (!project.errors.empty()) exit(1);

    // Code generation
    CodeGenerator::generate(project);
    if (!project.errors.empty()) exit(1);

    // Linking
    const LgsLinker linker;
    if (!linker.link(project)) exit(1);

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