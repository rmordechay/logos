#pragma once
#include "LgsFile.h"
#include "data/LgsDefinitions.h"

class LgsGroup;
class LgsMainFunc;
class LgsEnum;

class LgsMainFile final : public LgsFile {
public:
    std::vector<char*> appArgs;
    std::vector<LgsEnum*> enums;
    std::vector<LgsObject*> objects;
    std::map<std::string, LgsFunc*> funcs;
    std::vector<LgsInterface*> interfaces;
    std::vector<LgsGroup*> groups;
    std::vector<LgsSubType*> subtypes;

    explicit LgsMainFile(const size_t fileID, const fs::path& path) : LgsFile(fileID, LGS_MAIN_FILE_NAME, path) {}
    void format() override;
    json::value asJSON() override;
    ~LgsMainFile() override;
};
