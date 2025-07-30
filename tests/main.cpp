
#include "logos/LgsCodeGen.h"
#include <doctest.h>

int main(const int argc, char** argv) {
    LgsCodeGen::initLLVM();
    return doctest::Context(argc, argv).run();
}