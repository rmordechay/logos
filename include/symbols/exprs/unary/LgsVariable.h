#pragma once
#include "LgsUnaryExpr.h"

struct LgsSymbol;

class LgsVariable :  public LgsUnaryExpr {
public:
    std::string name;
    LgsSymbol ref;

    explicit LgsVariable(const std::string& name) : LgsUnaryExpr(nullptr), name(name) {}
    explicit LgsVariable(const std::string& name, LgsType* type) : LgsUnaryExpr(type), name(name) {}
    std::string prettyName() override;
    Value* hashValue(LgsCodeGen* codeGen) override;
    Value* createIRValue(LgsCodeGen* codeGen) override;
    LgsExpr* castTo(LgsType* type) override;
    bool equals(LgsExpr* other) override;
    ~LgsVariable() override = default;
};