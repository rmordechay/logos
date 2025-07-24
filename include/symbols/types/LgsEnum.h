#pragma once
#include "LgsType.h"

class LgsEnum final : public LgsType {
public:
    string name;

    explicit LgsEnum(const string& enumName) : name(enumName) {}
    Type* getIRType(LgsModule* module) override;
    string getName() override;
    string prettyName() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    string getStrFormatPart() const override;
    ~LgsEnum() override = default;
};


