#pragma once
#include "LgsType.h"
#include "exprs/LgsExpr.h"
#include "../codegen/LgsCodeGen.h"

class LgsUnaryExpr : public LgsExpr {
public:
    explicit LgsUnaryExpr() : LgsExpr(nullptr) {}
    explicit LgsUnaryExpr(LgsType* type) : LgsExpr(type) {}
    Value* addIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    Value* subIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    Value* mulIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    Value* divIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    Value* inIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    Value* modIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    Value* eqIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    Value* neIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    Value* ltIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    Value* gtIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    Value* geIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    Value* leIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    Value* andIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    Value* orIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    Value* bitAndIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    Value* bitOrIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    Value* bitXorIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    Value* rshiftIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    Value* lshiftIR(LgsCodeGen& codeGen, LgsExpr* other) override;
    std::pair<Value*, Value*> loadExprs(LgsCodeGen* codeGen, LgsExpr* rExpr);
};

