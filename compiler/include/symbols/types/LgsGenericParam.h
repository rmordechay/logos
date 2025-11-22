#pragma once
#include "LgsType.h"

class LgsGenericParam final : public LgsType {
public:
    std::string name;

    explicit LgsGenericParam(const std::string& name): name(name) {}
    Type* getIRType(LgsLLVMGen& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_TypeKind getRTTypeKind() override;
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    llvm::DIType* getDebugType(LgsLLVMGen& cg) override;
    LgsGenericParam* clone() override;
};
