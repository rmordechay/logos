#pragma once
#include "LgsType.h"

class LgsFloat final : public LgsType {
public:
    static constexpr auto name = "Float";

    LgsFloat() {
        isPrimitive = true;
        isFloat = true;
    }
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    Lgs_TypeKind getRTTypeKind() override;
    size_t sizeBytes() override;
    std::string strFormatPart() const override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsBinaryExpr* binExpr) override;
    Value* addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* subIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* mulIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* divIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
};

inline LgsFloat LGS_FLOAT;
