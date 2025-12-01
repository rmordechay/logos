#pragma once
#include "LgsFile.h"


class LgsTestFile final : public LgsFile {
public:
    std::string name;
    std::vector<LgsFunc*> tests;
    std::vector<LgsFunc*> funcs;
    std::vector<LgsVarDec*> varDecs;

    LgsTestFile(const fs::path& path) : LgsFile(path) {}
    size_t hashFile() override;
    ~LgsTestFile() override;
};
