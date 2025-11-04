#pragma once
#include "LgsType.h"
#include <string>

class LgsEnum final : public LgsType {
public:
    std::string name;
    bool isRoot = false;

    explicit LgsEnum(const std::string& enumName) : name(enumName), isRoot(true) {}
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    size_t getSizeBytes() override;
    LgsEnum* clone() override;
    ~LgsEnum() override = default;
};


