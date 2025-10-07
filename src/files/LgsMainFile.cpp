#include "files/LgsMainFile.h"
#include "funcs/LgsFunc.h"
#include "types/LgsEnum.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/LgsSubType.h"
#include "utils/LgsUtils.h"

void LgsMainFile::parseAsJSON(std::stringstream& json) {
    openJsonObject(json);

    openJsonKeyArray(json, "funcs");
    bool first = true;
    for (const auto& [funcName, func] : funcs) {
        if (!first) json << ',';
        first = false;
        func->parseAsJSON(json);
    }
    closeJsonArray(json, true);

    openJsonKeyArray(json, "object");
    first = true;
    for (const auto obj : objects) {
        if (!first) json << ',';
        first = false;
        obj->parseAsJSON(json);
    }
    closeJsonArray(json, true);

    openJsonKeyArray(json, "interfaces");
    first = true;
    for (const auto interface : interfaces) {
        if (!first) json << ',';
        first = false;
        interface->parseAsJSON(json);
    }
    closeJsonArray(json, true);

    openJsonKeyArray(json, "enums");
    first = true;
    for (const auto enum_ : enums) {
        if (!first) json << ',';
        first = false;
        enum_->parseAsJSON(json);
    }
    closeJsonArray(json);

    openJsonKeyArray(json, "subtypes");
    first = true;
    for (const auto subtype : subtypes) {
        if (!first) json << ',';
        first = false;
        subtype->parseAsJSON(json);
    }
    closeJsonArray(json);

    closeJsonObject(json);
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
