#pragma once
#include "LgsFile.h"

class LgsEnv;
class LgsVarDec;

class LgsEnvFile final : public LgsFile {
public:
    vector<LgsVarDec*> varDecs;
    LgsEnvFile(const string& fileName, path& path, const vector<LgsVarDec*>& varDecs) : LgsFile(fileName, path), varDecs(varDecs) {}
    ~LgsEnvFile() override = default;
};



