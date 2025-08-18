#include "files/LgsMainFile.h"
#include "funcs/LgsFunc.h"
#include "types/LgsEnum.h"
#include "types/LgsGroup.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"

void LgsMainFile::generateIR() {
    for (const auto object : objects) {
        object->getIRType(&codeGen);
        for (const auto& [_, method] : object->methods) {
            method->generateIR(&codeGen);
        }
    }
    for (const auto [_, func] : funcs) {
        func->generateIR(&codeGen);
    }
}

json::object LgsMainFile::asJSON() {
    json::object obj;
    json::array jsonEnums;
    for (const auto& enum_ : enums) {
        jsonEnums.emplace_back(enum_->asJSON());
    }
    obj["enums"] = jsonEnums;
    json::array jsonObjects;
    for (const auto& object : objects) {
        jsonObjects.emplace_back(object->asJSON());
    }
    obj["objects"] = jsonObjects;
    json::array jsonFuncs;
    for (const auto& [_, func] : funcs) {
        jsonFuncs.emplace_back(func->asJSON());
    }
    obj["funcs"] = jsonFuncs;
    json::array jsonInterfaces;
    for (const auto& interface : interfaces) {
        jsonInterfaces.emplace_back(interface->asJSON());
    }
    obj["interfaces"] = jsonInterfaces;
    json::array jsonGroups;
    for (const auto& group : groups) {
        jsonGroups.emplace_back(group->asJSON());
    }
    obj["groups"] = jsonGroups;
    return obj;
}

void LgsMainFile::format() {
    std::string indentStr = "";
}

LgsMainFile::~LgsMainFile() {
    for (const auto& [_, func] : funcs) {
        delete func;
    }
    for (const auto& object : objects) {
        delete object;
    }
    for (const auto lgsEnum : enums) {
        delete lgsEnum;
    }
}
