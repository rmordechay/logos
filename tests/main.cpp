#include "LgsConfigs.h"
#include "codegen/LgsCodeGen.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "../external/include/doctest.h"

int main(const int argc, char** argv) {
    LgsCodeGen::initLLVM();
    lgsConfigs.isDevMode = true;
    lgsConfigs.printIR = false;
    lgsConfigs.writeIRFiles = false;
    return doctest::Context(argc, argv).run();
}
