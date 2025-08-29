#pragma once
#include <stmts/LgsStmt.h>
#include "LgsValue.h"

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

    explicit LgsExpr(LgsType* type) : type(type) {}

    virtual LgsExpr* clone();
    virtual LgsExpr* castTo(LgsType* toType);
    virtual void completeType(LgsType* toType);
    virtual llvm::Value* hash(LgsLLVMGen& cg);
    virtual std::string pname() = 0; // pretty name
    virtual void assign(LgsLLVMGen& cg, LgsExpr* expr);
    virtual llvm::Value* addIR(LgsLLVMGen& cg, LgsExpr* other) = 0;
    virtual llvm::Value* subIR(LgsLLVMGen& cg, LgsExpr* other) = 0;
    virtual llvm::Value* mulIR(LgsLLVMGen& cg, LgsExpr* other) = 0;
    virtual llvm::Value* divIR(LgsLLVMGen& cg, LgsExpr* other) = 0;
    virtual llvm::Value* inIR(LgsLLVMGen& cg, LgsExpr* other) = 0;
    virtual llvm::Value* modIR(LgsLLVMGen& cg, LgsExpr* other) = 0;
    virtual llvm::Value* eqIR(LgsLLVMGen& cg, LgsExpr* other) = 0;
    virtual llvm::Value* neIR(LgsLLVMGen& cg, LgsExpr* other) = 0;
    virtual llvm::Value* ltIR(LgsLLVMGen& cg, LgsExpr* other) = 0;
    virtual llvm::Value* gtIR(LgsLLVMGen& cg, LgsExpr* other) = 0;
    virtual llvm::Value* geIR(LgsLLVMGen& cg, LgsExpr* other) = 0;
    virtual llvm::Value* leIR(LgsLLVMGen& cg, LgsExpr* other) = 0;
    virtual llvm::Value* andIR(LgsLLVMGen& cg, LgsExpr* other) = 0;
    virtual llvm::Value* orIR(LgsLLVMGen& cg, LgsExpr* other) = 0;
    virtual llvm::Value* bitAndIR(LgsLLVMGen& cg, LgsExpr* other) = 0;
    virtual llvm::Value* bitOrIR(LgsLLVMGen& cg, LgsExpr* other) = 0;
    virtual llvm::Value* bitXorIR(LgsLLVMGen& cg, LgsExpr* other) = 0;
    virtual llvm::Value* rshiftIR(LgsLLVMGen& cg, LgsExpr* other) = 0;
    virtual llvm::Value* lshiftIR(LgsLLVMGen& cg, LgsExpr* other) = 0;

    size_t getConstInt();
    std::string getConstStr();
    LgsIterator toIterator();
    void setType(LgsType* newType);
    bool equals(const LgsExpr* other);
    llvm::Value* getIRPtrTo(LgsLLVMGen& cg) const;

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
