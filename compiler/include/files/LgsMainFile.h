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
    std::vector<LgsVarDec*> varDecs;
    std::map<std::string, LgsFunc*> funcs;
    std::vector<LgsObject*> objects;
    std::vector<LgsInterface*> interfaces;
    std::vector<LgsSubType*> subtypes;
    std::vector<LgsEnum*> enums;

    explicit LgsMainFile(const fs::path& path) : LgsFile(path, CG_MODE_SRC_CODE) {}
    size_t hashFile() override;
    LgsFunc* getMainFunc();
    ~LgsMainFile() override;
};
