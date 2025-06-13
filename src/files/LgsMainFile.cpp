#include "files/LgsMainFile.h"

#include "funcs/LgsFunc.h"
#include "logos/LgsProject.h"
#include "types/LgsEnum.h"
#include "types/LgsObject.h"
#include "utils/LgsUtils.h"

Module* LgsMainFile::generateIR(LgsProject& project) {
    LgsRuntime runtime;
    runtime.module = createIRModule(LOGOS_MAIN_FILE_NAME, context);
    for (const auto [_, func] : funcs) {
        func->generateIR(&runtime);
    }
    for (const auto object : objects) {
        for (const auto& [_, method] : object->methods) {
            method->generateIR(&runtime);
        }
    }
    return runtime.module;
}

void LgsMainFile::format() {
    string indentStr = "";
    // ofstream outFile(absPath, ios::trunc);
}

json LgsMainFile::asJSON() {
    json tree;
    tree["name"] = name;
    tree["path"] = absPath;
    json jsonFuncs = {};
    for (const auto [_, func] : funcs) {
        jsonFuncs.emplace_back(func->asJSON());
    }
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

LgsMainFile::~LgsMainFile() {
    for (const auto& func : funcs) {
        delete func.second;
    }
}
