#pragma once
#include "LgsDefinitions.h"
#include "codegen/LgsCgModule.h"
#include "LgsSymbolTable.h"
#include "errors/LgsErrHandler.h"

namespace fs = std::filesystem;
class LgsStrConst;
class LgsApp;

class LgsFile {
public:
    fs::path path;
    LgsCgModule cg;
    LgsLocation location;
    LgsSymbolTable symbolTable;

    explicit LgsFile(const fs::path& path) : path(path) {}
    bool isMain() const;
    virtual size_t hashFile() = 0;
    virtual ~LgsFile() = default;
};

inline bool LgsFile::isMain() const {
    return path.filename() == LGS_MAIN_FILE;
}
