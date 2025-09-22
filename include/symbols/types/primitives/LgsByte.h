#pragma once
#include "LgsType.h"

class LgsByte final : public LgsType {
public:
    static constexpr auto name = "Byte";

    LgsByte() {
        isPrimitive = true;
        isInt = true;
        rtt = RTT_BYTE;
    }

    Type* getIRType(LgsLLVMGen& cg) override;
    LgsType* applyOp(LgsType* other, LgsOperator op) override;
    Value* addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* subIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* mulIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* divIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* modIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* eqIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* neIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* ltIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* gtIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* geIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* leIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* bitAndIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* bitOrIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* bitXorIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* rshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* lshiftIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* andIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* orIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string getName() override;
    std::string pname() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    json::value asJSON() override;
};

inline LgsByte LGS_BYTE;