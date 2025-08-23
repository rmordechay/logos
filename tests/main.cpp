#include "../include/codegen/LgsCodeGen.h"
#include <../include/external/doctest.h>

int main(const int argc, char** argv) {
    LgsCodeGen::initLLVM();
    return doctest::Context(argc, argv).run();
}