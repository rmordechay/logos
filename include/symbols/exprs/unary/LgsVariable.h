#pragma once
#include "LgsUnaryExpr.h"

struct LgsSymbol;

class LgsVariable :  public LgsUnaryExpr {
public:
    string name;
    LgsSymbol ref;

    explicit LgsVariable(const string& name) : LgsUnaryExpr(nullptr), name(name) {}
    string getExprName() override;
    string prettyName() override;
    Value* hashValue(LgsModule* module) override;
    Value* createIRValue(LgsModule* module) override;
    LgsExpr* convertExpr(LgsType* type) override;
    bool equals(LgsExpr* other) override;
    ~LgsVariable() override = default;
};

class LgsConst final :  public LgsVariable {
public:
    explicit LgsConst(const string& name) : LgsVariable(name) {}
};


