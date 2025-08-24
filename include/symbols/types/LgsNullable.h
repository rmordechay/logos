#pragma once
#include "LgsType.h"

class LgsNullable final : public LgsType {
public:
    LgsType* baseType;

    explicit LgsNullable(LgsType* baseType) : baseType(baseType) {}
    llvm::Type* getIRType(LgsLLVM& codeGen) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    std::string pname() override;
    json::value asJSON() override;
    bool canCastTo(LgsType* other) override;
    size_t getSizeBytes() override;
    std::string strFormatPart() const override;
    ~LgsNullable() override;
};
