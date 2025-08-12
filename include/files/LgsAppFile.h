#pragma once

#include "LgsFile.h"
#include "configs/LgsDefinitions.h"

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

    explicit LgsAppFile(const fs::path& path, const vector<LgsVarDec*>& varDecs) : LgsFile(LGS_APP_FILE_NAME, path), varDecs(varDecs) {}
    ~LgsAppFile() override = default;
};


