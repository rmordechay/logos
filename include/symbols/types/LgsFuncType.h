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
    bool isStatic = false;
    bool isOptional = false;
    bool hasDefaults = false;
    int returnParamIndex = -1;
    FunctionType* IRType = nullptr;
    string* implementsName = nullptr;

    Type* getIRType(LgsCodeGen* codeGen) override;
    string getName() override;
    LgsExpr* getZeroValue() override;
    string prettyName() override;
    bool equals(LgsType* other) override;
    string getStrFormatPart() const override;
    ~LgsFuncType() override;
};
