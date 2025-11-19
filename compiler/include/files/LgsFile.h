#pragma once
#include "LgsSymbolTable.h"
#include "errors/LgsErrors.h"
#include "codegen/LgsLLVMGen.h"
#include "LgsDefinitions.h"

namespace fs = std::filesystem;
class LgsStrConst;
class LgsApp;

class LgsFile {
public:
    fs::path path;
    LgsLLVMGen cg;
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
