#pragma once

#include "LgsFile.h"
#include "data/LgsDefinitions.h"

class LgsGroup;
class LgsMainFunc;
class LgsEnum;

class LgsMainFile final : public LgsFile {
public:
    vector<LgsEnum*> enums;
    vector<LgsObject*> objects;
    vector<LgsInterface*> interfaces;
    vector<LgsGroup*> groups;
    map<string, LgsFunc*> funcs;

    explicit LgsMainFile(const string& path) : LgsFile(LOGOS_MAIN_FILE_NAME, path) {}
    void format() override;
    Module* generateIR(LgsApp& project) override;
    ~LgsMainFile() override;
};


