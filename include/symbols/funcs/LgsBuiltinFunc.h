#pragma once
#include "funcs/LgsFunc.h"

class LgsBuiltinFunc : public LgsFunc {
public:
    LgsBuiltinFunc(const string& name, LgsType* rt, const string& parentName, const vector<LgsType*>& paramsTypes, const uint16_t flags = 0): LgsFunc(name, rt) {
        funcType->isBuiltin = true;
        funcType->flags = flags;
        if (parentName != "") {
            funcType->parentName = parentName;
            funcType->setFlag(METHOD);
        }
        for (const auto paramsType : paramsTypes) {
            funcType->params.emplace_back(LgsParam(paramsType));
        }
    }
    ~LgsBuiltinFunc() override = default;
};
