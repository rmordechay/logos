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
    ~LgsTestFile() override;
};


inline LgsTestFile::~LgsTestFile() {
    for (const auto& test : tests) {
        delete test;
    }
    tests.clear();
    for (const auto& func : funcs) {
        delete func;
    }
    funcs.clear();
}