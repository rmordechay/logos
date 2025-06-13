#include "logos/Logos.h"
#include <analysis/AntlrConverter.h>
#include "logos/Platform.h"

void Logos::run() {
    // Validation
    if (!app.validateProject()) exit(1);

    // Lexing and Parsing
    if (!app.parse()) exit(1);

    // Semantic analysis
    if (!app.analyse()) exit(1);

    // Code generation
    if (!app.generate()) exit(1);

    // Linking
    if (!app.link()) exit(1);

    // Running
    execv(app.paths.execFilePath.c_str(), args.data());
}
