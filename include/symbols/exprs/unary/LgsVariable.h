#pragma once
#include "LgsUnaryExpr.h"

struct LgsSymbol;

class LgsVariable final :  public LgsUnaryExpr {
public:
    std::string name;
    LgsSymbol ref;

    explicit LgsVariable(const std::string& name, LgsType* type = nullptr) : LgsUnaryExpr(type), name(name) {}
    std::string pname() override;
    Value* hash(LgsCodeGen* codeGen) override;
    void createIRValue(LgsCodeGen* codeGen) override;
    json::value_ref asJSON() override;
    bool equals(LgsExpr* other) override;
};