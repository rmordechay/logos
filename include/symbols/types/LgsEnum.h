#pragma once
#include "LgsType.h"
#include "data/LgsDefinitions.h"
#include "exprs/unary/LgsEnumField.h"
#include "stmts/LgsField.h"

class LgsEnumField;

class LgsEnum final : public LgsType {
public:
    string name;

    explicit LgsEnum(const string& enumName) : name(enumName) {
        fields[LOGOS_DEFAULT_ENUM] = new LgsField(LOGOS_DEFAULT_ENUM, &name, this, new LgsDefaultEnumField(this));
    }
    Type* getIRType() override;
    string getIRName() override;
    string pName() const override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
    ~LgsEnum() override = default;
};


