#pragma once
#include "LgsType.h"

class LgsNullable final : public LgsType {
public:
    LgsType* baseType;

    explicit LgsNullable(LgsType* baseType) : baseType(baseType) {}
    llvm::Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    std::string pname() override;
    json::value asJSON() override;
    bool canCastTo(LgsType* other) override;
    size_t getSizeBytes() override;
    std::string strFormatPart() const override;
    ~LgsNullable() override;
};
