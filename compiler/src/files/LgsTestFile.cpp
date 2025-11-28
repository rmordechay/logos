#include "files/LgsTestFile.h"

#include "funcs/LgsFunc.h"

size_t LgsTestFile::hashFile() {
    assert(0);
}

LgsTestFile::~LgsTestFile() {
    for (const auto& test : tests) {
        delete test;
    }
    tests.clear();
    for (const auto& func : funcs) {
        delete func;
    }
    funcs.clear();
}
