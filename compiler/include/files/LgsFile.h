#pragma once
#include "codegen/LgsCgFile.h"

namespace fs = std::filesystem;
class LgsStrConst;
class LgsApp;

class LgsFile {
public:
    fs::path path;
    LgsCgFile cgFile;
    LgsSymbolTable symbolTable;

    explicit LgsFile(const fs::path& path, const LgsCodeGenMode mode) : path(path), cgFile(mode) {}
    bool isMain() const;
    virtual size_t hashFile();
    void setupCodeGen(LgsAppConfigs& appConfigs_);
    virtual ~LgsFile() = default;
};
