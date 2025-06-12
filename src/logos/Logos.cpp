#include "logos/Logos.h"
#include "codegen/LgsLinker.h"
#include "analysis/SemaAnalyser.h"
#include <analysis/AntlrConverter.h>
#include "codegen/CodeGenerator.h"
#include "logos/Platform.h"

void Logos::run() {
    // Validation
    if (!project.validateProject()) exit(1);

    // Lexing and Parsing
    if (!project.parseFiles()) exit(1);

    // Semantic analysis
    if (!project.analyse()) exit(1);

    // Code generation
    CodeGenerator::generate(project);
    if (!project.errHandler.successful) exit(1);

    // Linking
    const LgsLinker linker;
    if (!linker.link(project)) exit(1);

    // Running
    execv(application.paths.execFilePath.c_str(), args.data());
}