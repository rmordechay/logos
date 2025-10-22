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
    std::vector<char*> appArgs;
    std::vector<LgsEnum*> enums;
    std::vector<LgsObject*> objects;
    std::map<std::string, LgsFunc*> funcs;
    std::vector<LgsInterface*> interfaces;
    std::vector<LgsSubType*> subtypes;

    explicit LgsMainFile(const size_t fileID, const fs::path& path) : LgsFile(fileID, path) {}
    inline size_t hashFile() override;
    ~LgsMainFile() override;
};

inline size_t LgsMainFile::hashFile() {
    size_t hash = 0;
    hashString(hash, LGS_MAIN_FILE_NAME);
    for (const auto& [funcName, func] : funcs) {
        func->hashValue(hash);
    }
    for (const auto obj : objects) {
        obj->hashValue(hash);
    }
    for (const auto interface : interfaces) {
        interface->hashValue(hash);
    }
    for (const auto enum_ : enums) {
        enum_->hashValue(hash);
    }
    for (const auto subtype : subtypes) {
        subtype->hashValue(hash);
    }
    return hash;
}

inline LgsMainFile::~LgsMainFile() {
    for (const auto& [_, func] : funcs) {
        delete func;
    }
    funcs.clear();
    for (const auto& object : objects) {
        freeType(object);
    }
    objects.clear();
    for (const auto lgsEnum : enums) {
        freeType(lgsEnum);
    }
    enums.clear();
}
