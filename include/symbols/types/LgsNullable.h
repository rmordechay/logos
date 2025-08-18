#pragma once
#include "LgsType.h"

class LgsNullable final : public LgsType {
public:
    LgsType* baseType;

    explicit LgsNullable(LgsType* baseType) : baseType(baseType) {}
    llvm::Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    std::string pname() override;
    json::object asJSON() override;
    bool equals(LgsType* other) override;
    size_t getSizeBytes() override;
    std::string strFormatPart() const override;
    ~LgsNullable() override;
};
