#pragma once
#include <stmts/LgsStmt.h>
#include "LgsValue.h"

class LgsIntConst;
class LgsVectorExpr;
class LgsPrefixExpr;
class LgsIterator;
class LgsPostfixExpr;
class LgsCodeGen;
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
    bool isConstant = false;

    explicit LgsExpr(LgsType* type) : type(type) {}
    size_t getConstInt();
    std::string getConstStr();
    LgsIterator toIterator();
    void setType(LgsType* newType);

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
    LgsVectorExpr* asVector();
    LgsIntConst* asIntConst();

    virtual bool equals(LgsExpr* other);
    virtual bool castTo(LgsType* toType);
    virtual llvm::Value* hash(LgsCodeGen* codeGen);

    virtual std::string pname() = 0; // pretty name
    virtual llvm::Value* addIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* subIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* mulIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* divIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* modIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* eqIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* neIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* ltIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* gtIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* geIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* leIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* andIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* orIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* bitAndIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* bitOrIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* bitXorIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* rshiftIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual llvm::Value* lshiftIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    ~LgsExpr() override;
};
