#include "files/LgsMainFile.h"
#include "funcs/LgsFunc.h"
#include "types/LgsEnum.h"
#include "types/LgsGroup.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"

json::value LgsMainFile::asJSON() {
    json::object obj;
    json::array jsonEnums;
    for (const auto& enum_ : enums) {
        jsonEnums.emplace_back(enum_->asJsonStr());
    }
    obj["enums"] = jsonEnums;
    json::array jsonObjects;
    for (const auto& object : objects) {
        jsonObjects.emplace_back(object->asJsonStr());
    }
    obj["objects"] = jsonObjects;
    json::array jsonFuncs;
    for (const auto& [_, func] : funcs) {
        jsonFuncs.emplace_back(func->asJsonStr());
    }
    obj["funcs"] = jsonFuncs;
    json::array jsonInterfaces;
    for (const auto& interface : interfaces) {
        jsonInterfaces.emplace_back(interface->asJsonStr());
    }
    obj["interfaces"] = jsonInterfaces;
    json::array jsonGroups;
    for (const auto& group : groups) {
        jsonGroups.emplace_back(group->asJsonStr());
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
