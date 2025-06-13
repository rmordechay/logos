#include "logos/Logos.h"
#include <analysis/AntlrConverter.h>
#include "logos/Platform.h"

void Logos::run() {
    // Validation
    if (!project.validateProject()) exit(1);

    // Lexing and Parsing
    if (!project.parseFiles()) exit(1);

    // Semantic analysis
    if (!project.analyse()) exit(1);

    // Code generation
    if (!project.generate()) exit(1);

    // Linking
    if (!project.link()) exit(1);

    // Running
    execv(application.paths.execFilePath.c_str(), args.data());
}