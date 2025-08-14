#pragma once
#include "types/LgsFuncType.h"
#include "funcs/LgsFunc.h"

class LgsBuiltinFunc : public LgsFunc {
public:
    LgsBuiltinFunc(const std::string& name, LgsType* rt): LgsFunc(name, rt) {}
    LgsBuiltinFunc(const std::string& name, LgsType* rt, const std::string& parentName, const std::vector<LgsType*>& paramsTypes, const bool isPublic = false, const bool isVariadic = false): LgsFunc(name, rt) {
        funcType->isPublic = isPublic;
        funcType->isVariadic = isVariadic;
        init(parentName, paramsTypes);
    }

    void init(const std::string& parentName, const std::vector<LgsType*>& paramsTypes) const {
        if (parentName != "") {
            funcType->parentName = parentName;
            funcType->isMethod = true;
        }
        for (const auto paramsType : paramsTypes) {
            funcType->params.emplace_back(paramsType);
        }
    }
};
