#pragma once
#include "LgsType.h"
#include "logos/LgsModule.h"

class LgsNullable final : public LgsType {
public:
    LgsType* baseType;

    explicit LgsNullable(LgsType* baseType) : baseType(baseType) {}
    Type* getIRType(LgsModule* module) override;
    string getName() override;
    LgsExpr* getZeroValue() override;
    string prettyName() override;
    bool equals(LgsType* other) override;
    ~LgsNullable() override = default;
};
