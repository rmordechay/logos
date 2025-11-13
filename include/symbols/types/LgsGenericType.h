#pragma once
#include "LgsType.h"

class LgsGenericType final : public LgsType {
public:
    std::string name;

    explicit LgsGenericType(const std::string& name): name(name) {}
    Type* getIRType(LgsLLVMGen& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_TypeKind getRTTypeKind() override;
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    LgsGenericType* clone() override;
    std::string strFormatPart() const override;
};
