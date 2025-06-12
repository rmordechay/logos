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
    int returnParamIndex = -1;
    FunctionType* IRType = nullptr;

    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    string prettyName() const override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) override;
    LgsType* clone() override;
    ~LgsFuncType() override = default;
};
