#include "test/LgsTest.h"
#include "funcs/LgsFunc.h"

json::value LgsTest::asJSON() {
    assert(0);
}

LgsTest::~LgsTest() {
    if (func) {
        delete func;
        func = nullptr;
    }
}
