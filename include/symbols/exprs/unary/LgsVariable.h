#ifndef LOGOSVARIABLEEXPR_H
#define LOGOSVARIABLEEXPR_H
#include "LgsUnaryExpr.h"

struct LgsSymbol;

class LgsVariable :  public LgsUnaryExpr {
public:
    std::string name;
    LgsSymbol* ref = nullptr;

    explicit LgsVariable(const std::string& name) : LgsUnaryExpr(nullptr), name(name) {}
    std::string getName() override;
    std::string prettyName() override;
    uint32_t hashValue(LgsRuntime* runtime) override;
    Value* createIRValue(LgsRuntime* runtime) override;
    bool equals(LgsExpr* other) override;
    Value* eqIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* neIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* gtIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* ltIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* geIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* leIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* bitAndIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* bitOrIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* bitXorIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* rshiftIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* lshiftIR(LgsRuntime* runtime, LgsExpr* other) override;
    json asJSON() override;
    ~LgsVariable() override = default;
};

class LgsConst final :  public LgsVariable {
public:
    explicit LgsConst(const std::string& name) : LgsVariable(name) {}
};

#endif //LOGOSVARIABLEEXPR_H
