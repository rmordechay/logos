#pragma once
#include "LgsType.h"

class LgsFloat final : public LgsType {
public:
    static constexpr auto name = "Float";

    LgsFloat() {
        isPrimitive = true;
        rtt = RTT_FLOAT;
    }
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    size_t getSizeBytes() override;
    std::string strFormatPart() const override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyOp(LgsType* other, LgsOperator op) override;
    Value* addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* subIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* mulIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* divIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    std::string pname() override;
    json::value asJSON() override;
};

inline LgsFloat LGS_FLOAT;
