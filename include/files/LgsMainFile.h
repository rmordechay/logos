#pragma once

#include "LgsFile.h"
#include "configs/LgsDefinitions.h"

class LgsGroup;
class LgsMainFunc;
class LgsEnum;

class LgsMainFile final : public LgsFile {
public:
    vector<LgsEnum*> enums;
    vector<LgsObject*> objects;
    map<string, LgsFunc*> funcs;
    vector<LgsInterface*> interfaces;
    vector<LgsGroup*> groups;

    explicit LgsMainFile(const fs::path& path) : LgsFile(LGS_MAIN_FILE_NAME, path) {}
    void format() override;
    void generateIR() override;
    ~LgsMainFile() override;
};
