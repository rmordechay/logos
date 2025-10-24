#pragma once
#include "LgsFile.h"
#include "funcs/LgsFunc.h"


class LgsTestFile final : public LgsFile {
public:
    std::string name;
    std::vector<LgsFunc*> tests;
    std::vector<LgsFunc*> funcs;
    std::vector<LgsVarDec*> varDecs;

    LgsTestFile(const size_t fileID, const fs::path& path) : LgsFile(fileID, path) {}
    size_t hashFile() override;
    ~LgsTestFile() override;
};
