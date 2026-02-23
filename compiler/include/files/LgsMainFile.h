#pragma once
#include <filesystem>
#include <map>
#include <string>
#include <vector>

#include "LgsFile.h"
#include "funcs/LgsFunc.h"
#include "types/LgsEnum.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/LgsSubType.h"
#include "codegen/LgsCodeGen.h"

class LgsMainFunc;
class LgsEnum;
class LgsFunc;
class LgsIOPair;
class LgsInterface;
class LgsObject;
class LgsSubType;
class LgsVarDec;

class LgsMainFile final : public LgsFile {
public:
    std::map<std::string, LgsFunc*> funcs;
    std::vector<LgsVarDec*> varDecs;
    std::vector<LgsIOPair*> ioPairs;
    std::vector<LgsSubType*> subtypes;
    std::vector<LgsObject*> objects;
    std::vector<LgsInterface*> interfaces;
    std::vector<LgsEnum*> enums;

    explicit LgsMainFile(const fs::path& path) : LgsFile(path, CG_MODE_SRC) {}
    size_t hashFile() override;
    ~LgsMainFile() override;
};
