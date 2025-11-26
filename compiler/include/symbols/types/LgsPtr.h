#pragma once
#include "LgsType.h"

class LgsPtr final : public LgsType {
public:
    static constexpr auto name = "CPtr";
    LgsType* baseType;

    explicit LgsPtr(LgsType* baseType) : baseType(baseType) {}
    std::string getName() override;
    std::string pname() override;
    Type* getIRType(LgsLLVMGen& cg) override;
    Constant* getRTType(LgsLLVMGen& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    llvm::DIType* getDebugType(LgsLLVMGen& cg) override;
    LgsType* clone() override;
    ~LgsPtr() override;
};
