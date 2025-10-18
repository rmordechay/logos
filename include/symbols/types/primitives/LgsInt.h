#pragma once
#include "LgsType.h"

class LgsInt final : public LgsType {
public:
    static constexpr auto name = "Int";

    LgsInt() {
        isPrimitive = true;
        isInt = true;
    }
    size_t getSizeBytes() override;
    Type* getIRType(LgsLLVMGen& cg) override;
    LgsExpr* getZeroValue() override;
    Lgs_rttype getRTType() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsBinOpType op, LgsType* other) override;
    Value* addIR(LgsLLVMGen& cg, Value* self, Value* other) override;
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
    std::string strFormatPart() const override;
    std::string getName() override;
    DIBasicType* getDebugType(LgsLLVMGen& cg) override;
};

inline LgsInt LGS_INT;
