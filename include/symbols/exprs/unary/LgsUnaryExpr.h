#pragma once
#include "exprs/LgsExpr.h"
#include "codegen/LgsLLVMGen.h"

class LgsUnaryExpr : public LgsExpr {
public:
    explicit LgsUnaryExpr() : LgsExpr(nullptr) {}
    explicit LgsUnaryExpr(LgsType* type) : LgsExpr(type) {}
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
    std::pair<Value*, Value*> loadExprs(LgsLLVMGen* cg, LgsExpr* rExpr);
};

