#pragma once
#include "LgsType.h"
#include <string>

class LgsEnum final : public LgsType {
public:
    std::string name;

    explicit LgsEnum(const std::string& enumName) : name(enumName) {}
    Type* getIRType(LgsLLVMGen& cg) override;
    Constant* getRTType(LgsLLVMGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    size_t sizeBytes() override;
    LgsEnum* clone() override;
    llvm::DIType* getDebugType(LgsLLVMGen& cg) override;
};


