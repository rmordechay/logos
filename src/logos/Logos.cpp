#include "logos/Logos.h"
#include "codegen/LgsLinker.h"
#include "analysis/SemaAnalyser.h"
#include <analysis/AntlrConverter.h>
#include "codegen/CodeGenerator.h"
#include "logos/Platform.h"

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
    execv(application.paths.execFilePath.c_str(), args.data());
}