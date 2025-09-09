#pragma once
#include "exprs/LgsExpr.h"

class LgsIntConst final : public LgsExpr {
public:
    uint64_t value;

    LgsIntConst(LgsType* type, const size_t value) : LgsExpr(type), value(value) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    LgsExpr* castTo(LgsType* toType) override;
    LgsExpr* clone() override;
    Value* addIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* subIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* mulIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* divIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* modIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* eqIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* neIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* ltIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* gtIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* geIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* leIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* andIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* orIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* bitAndIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* bitOrIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* bitXorIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* rshiftIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* lshiftIR(LgsLLVMGen& cg, LgsExpr* other) override;
    std::string pname() override;
    json::value asJSON() override;
};
