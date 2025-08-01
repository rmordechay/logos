#pragma once
#include "LgsUnaryExpr.h"

struct LgsSymbol;

class LgsVariable :  public LgsUnaryExpr {
public:
    string name;
    LgsSymbol ref;

    explicit LgsVariable(const string& name) : LgsUnaryExpr(nullptr), name(name) {}
    explicit LgsVariable(const string& name, LgsType* type) : LgsUnaryExpr(type), name(name) {}
    string prettyName() override;
    Value* hashValue(LgsCodeGen* codeGen) override;
    Value* createIRValue(LgsCodeGen* codeGen) override;
    LgsExpr* convertExpr(LgsType* type) override;
    bool equals(LgsExpr* other) override;
    ~LgsVariable() override = default;
};