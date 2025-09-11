#pragma once
#include "LgsType.h"

class LgsInt final : public LgsType {
public:
    static constexpr auto name = "Int";

    LgsInt() {
        isPrimitive = true;
        isNumber = true;
        isInt = true;
        rtt = RTT_INT;
    }
    size_t getSizeBytes() override;
    Type* getIRType(LgsLLVMGen& cg) override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    bool canAssignTo(LgsType* other, LgsAssignType op) override;
    bool canApplyOp(LgsType* other, LgsOperator op) override;
    Value* addIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* subIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* mulIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* divIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* inIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* modIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* eqIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* neIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* ltIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* gtIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* geIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* leIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* andIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* orIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* bitAndIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* bitOrIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* bitXorIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* rshiftIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* lshiftIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    std::string strFormatPart() const override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    LgsType* clone() override;
    DIBasicType* getDebugType(LgsLLVMGen& cg) override;
};

inline LgsInt LGS_INT;
