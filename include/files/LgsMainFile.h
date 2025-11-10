#pragma once
#include "LgsFile.h"
#include "funcs/LgsFunc.h"
#include "types/LgsEnum.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/LgsSubType.h"

class LgsMainFunc;
class LgsEnum;

class LgsMainFile final : public LgsFile {
public:
    std::vector<LgsEnum*> enums;
    std::vector<LgsObject*> objects;
    std::vector<LgsInterface*> interfaces;
    std::map<std::string, LgsFunc*> funcs;
    std::vector<LgsSubType*> subtypes;

    explicit LgsMainFile(const size_t fileID, const fs::path& path) : LgsFile(fileID, path) {}
    size_t hashFile() override;
    LgsFunc* getMainFunc();
    ~LgsMainFile() override;
};
