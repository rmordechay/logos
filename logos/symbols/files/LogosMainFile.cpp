#include "LogosMainFile.h"


LogosMainFile::~LogosMainFile() {
    delete mainFunc;
    for (const auto func : funcs) {
        delete func;
    }
}
