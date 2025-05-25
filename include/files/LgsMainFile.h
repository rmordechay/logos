#ifndef LOGOSMAINFILE_H
#define LOGOSMAINFILE_H
#include "data/LgsDefinitions.h"
#include "LgsFile.h"
#include "funcs/LgsFuncImpl.h"
#include "types/LgsEnum.h"
#include "types/LgsObject.h"

class LgsEnum;

class LgsMainFile final : public LgsFile {
public:
    vector<LgsEnum*> enums;
    vector<LgsObject*> objects;
    vector<LgsInterface*> interfaces;
    map<string, LgsFuncImpl*> funcs;
    LgsMainFunc* mainFunc = nullptr;

    explicit LgsMainFile(const string& path) : LgsFile(LOGOS_MAIN_FILE_NAME, path) {}
    void format() override;
    json asJSON() override;
    ~LgsMainFile() override;
};

inline void LgsMainFile::format() {
    string indentStr = "";
    ofstream outFile(absPath, ios::trunc);
    outFile << mainFunc->format(indentStr);
}

inline json LgsMainFile::asJSON() {
    json tree;
    tree["name"] = name;
    tree["path"] = absPath;
    json jsonFuncs = {};
    for (const auto [_, func] : funcs) {
        jsonFuncs.emplace_back(func->asJSON());
    }
    jsonFuncs.emplace_back(mainFunc->asJSON());
    tree["funcs"] = jsonFuncs;
    if (!enums.empty()) {
        json jsonEnums = {};
        for (const auto& lgsEnum : enums) {
            jsonEnums.emplace_back(lgsEnum->asJSON());
        }
        tree["enums"] = jsonEnums;
    }
    if (!objects.empty()) {
        json jsonObjects = {};
        for (const auto& obj : objects) {
            jsonObjects.emplace_back(obj->asJSON());
        }
        tree["objects"] = jsonObjects;
    }
    return tree;
}

inline LgsMainFile::~LgsMainFile() {
    delete mainFunc;
    for (const auto& func : funcs) {
        delete func.second;
    }
}


#endif //LOGOSMAINFILE_H
