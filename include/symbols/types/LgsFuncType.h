#pragma once
#include "LgsType.h"
#include "funcs/LgsParam.h"


class LgsParam;

class LgsFuncType final : public LgsType {
public:
    string name;
    string IRName;
    string parentName;
    LgsType* rt = nullptr;
    vector<LgsParam> params;
    bool isMethod = false;
    bool isStatic = false;
    bool isPublic = false;
    bool isVirtual = false;
    bool isVariadic = false;
    bool isAnonymous = false;
    bool isRvBig = false;
    bool swapReturn = false;
    bool hasDefaultParams = false;
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


