#pragma once
#include "LgsFile.h"
#include "configs/LgsDefinitions.h"

class LgsGroup;
class LgsMainFunc;
class LgsEnum;

class LgsMainFile final : public LgsFile {
public:
    std::vector<LgsEnum*> enums;
    std::vector<LgsObject*> objects;
    std::map<std::string, LgsFunc*> funcs;
    std::vector<LgsInterface*> interfaces;
    std::vector<LgsTable*> tables;
    std::vector<LgsGroup*> groups;

    explicit LgsMainFile(const size_t fileID, const fs::path& path) : LgsFile(fileID, LGS_MAIN_FILE_NAME, path) {}
    void format() override;
    void generateIR() override;
    json::value asJSON() override;
    ~LgsMainFile() override;
};
