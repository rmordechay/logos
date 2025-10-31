#include "codegen/LgsLLVMGen.h"
#include "data/LgsConfigs.h"
#include "external/doctest.h"

int main(const int argc, char** argv) {
    LgsLLVMGen::initLLVM();
    lgsConfigs.devMode = false;
    lgsConfigs.writeIRFiles = false;
    return doctest::Context(argc, argv).run();
}
