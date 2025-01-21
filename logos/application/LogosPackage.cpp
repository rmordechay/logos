#include "LogosPackage.h"

LogosPackage::~LogosPackage() {
    for (const auto file : files) {
        delete file;
    }
    for (const auto package : packages) {
        delete package;
    }
}

