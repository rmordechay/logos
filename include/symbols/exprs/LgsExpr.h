#pragma once
#include <stmts/LgsStmt.h>
#include "LgsValue.h"

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

class LgsExpr : virtual public LgsStmt {
public:
    LgsType* type = nullptr;
    bool isSpread = false;
    bool isMutable = false;
    bool isValueKnown = false;
    bool isNullable = false;
    bool isImportName = false;
    LgsValue* owner = nullptr;
    Value* destPtrValue = nullptr;

    explicit LgsExpr(LgsType* type = nullptr) : type(type) {}
    virtual LgsExpr* castTo(LgsType* toType, bool explicitCast = false);
    virtual Value* castToIR(LgsLLVMGen& cg, LgsType* toType);
    virtual void completeType(LgsType* toType);
    virtual Value* hash(LgsLLVMGen& cg);
    virtual void assign(LgsLLVMGen& cg, LgsExpr* expr);
    virtual bool equals(LgsExpr* other);
    virtual LgsExpr* cloneExpr();

    void freeOwner(LgsLLVMGen& cg);
    int64_t* getConstInt();
    std::string* getConstStr();
    void setType(LgsType* newType);

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
    LgsIntConst* asIntConst();
    LgsMetaVar* asLoopMetaVar();
    LgsBinaryExpr* asBinExpr();
    ~LgsExpr() override = default;
};
