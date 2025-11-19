#pragma once
#include "LgsType.h"

class LgsByte final : public LgsType {
public:
    static constexpr auto name = "Byte";

    LgsByte() {
        isPrimitive = true;
        isInt = true;
    }

    Type* getIRType(LgsLLVMGen& cg) override;
    LgsType* applyBinOp(LgsBinaryExpr* binExpr) override;
    Value* addIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* subIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* mulIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* divIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* modIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* bitAndIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* bitOrIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* bitXorIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* rshiftIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    Value* lshiftIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* other) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_TypeKind getRTTypeKind() override;
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
};

inline LgsByte LGS_BYTE;