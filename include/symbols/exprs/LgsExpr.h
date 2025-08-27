#pragma once
#include <stmts/LgsStmt.h>
#include "LgsValue.h"

class LgsLoopMetaVar;
class LgsIntConst;
class LgsVectorExpr;
class LgsPrefixExpr;
class LgsIterator;
class LgsPostfixExpr;
class LgsLLVM;
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
    virtual std::string pname() = 0; // pretty name
    virtual llvm::Value* addIR(LgsLLVM& codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* subIR(LgsLLVM& codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* mulIR(LgsLLVM& codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* divIR(LgsLLVM& codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* inIR(LgsLLVM& codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* modIR(LgsLLVM& codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* eqIR(LgsLLVM& codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* neIR(LgsLLVM& codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* ltIR(LgsLLVM& codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* gtIR(LgsLLVM& codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* geIR(LgsLLVM& codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* leIR(LgsLLVM& codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* andIR(LgsLLVM& codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* orIR(LgsLLVM& codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* bitAndIR(LgsLLVM& codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* bitOrIR(LgsLLVM& codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* bitXorIR(LgsLLVM& codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* rshiftIR(LgsLLVM& codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* lshiftIR(LgsLLVM& codeGen, LgsExpr* other) = 0;

    size_t getConstInt();
    std::string getConstStr();
    LgsIterator toIterator();
    void setType(LgsType* newType);
    bool equals(const LgsExpr* other);

    LgsFunc* asFunc();
    LgsVariable* asVariable();
    LgsPrefixExpr* asPrefixExpr();
    LgsIterIndex* asIterIndex();
    LgsInstance* asInstance();
    LgsArrayExpr* asArrayExpr();
    LgsHashMap* asHashMap();
    LgsCharConst* asCharConst();
    LgsFloatConst* asFloatConst();
    LgsStrConst* asStrConst();
    LgsVectorExpr* asVectorExpr();
    LgsIntConst* asIntConst();
    LgsLoopMetaVar* asLoopMetaVar();

    virtual LgsExpr* clone();
    virtual LgsExpr* castTo(LgsType* toType);
    virtual void completeType(LgsType* toType);
    virtual llvm::Value* hash(LgsLLVM& codeGen);
    ~LgsExpr() override;
};
