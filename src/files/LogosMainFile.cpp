#include "files/LogosMainFile.h"

#include "funcs/LogosUserFunc.h"


LogosMainFile::~LogosMainFile() {
    delete mainFunc;
    for (const auto& func : funcs) {
        delete func;
    }
}
