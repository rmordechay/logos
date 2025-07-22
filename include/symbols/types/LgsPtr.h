#pragma once
#include "LgsType.h"
#include "logos/LgsModule.h"

class LgsPtr final : public LgsType {
public:
    static constexpr auto name = "Ptr";
    LgsType* baseType;

    explicit LgsPtr(LgsType* baseType) : baseType(baseType) {}
    string getIRName() override;
    string prettyName() const override;
    Type* getIRType(LgsModule* module) override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    ~LgsPtr() override = default;
};
