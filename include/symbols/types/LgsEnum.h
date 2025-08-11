#pragma once
#include "LgsType.h"

class LgsEnum final : public LgsType {
public:
    string name;

    explicit LgsEnum(const string& enumName) : name(enumName) {}
    Type* getIRType(LgsCodeGen* codeGen) override;
    string getName() override;
    string prettyName() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    string strFormatPart() const override;
    size_t getSizeBytes() override;
    ~LgsEnum() override = default;
};


