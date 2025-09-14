#include "files/LgsTestFile.h"
#include "funcs/LgsFunc.h"
#include "test/LgsTest.h"

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
