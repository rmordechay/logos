#pragma once
#include "LgsSymbolTable.h"
#include "data/LgsErrors.h"
#include "codegen/LgsLLVMGen.h"
#include "data/LgsDefinitions.h"

namespace fs = std::filesystem;
class LgsStrConst;
class LgsApp;

class LgsFile {
public:
    size_t id = 0;
    fs::path path;
    LgsLocation location;
    LgsLLVMGen llvmCodeGen;
    LgsSymbolTable symbolTable;

    explicit LgsFile(const size_t fileID, const fs::path& path) : id(fileID), path(path) {}
    bool isMain() const;
    virtual size_t hashFile() = 0;
    virtual ~LgsFile() = default;
};

inline bool LgsFile::isMain() const {
    return path.filename() == LGS_MAIN_FILE;
}
