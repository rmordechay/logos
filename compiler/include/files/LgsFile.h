#pragma once
#include <filesystem>

#include "codegen/LgsCgFile.h"
#include "LgsSymbolTable.h"
#include "codegen/LgsCodeGen.h"

class LgsAppFile;
class LgsEnvFile;
class LgsInterfaceFile;
class LgsMainFile;
class LgsObjectFile;
class LgsTestFile;
struct LgsAppConfigs;

namespace fs = std::filesystem;
class LgsStrConst;
class LgsApp;

class LgsFile {
public:
    fs::path path;
    LgsCgFile cgFile;
    LgsSymbolTable symbolTable;

    explicit LgsFile(const fs::path& path, const LgsCodeGenMode mode) : path(path), cgFile(mode) {}
    virtual size_t hashFile();
    void setupCodeGen(LgsAppConfigs& appConfigs);
    LgsMainFile* asMainFile();
    LgsObjectFile* asObjectFile();
    LgsInterfaceFile* asInterfaceFile();
    LgsTestFile* asTestFile();
    LgsEnvFile* asEnvFile();
    LgsAppFile* asAppFile();
    virtual ~LgsFile() = default;
};
