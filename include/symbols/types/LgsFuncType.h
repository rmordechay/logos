#pragma once
#include "LgsType.h"
#include "funcs/LgsParam.h"

class LgsFuncType final : public LgsType {
public:
    string name;
    string IRName;
    string parentName;
    LgsType* rt = nullptr;
    vector<LgsParam> params;
    bool isMethod = false;
    bool isPublic = false;
    bool isVirtual = false;
    bool isVariadic = false;
    bool isAnonymous = false;
    bool isSwapReturn = false;
    bool isStaticMethod = false;
    bool hasDefaults = false;
    int returnParamIndex = -1;
    FunctionType* IRType = nullptr;

    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    string prettyName() const override;
    bool equals(LgsType* other) override;
    ~LgsFuncType() override;
};
