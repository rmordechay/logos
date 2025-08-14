#pragma once

#include "LgsFile.h"
#include "configs/LgsDefinitions.h"

class LgsType;
class LgsVarDec;

struct RequireEnvVar {
    std::string name;
    LgsType* type;
};

class LgsAppFile final : public LgsFile {
public:
    std::vector<LgsVarDec*> varDecs;
    std::vector<RequireEnvVar> requireEnvVars;

    explicit LgsAppFile(const fs::path& path, const std::vector<LgsVarDec*>& varDecs) : LgsFile(LGS_APP_FILE_NAME, path), varDecs(varDecs) {}
    ~LgsAppFile() override = default;
};


