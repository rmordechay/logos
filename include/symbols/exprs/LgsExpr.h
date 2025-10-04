#pragma once
#include <stmts/LgsStmt.h>
#include "LgsValue.h"

class LgsJson;
class LgsCast;
class LgsTypeExpr;
class LgsLoopMetaVar;
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

using namespace llvm;

enum LgsAssignType {
    ASSIGN,
    ASSIGN_ADD,
    ASSIGN_SUB,
    ASSIGN_MUL,
    ASSIGN_DIV,
    ASSIGN_MOD,
    ASSIGN_AND,
    ASSIGN_OR,
    ASSIGN_XOR,
    ASSIGN_LSHIFT,
    ASSIGN_RSHIFT,
};

class LgsExpr : virtual public LgsStmt {
public:
    LgsType* type = nullptr;
    bool isNull = false;
    bool isSpread = false;
    bool isMutable = false;
    LgsValue* owner = nullptr;
    Value* destPtrValue = nullptr;

    explicit LgsExpr(LgsType* type = nullptr) : type(type) {}
    virtual LgsExpr* castTo(LgsType* toType, bool explicitCast = false);
    virtual Value* castToIR(LgsLLVMGen& cg, LgsType* toType);
    virtual void completeType(LgsType* toType);
    virtual Value* hash(LgsLLVMGen& cg);
    virtual void assign(LgsLLVMGen& cg, LgsExpr* expr);
    virtual bool equals(LgsExpr* other);
    virtual LgsExpr* clone();

    void freeOwner(LgsLLVMGen& cg);
    int64_t getConstInt();
    std::string getConstStr();
    void setType(LgsType* newType);
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
    LgsCharConst* asCharConst();
    LgsFloatConst* asFloatConst();
    LgsStrConst* asStrConst();
    LgsVectorExpr* asVectorExpr();
    LgsIntConst* asIntConst();
    LgsLoopMetaVar* asLoopMetaVar();

    virtual Value* eqIR(LgsLLVMGen& cg, Value* other);
    virtual Value* neIR(LgsLLVMGen& cg, Value* other);
    virtual Value* ltIR(LgsLLVMGen& cg, Value* other);
    virtual Value* gtIR(LgsLLVMGen& cg, Value* other);
    virtual Value* geIR(LgsLLVMGen& cg, Value* other);
    virtual Value* leIR(LgsLLVMGen& cg, Value* other);
    virtual Value* andIR(LgsLLVMGen& cg, Value* other);
    virtual Value* orIR(LgsLLVMGen& cg, Value* other);
    ~LgsExpr() override = default;
};
