#include "codegen/LgsLLVMGen.h"
#include "external/doctest.h"

int main(const int argc, char** argv) {
    LgsLLVMGen::initLLVM();
    return doctest::Context(argc, argv).run();
}