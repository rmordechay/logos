#include "logos/Logos.h"

void Logos::run() {
    // Validation
    if (!app.validate()) exit(1);

    // Lexing and Parsing
    if (!app.parse()) exit(1);

    // Semantic analysis
    if (!app.analyse()) exit(1);

    // Code generation
    if (!app.generate()) exit(1);

    // Linking
    if (!app.link()) exit(1);

    // Running
    app.run();
}
