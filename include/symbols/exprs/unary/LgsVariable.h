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
    uint32_t hashValue(CodegenMetadata* metadata) override;
    Value* getLength(CodegenMetadata* metadata) override;
    Value* createIRValue(CodegenMetadata* metadata) override;
    Value* eqIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* neIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* gtIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* ltIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* geIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* leIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* bitAndIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* bitOrIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* bitXorIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* rshiftIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* lshiftIR(CodegenMetadata* metadata, LgsExpr* other) override;
    json asJSON() override;
    ~LgsVariable() override = default;
};

class LgsConst final :  public LgsVariable {
public:
    explicit LgsConst(const std::string& name) : LgsVariable(name) {}
};

#endif //LOGOSVARIABLEEXPR_H
