#pragma once
#include "funcs/LgsFunc.h"

class LgsBuiltinFunc : public LgsFunc {
public:
    LgsBuiltinFunc(const string& name, LgsType* rt, const string& parentName, const vector<LgsParam>& params = {}): LgsFunc(name, rt, params) {
        funcType.isBuiltin = true;
        if (parentName != "") {
            funcType.parentName = parentName;
            funcType.isMethod = true;
        }
    }
    LgsBuiltinFunc(const string& name, LgsType* rt, const string& parentName, const vector<LgsType*>& paramsTypes, bool isPublic = false, bool isVariadic = false): LgsBuiltinFunc(name, rt, parentName) {
        funcType.isPublic = isPublic;
        funcType.isVariadic = isVariadic;
        for (const auto paramsType : paramsTypes) {
            funcType.params.emplace_back(LgsParam(paramsType));
        }
    }
    ~LgsBuiltinFunc() override = default;
};
