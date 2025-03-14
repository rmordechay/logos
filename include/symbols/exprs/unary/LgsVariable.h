#ifndef LOGOSVARIABLEEXPR_H
#define LOGOSVARIABLEEXPR_H
#include "LogosUnaryExpr.h"
#include "stmts/LgsVarDec.h"

class LgsVariable final :  public LgsUnaryExpr {
public:
    std::string name;

    explicit LgsVariable(const std::string& name) : LgsUnaryExpr(nullptr), name(name) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    string getName() override;
    ~LgsVariable() override = default;
};

#endif //LOGOSVARIABLEEXPR_H
