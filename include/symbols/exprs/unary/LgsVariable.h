#ifndef LOGOSVARIABLEEXPR_H
#define LOGOSVARIABLEEXPR_H
#include "LogosUnaryExpr.h"
#include "stmts/LgsVarDec.h"

class LgsVariable final :  public LgsUnaryExpr {
public:
    std::string name;

    explicit LgsVariable(const std::string& name) : LgsUnaryExpr(nullptr), name(name) {}
    string getName() override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsVariable() override = default;
};

#endif //LOGOSVARIABLEEXPR_H
