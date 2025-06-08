#pragma once
#include "LgsFile.h"

class LgsEnv;
class LgsVarDec;

class LgsEnvFile final : public LgsFile {
public:
    vector<LgsVarDec*> varDecs;

    LgsEnvFile(const filesystem::path& path, const vector<LgsVarDec*>& varDecs) : LgsFile(path.filename(), path), varDecs(varDecs) {}
};


