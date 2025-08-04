#pragma once
#include "types/LgsFuncType.h"
#include "funcs/LgsFunc.h"

class LgsBuiltinFunc : public LgsFunc {
public:
    LgsBuiltinFunc(const string& name, LgsType* rt): LgsFunc(name, rt) {}
    LgsBuiltinFunc(const string& name, LgsType* rt, const string& parentName, const vector<LgsType*>& paramsTypes, const bool isPublic = false, const bool isVariadic = false): LgsFunc(name, rt) {
        funcType->isPublic = isPublic;
        funcType->isVariadic = isVariadic;
        init(parentName, paramsTypes);
    }

    void init(const string& parentName, const vector<LgsType*>& paramsTypes) const {
        if (parentName != "") {
            funcType->parentName = parentName;
            funcType->isMethod = true;
        }
        for (const auto paramsType : paramsTypes) {
            funcType->params.emplace_back(paramsType);
        }
    }
};
