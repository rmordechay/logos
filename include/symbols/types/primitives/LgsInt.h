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
    std::string strFormatPart() const override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    LgsType* clone() override;
    DIBasicType* getDebugType(LgsLLVMGen& cg) override;
};

inline LgsInt LGS_INT;
