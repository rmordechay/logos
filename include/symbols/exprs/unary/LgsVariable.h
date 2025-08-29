#pragma once
#include "LgsAssignable.h"
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
    std::string pname() override;
    json::value asJSON() override;
};