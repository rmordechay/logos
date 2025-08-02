#pragma once
#include "types/LgsFuncType.h"
#include "funcs/LgsFunc.h"

class LgsBuiltinFunc : public LgsFunc {
public:
    LgsBuiltinFunc(const string& name, LgsType* rt, const string& parentName, const vector<LgsType*>& paramsTypes, const bool isPublic = false, const bool isVariadic = false): LgsFunc(name, rt) {
        isBuiltin = true;
        funcType->isPublic = isPublic;
        funcType->isVariadic = isVariadic;
        if (parentName != "") {
            funcType->parentName = parentName;
            funcType->isMethod = true;
        }
        for (const auto paramsType : paramsTypes) {
            funcType->params.emplace_back(paramsType);
        }
    }
};
