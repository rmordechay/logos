#pragma once
#include "LgsFile.h"
#include "data/LgsDefinitions.h"

class LgsMainFunc;
class LgsEnum;

class LgsMainFile final : public LgsFile {
public:
    std::vector<char*> appArgs;
    std::vector<LgsEnum*> enums;
    std::vector<LgsObject*> objects;
    std::map<std::string, LgsFunc*> funcs;
    std::vector<LgsInterface*> interfaces;
    std::vector<LgsSubType*> subtypes;

    explicit LgsMainFile(const size_t fileID, const fs::path& path) : LgsFile(fileID, path) {}
    void format() override;
    void parseAsJSON(std::stringstream& json) override;
    ~LgsMainFile() override;
};
