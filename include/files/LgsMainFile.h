#ifndef LOGOSMAINFILE_H
#define LOGOSMAINFILE_H
#include "LgsDefinitions.h"
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
    map<string, vector<LgsFuncImpl*>> funcs;
    LgsMainFunc* mainFunc = nullptr;

    explicit LgsMainFile(const string& path) : LgsFile(LOGOS_MAIN_FILE_NAME, path) {}
    void format() override;
    json asJSON() override;
    vector<LgsFuncImpl*> getAllFuncs();
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
    for (const auto& func : getAllFuncs()) {
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

inline vector<LgsFuncImpl*> LgsMainFile::getAllFuncs() {
    vector<LgsFuncImpl*> allFuncs;
    for (const auto& [_, overloads] : funcs) {
        for (const auto& func : overloads) {
            allFuncs.emplace_back(func);
        }
    }
    return allFuncs;
}

inline LgsMainFile::~LgsMainFile() {
    delete mainFunc;
    for (const auto& func : getAllFuncs()) {
        delete func;
    }
}


#endif //LOGOSMAINFILE_H
