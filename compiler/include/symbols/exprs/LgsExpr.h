#pragma once
#include <stmts/LgsStmt.h>
#include "LgsValue.h"

class LgsMatrixExpr;
class LgsNullableExpr;
class LgsEnvVar;
class LgsBinaryExpr;
class LgsNull;
class LgsJson;
class LgsCast;
class LgsTypeExpr;
class LgsMetaVar;
class LgsIntConst;
class LgsVectorExpr;
class LgsPrefixExpr;
class LgsPostfixExpr;
class LgsLLVMGen;
class LgsFunc;
class LgsHashMap;
class LgsFuncCall;
class LgsType;
class LgsVariable;
class LgsSelection;
class LgsInstance;
class LgsIterIndex;
class LgsArrayExpr;
class LgsSArray;
class LgsCharConst;
class LgsFloatConst;
class LgsStrConst;
class LgsTypeConst;

class LgsExpr : public LgsStmt {
public:
    LgsType* type = nullptr;
    bool isMutable = true;
    bool isImportName = false;
    LgsValue* owner = nullptr;
    Value* destPtrValue = nullptr;

    explicit LgsExpr(LgsType* type = nullptr) : type(type) {}
    void freeOwner(LgsLLVMGen& cg);
    int64_t* getConstInt();
    std::string* getConstStr();
    void setType(LgsType* newType);
    LgsExpr* clone() override;

    virtual LgsExpr* castExplicitly(LgsType* toType);
    virtual void castImplicitly(LgsType* toType);
    virtual Value* castIR(LgsLLVMGen& cg, LgsType* toType) = 0;
    virtual Value* hashValue(LgsLLVMGen& cg);
    virtual void assign(LgsLLVMGen& cg, LgsExpr* expr);
    virtual bool equals(LgsExpr* other);
    virtual std::string asText() = 0;

    LgsNull* asNull();
    LgsFunc* asFunc();
    LgsVariable* asVariable();
    LgsPrefixExpr* asPrefixExpr();
    LgsIterIndex* asIterIndex();
    LgsTypeExpr* asTypeExpr();
    LgsJson* asJson();
    LgsCast* asCast();
    LgsInstance* asInstance();
    LgsArrayExpr* asArrayExpr();
    LgsHashMap* asHashMap();
    LgsEnvVar* asEnvVar();
    LgsCharConst* asCharConst();
    LgsFloatConst* asFloatConst();
    LgsStrConst* asStrConst();
    LgsVectorExpr* asVectorExpr();
    LgsMatrixExpr* asMatrixExpr();
    LgsIntConst* asIntConst();
    LgsMetaVar* asLoopMetaVar();
    LgsBinaryExpr* asBinExpr();
    LgsNullableExpr* asNullableExpr();
    ~LgsExpr() override = default;
};

void freeExpr(LgsExpr* expr);
void freeExprs(std::vector<LgsExpr*>& exprs);
