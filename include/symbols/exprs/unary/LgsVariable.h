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
    string getStrFormatPart() const override;
    uint32_t hashValue(CodeGenMetadata* metadata) override;
    Value* getLength(CodeGenMetadata* metadata) override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* eqIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* neIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* gtIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* ltIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* geIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* leIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* bitAndIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* bitOrIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* bitXorIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* rshiftIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* lshiftIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    json asJSON() override;
    ~LgsVariable() override = default;
};

class LgsConst final :  public LgsVariable {
public:
    explicit LgsConst(const std::string& name) : LgsVariable(name) {}
};

#endif //LOGOSVARIABLEEXPR_H
