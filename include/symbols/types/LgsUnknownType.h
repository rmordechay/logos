#pragma once
#include "LgsType.h"

class LgsUnknownType final : public LgsType {
public:
    string name;

    explicit LgsUnknownType(const string& name = "") : name(name) {}
    Type* getIRType(LgsModule* module) override;
    string getName() override;
    string prettyName() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    ~LgsUnknownType() override = default;
};
