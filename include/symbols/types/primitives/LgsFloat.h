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
    Lgs_RTType getRTType() override;
    size_t getSizeBytes() override;
    std::string strFormatPart() const override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyOp(LgsType* other, LgsOperator op) override;
    Value* addIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* subIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* mulIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* divIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* eqIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    std::string pname() override;
    json::value asJsonStr() override;
};

inline LgsFloat LGS_FLOAT;
