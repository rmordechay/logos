#include "LgsConfigs.h"
#include "codegen/LgsLLVMGen.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "../external/include/doctest.h"

int main(const int argc, char** argv) {
    LgsLLVMGen::initLLVM();
    lgsConfigs.isDevMode = true;
    lgsConfigs.printIR = false;
    lgsConfigs.writeIRFiles = false;
    return doctest::Context(argc, argv).run();
}
