#pragma once
#include "LgsFile.h"

class LgsTest;

class LgsTestFile final : public LgsFile {
public:
    std::string name;
    std::vector<LgsTest*> tests;
    std::vector<LgsFunc*> funcs;

    LgsTestFile(const size_t fileID, const std::string& name, const fs::path& path) : LgsFile(fileID, name, path) {}
    ~LgsTestFile() override;
};
