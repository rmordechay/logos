#include "funcs/LogosFunc.h"

#include <LogosDefinitions.h>

LogosFunc::~LogosFunc() {
    for (const auto param : params) {
        delete param;
    }
    delete stmtBlock;
}
