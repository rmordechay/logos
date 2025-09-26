#pragma once
#include "LgsType.h"

class LgsBool final : public LgsType {
public:
    static constexpr auto name = "Bool";
    static constexpr auto trueLiteral = "true";
    static constexpr auto falseLiteral = "false";

    LgsBool() {
        isPrimitive = true;
        isInt = true;
    }
    Type* getIRType(LgsLLVMGen& cg) override;
    LgsType* applyOp(LgsType* other, LgsOperator op) override;
    Value* addIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* subIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* mulIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* divIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* modIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* eqIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* neIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* ltIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* gtIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* geIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* leIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* bitAndIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* bitOrIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* bitXorIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* rshiftIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* lshiftIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* andIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* orIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    std::string strFormatPart() const override;
    size_t getSizeBytes() override;
    bool canCastTo(LgsType* other) override;
};

inline LgsBool LGS_BOOL;


