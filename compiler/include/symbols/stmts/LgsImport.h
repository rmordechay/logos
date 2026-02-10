#pragma once
#include "errors/LgsErrHandler.h"

enum LgsImportType {
    LGS_IMPORT,
    LGS_C_IMPORT,
};

class LgsImport final {
public:
    LgsImportType type;
    std::string importPath;
    LgsLocation location;

    LgsImport(LgsImportType type, const std::string& importPath) : type(type), importPath(importPath) {}
};
