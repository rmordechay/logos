#pragma once
#include "LgsAssignable.h"
#include "LgsUnaryExpr.h"

struct LgsSymbol;

class LgsVariable final :  public LgsUnaryExpr, public LgsAssignable {
public:
    std::string name;
    LgsSymbol ref;

    explicit LgsVariable(const std::string& name, LgsType* type = nullptr) : LgsUnaryExpr(type), name(name) {}
    Value* hash(LgsLLVM& codeGen) override;
    LgsExpr* castTo(LgsType* toType) override;
    void assign(LgsLLVM& codeGen, LgsExpr* expr) override;
    std::string pname() override;
    json::value asJSON() override;
};