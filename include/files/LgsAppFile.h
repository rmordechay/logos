#pragma once

#include "LgsFile.h"
#include "data/LgsDefinitions.h"

class LgsType;
class LgsVarDec;

struct RequireEnvVar {
    string name;
    LgsType* type;
};

class LgsAppFile final : public LgsFile {
public:
    vector<LgsVarDec*> varDecs;
    vector<RequireEnvVar> requireEnvVars;

    explicit LgsAppFile(const path& path, const vector<LgsVarDec*>& varDecs) : LgsFile(LOGOS_APP_FILE_NAME, path), varDecs(varDecs) {}
    ~LgsAppFile() override = default;
};


