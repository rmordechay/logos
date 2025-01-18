#include "LogosRootPackage.h"

LogosRootPackage::~LogosRootPackage() {
    delete mainFile;
    for (const auto file : files) {
        delete file;
    }
    for (const auto package : packages) {
        delete package;
    }
}
