#pragma once
#include <stmts/LgsStmt.h>
#include "LgsValue.h"

class LgsCast;
class LgsTypeExpr;
class LgsLoopMetaVar;
class LgsIntConst;
class LgsVectorExpr;
class LgsPrefixExpr;
class LgsIterator;
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

    explicit LgsExpr(LgsType* type = nullptr) : type(type) {}
    virtual LgsExpr* clone();
    virtual LgsExpr* castTo(LgsType* toType);
    virtual void completeType(LgsType* toType);

    virtual Value* hash(LgsLLVMGen& cg);
    virtual void assign(LgsLLVMGen& cg, LgsExpr* expr);
    virtual Value* getIRPtrTo(LgsLLVMGen& cg) const;
    virtual bool equals(LgsExpr* other);

    void freeOwner(LgsLLVMGen& cg);
    size_t getConstInt();
    std::string getConstStr();
    LgsIterator toIterator();
    void setType(LgsType* newType);
    std::pair<Value*, Value*> loadOperands(LgsLLVMGen& cg, LgsExpr* other);

    LgsFunc* asFunc();
    LgsVariable* asVariable();
    LgsPrefixExpr* asPrefixExpr();
    LgsIterIndex* asIterIndex();
    LgsTypeExpr* asTypeExpr();
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

    ~LgsExpr() override;
};
