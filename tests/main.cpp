#include "data/LgsConfigs.h"
#include "codegen/LgsLLVMGen.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "external/doctest.h"

int main(const int argc, char** argv) {
    LgsLLVMGen::initLLVM();
    lgsConfigs.devMode = true;
    lgsConfigs.printIR = false;
    lgsConfigs.writeIRFiles = false;
    return doctest::Context(argc, argv).run();
}
