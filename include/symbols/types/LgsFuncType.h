#pragma once
#include "LgsType.h"
#include "funcs/LgsParam.h"

class LgsFuncType final : public LgsType {
public:
    std::string name;
    std::string IRName;
    std::string parentName;
    LgsType* rt = nullptr;
    std::vector<LgsParam> params;
    bool isMethod = false;
    bool isPublic = false;
    bool isVirtual = false;
    bool isVariadic = false;
    bool isStatic = true;
    bool isOptional = false;
    bool isTerminator = false;
    bool hasDefaults = false;
    FunctionType* IRType = nullptr;

    Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    std::string prettyName() override;
    size_t getSizeBytes() override;
    bool equals(LgsType* other) override;
    std::string strFormatPart() const override;
    ~LgsFuncType() override;
};
