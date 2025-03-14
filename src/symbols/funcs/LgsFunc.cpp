#include "funcs/LgsFunc.h"

#include <LgsDefinitions.h>

LgsFunc::~LgsFunc() {
    for (const auto param : params) {
        delete param;
    }
    delete stmtBlock;
}
