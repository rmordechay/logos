#pragma once
#include "LgsUnaryExpr.h"

struct LgsSymbol;

class LgsVariable final :  public LgsUnaryExpr {
public:
    std::string name;
    LgsSymbol ref;

    explicit LgsVariable(const std::string& name, LgsType* type = nullptr) : LgsUnaryExpr(type), name(name) {
        isAssignable = true;
    }

    Value* hash(LgsLLVM& codeGen) override;
    LgsExpr* castTo(LgsType* toType) override;
    std::string pname() override;
    json::value asJSON() override;
};