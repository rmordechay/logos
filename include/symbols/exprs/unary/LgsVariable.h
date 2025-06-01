#ifndef LOGOSVARIABLEEXPR_H
#define LOGOSVARIABLEEXPR_H
#include "LgsUnaryExpr.h"

class LgsVariable :  public LgsUnaryExpr {
public:
    std::string name;
    LgsSymbol* ref = nullptr;

    explicit LgsVariable(const std::string& name) : LgsUnaryExpr(nullptr), name(name) {}
    string getName() override;
    string prettyName() override;
    uint32_t hashValue(Module* module) override;
    Value* getLength(Module* module) override;
    Value* createIRValue(Module* module) override;
    Value* eqIR(Module* module, LgsExpr* other) override;
    Value* neIR(Module* module, LgsExpr* other) override;
    Value* gtIR(Module* module, LgsExpr* other) override;
    Value* ltIR(Module* module, LgsExpr* other) override;
    Value* geIR(Module* module, LgsExpr* other) override;
    Value* leIR(Module* module, LgsExpr* other) override;
    Value* bitAndIR(Module* module, LgsExpr* other) override;
    Value* bitOrIR(Module* module, LgsExpr* other) override;
    Value* bitXorIR(Module* module, LgsExpr* other) override;
    Value* rshiftIR(Module* module, LgsExpr* other) override;
    Value* lshiftIR(Module* module, LgsExpr* other) override;
    json asJSON() override;
    ~LgsVariable() override = default;
};

class LgsConst final :  public LgsVariable {
public:
    explicit LgsConst(const std::string& name) : LgsVariable(name) {}
};

#endif //LOGOSVARIABLEEXPR_H
