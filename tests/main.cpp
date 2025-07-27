#include "utils/LgsIRUtils.h"
#include "utils/LgsUtils.h"

#include <doctest.h>

int main(const int argc, char** argv) {
    initLLVM();
    return doctest::Context(argc, argv).run();
}