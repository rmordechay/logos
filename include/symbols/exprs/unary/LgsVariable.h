#pragma once
#include "LgsAssignable.h"
#include "LgsSymbol.h"
#include "LgsUnaryExpr.h"

struct LgsSymbol;

class LgsVariable final :  public LgsUnaryExpr {
public:
    std::string name;
    LgsSymbol ref;

    explicit LgsVariable(const std::string& name, LgsType* type = nullptr) : LgsUnaryExpr(type), name(name) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    Value* hash(LgsLLVMGen& cg) override;
    LgsExpr* castTo(LgsType* toType) override;
    void assign(LgsLLVMGen& cg, LgsExpr* expr) override;
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