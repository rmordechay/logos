#pragma once
#include "LgsType.h"
#include "exprs/LgsExpr.h"
#include "../codegen/LgsLLVM.h"

class LgsUnaryExpr : public LgsExpr {
public:
    explicit LgsUnaryExpr() : LgsExpr(nullptr) {}
    explicit LgsUnaryExpr(LgsType* type) : LgsExpr(type) {}
    Value* addIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* subIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* mulIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* divIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* inIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* modIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* eqIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* neIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* ltIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* gtIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* geIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* leIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* andIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* orIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* bitAndIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* bitOrIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* bitXorIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* rshiftIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* lshiftIR(LgsLLVM& codeGen, LgsExpr* other) override;
    std::pair<Value*, Value*> loadExprs(LgsLLVM* codeGen, LgsExpr* rExpr);
};

