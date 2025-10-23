#pragma once
#include "LgsType.h"

class LgsSize final : public LgsType {
public:
    static constexpr auto name = "Size";

    LgsSize() {
        isPrimitive = true;
        isInt = true;
    }
    size_t getSizeBytes() override;
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    LgsType* applyBinOp(LgsBinOpType op, LgsType* other) override;
    Value* addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* subIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* mulIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* divIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* modIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* bitAndIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* bitOrIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* bitXorIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* rshiftIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* lshiftIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* eqIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* neIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* ltIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* gtIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* geIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* leIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* andIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* orIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Lgs_rttype getRTType() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
};

inline LgsSize LGS_SIZE;