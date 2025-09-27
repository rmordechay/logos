#pragma once
#include "LgsType.h"

class LgsEnum final : public LgsType {
public:
    std::string name;

    explicit LgsEnum(const std::string& enumName) : name(enumName) {}
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    json::value asJsonStr() override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    size_t getSizeBytes() override;
    ~LgsEnum() override = default;
};


