#pragma once
#include "LgsType.h"
#include "data/LgsDefinitions.h"
#include "exprs/unary/LgsEnumField.h"
#include "stmts/LgsField.h"

class LgsEnumField;

class LgsEnum final : public LgsType {
public:
    string name;

    explicit LgsEnum(const string& enumName) : name(enumName) {}
    Type* getIRType(LLVMContext& context) override;
    string getIRName() override;
    string prettyName() const override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    string getStrFormatPart() const override;
    ~LgsEnum() override = default;
};


