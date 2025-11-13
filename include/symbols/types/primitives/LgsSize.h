#pragma once
#include "LgsType.h"

class LgsSize final : public LgsType {
public:
    static constexpr auto name = "Size";

    LgsSize() {
        isPrimitive = true;
        isInt = true;
    }
    size_t sizeBytes() override;
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    LgsType* applyBinOp(LgsBinaryExpr* binExpr) override;
    Value* addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* subIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* mulIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* divIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* modIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* bitAndIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* bitOrIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* bitXorIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* rshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* lshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* eqIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* neIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* ltIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* gtIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* geIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* leIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* andIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* orIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Lgs_TypeKind getRTTypeKind() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
};

inline LgsSize LGS_SIZE;