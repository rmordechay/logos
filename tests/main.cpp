#include "codegen/LgsLLVM.h"
#include "external/doctest.h"

int main(const int argc, char** argv) {
    LgsLLVM::initLLVM();
    return doctest::Context(argc, argv).run();
}