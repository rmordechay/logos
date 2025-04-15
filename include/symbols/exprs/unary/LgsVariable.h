#ifndef LOGOSVARIABLEEXPR_H
#define LOGOSVARIABLEEXPR_H
#include "LgsUnaryExpr.h"

class LgsVariable :  public LgsUnaryExpr {
public:
    std::string name;
    LgsSymbol* ref = nullptr;

    explicit LgsVariable(const std::string& name) : LgsUnaryExpr(nullptr), name(name) {}
    string getName() override;
    uint32_t hashValue() override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* eqIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    ~LgsVariable() override;
};

class LgsConst final :  public LgsVariable {
public:
    explicit LgsConst(const std::string& name) : LgsVariable(name) {}
};

#endif //LOGOSVARIABLEEXPR_H
