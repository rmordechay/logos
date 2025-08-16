#pragma once
#include <stmts/LgsStmt.h>

#include "LgsValue.h"

class LgsVec2;
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
class LgsBoolConst;
class LgsCharConst;
class LgsFloatConst;
class LgsIntConst;
class LgsStrConst;
class LgsTypeConst;

class LgsExpr : virtual public LgsStmt {
public:
    LgsType* type = nullptr;
    bool isNull = false;
    bool isSpread = false;
    bool isConstant = false;
    bool isHeapAlloc = false;

    explicit LgsExpr(LgsType* type) : type(type) {}
    int getConstInt();
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
    LgsBoolConst* asBoolConst();
    LgsCharConst* asCharConst();
    LgsFloatConst* asFloatConst();
    LgsIntConst* asIntConst();
    LgsStrConst* asStrConst();
    LgsVec2* asVec2();

    virtual LgsExpr* clone();
    virtual bool equals(LgsExpr* other);
    virtual LgsExpr* castTo(LgsType* toType);
    virtual Value* hashValue(LgsCodeGen* codeGen);

    virtual std::string prettyName() = 0;
    virtual Value* addIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual Value* subIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual Value* mulIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual Value* divIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual Value* modIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual Value* eqIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual Value* neIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual Value* ltIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual Value* gtIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual Value* geIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual Value* leIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual Value* andIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual Value* orIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual Value* bitAndIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual Value* bitOrIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual Value* bitXorIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual Value* rshiftIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual Value* lshiftIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    ~LgsExpr() override;
};

