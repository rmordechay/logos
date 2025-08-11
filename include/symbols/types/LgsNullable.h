#pragma once
#include "LgsType.h"

class LgsNullable final : public LgsType {
public:
    LgsType* baseType;

    explicit LgsNullable(LgsType* baseType) : baseType(baseType) {}
    Type* getIRType(LgsCodeGen* codeGen) override;
    string getName() override;
    LgsExpr* getZeroValue() override;
    string prettyName() override;
    bool equals(LgsType* other) override;
    size_t getSizeBytes() override;
    ~LgsNullable() override;
};
