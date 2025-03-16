#include "funcs/LgsFunc.h"

#include <LgsConfig.h>

LgsFunc::~LgsFunc() {
    for (const auto param : params) {
        delete param;
    }
    delete stmtBlock;
}
