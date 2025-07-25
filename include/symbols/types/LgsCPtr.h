#pragma once
#include "LgsType.h"
#include "logos/LgsModule.h"

class LgsCPtr final : public LgsType {
public:
    static constexpr auto name = "Ptr";
    LgsType* baseType;

    explicit LgsCPtr(LgsType* baseType) : baseType(baseType) {}
    string getName() override;
    string prettyName() override;
    Type* getIRType(LgsModule* module) override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    ~LgsCPtr() override = default;
};
