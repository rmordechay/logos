#pragma once
#include "LgsFile.h"
#include "data/LgsDefinitions.h"
#include "funcs/LgsFunc.h"
#include "types/LgsEnum.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/LgsSubType.h"
#include "utils/LgsUtils.h"

class LgsMainFunc;
class LgsEnum;

class LgsMainFile final : public LgsFile {
public:
    std::vector<LgsEnum*> enums;
    std::vector<LgsObject*> objects;
    std::map<std::string, LgsFunc*> funcs;
    std::vector<LgsInterface*> interfaces;
    std::vector<LgsSubType*> subtypes;

    explicit LgsMainFile(const size_t fileID, const fs::path& path) : LgsFile(fileID, path) {}
    size_t hashFile() override;
    LgsFunc* getMainFunc();
    ~LgsMainFile() override;
};