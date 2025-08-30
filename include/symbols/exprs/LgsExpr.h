#pragma once
#include <stmts/LgsStmt.h>
#include "LgsValue.h"
#include "stmts/LgsAssignment.h"

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

class LgsExpr : virtual public LgsStmt {
public:
    LgsType* type = nullptr;
    bool isNull = false;
    bool isSpread = false;
    bool isMutable = false;
    bool isAssignable = false;

    explicit LgsExpr(LgsType* type) : type(type) {}
    virtual LgsExpr* clone();
    virtual LgsExpr* castTo(LgsType* toType);
    virtual void completeType(LgsType* toType);
    virtual Value* hash(LgsLLVMGen& cg);
    virtual std::string pname() = 0; // pretty name
    virtual void assign(LgsLLVMGen& cg, LgsExpr* expr);
    virtual Value* addIR(LgsLLVMGen& cg, LgsExpr* other);
    virtual Value* subIR(LgsLLVMGen& cg, LgsExpr* other);
    virtual Value* mulIR(LgsLLVMGen& cg, LgsExpr* other);
    virtual Value* divIR(LgsLLVMGen& cg, LgsExpr* other);
    virtual Value* inIR(LgsLLVMGen& cg, LgsExpr* other);
    virtual Value* modIR(LgsLLVMGen& cg, LgsExpr* other);
    virtual Value* eqIR(LgsLLVMGen& cg, LgsExpr* other);
    virtual Value* neIR(LgsLLVMGen& cg, LgsExpr* other);
    virtual Value* ltIR(LgsLLVMGen& cg, LgsExpr* other);
    virtual Value* gtIR(LgsLLVMGen& cg, LgsExpr* other);
    virtual Value* geIR(LgsLLVMGen& cg, LgsExpr* other);
    virtual Value* leIR(LgsLLVMGen& cg, LgsExpr* other);
    virtual Value* andIR(LgsLLVMGen& cg, LgsExpr* other);
    virtual Value* orIR(LgsLLVMGen& cg, LgsExpr* other);
    virtual Value* bitAndIR(LgsLLVMGen& cg, LgsExpr* other);
    virtual Value* bitOrIR(LgsLLVMGen& cg, LgsExpr* other);
    virtual Value* bitXorIR(LgsLLVMGen& cg, LgsExpr* other);
    virtual Value* rshiftIR(LgsLLVMGen& cg, LgsExpr* other);
    virtual Value* lshiftIR(LgsLLVMGen& cg, LgsExpr* other);

    size_t getConstInt();
    std::string getConstStr();
    LgsIterator toIterator();
    void setType(LgsType* newType);
    bool equals(const LgsExpr* other);
    Value* getIRPtrTo(LgsLLVMGen& cg) const;

    LgsFunc* asFunc();
    LgsVariable* asVariable();
    LgsPrefixExpr* asPrefixExpr();
    LgsIterIndex* asIterIndex();
    LgsTypeExpr* asTypeExpr();
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
