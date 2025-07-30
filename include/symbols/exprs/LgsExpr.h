#pragma once
#include "LgsValue.h"

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

class LgsExpr : virtual public LgsValue {
public:
    LgsType* type = nullptr;
    bool isNull = false;
    bool isSpread = false;
    bool isHeapAlloc = false;
    bool isConstant = false;
    BasicBlock* parentBlock = nullptr;

    explicit LgsExpr(LgsType* type) : type(type) {}
    Value* getIRValue(LgsCodeGen* codeGen);
    void setType(LgsType* newType);
    int getConstInt();
    string getConstStr();
    LgsIterator toIterator();

    LgsFunc* asFunc();
    LgsVariable* asVariable();
    LgsFuncCall* asFuncCall();
    LgsPrefixExpr* asPrefixExpr();
    LgsPostfixExpr* asPostfixExpr();
    LgsIterIndex* asIterIndex();
    LgsInstance* asInstance();
    LgsSelection* asSelection();
    LgsArrayExpr* asArrayExpr();
    LgsHashMap* asHashMap();
    LgsBoolConst* asBoolConst();
    LgsCharConst* asCharConst();
    LgsFloatConst* asFloatConst();
    LgsIntConst* asIntConst();
    LgsStrConst* asStrConst();

    virtual LgsExpr* clone();
    virtual bool equals(LgsExpr* other);
    virtual LgsExpr* convertExpr(LgsType* toType);
    virtual void free(LgsCodeGen* codeGen);
    virtual Value* hashValue(LgsCodeGen* codeGen);

    virtual string prettyName() = 0;
    virtual Value* createIRValue(LgsCodeGen* codeGen) = 0;
    virtual Value* addIR(LgsCodeGen* codeGen, LgsExpr* other) = 0;
    virtual Value* subIR(LgsCodeGen* codeGen, LgsExpr* other);
    virtual Value* mulIR(LgsCodeGen* codeGen, LgsExpr* other);
    virtual Value* divIR(LgsCodeGen* codeGen, LgsExpr* other);
    virtual Value* modIR(LgsCodeGen* codeGen, LgsExpr* other);
    virtual Value* eqIR(LgsCodeGen* codeGen, LgsExpr* other);
    virtual Value* neIR(LgsCodeGen* codeGen, LgsExpr* other);
    virtual Value* ltIR(LgsCodeGen* codeGen, LgsExpr* other);
    virtual Value* gtIR(LgsCodeGen* codeGen, LgsExpr* other);
    virtual Value* geIR(LgsCodeGen* codeGen, LgsExpr* other);
    virtual Value* leIR(LgsCodeGen* codeGen, LgsExpr* other);
    virtual Value* andIR(LgsCodeGen* codeGen, LgsExpr* other);
    virtual Value* orIR(LgsCodeGen* codeGen, LgsExpr* other);
    virtual Value* bitAndIR(LgsCodeGen* codeGen, LgsExpr* other);
    virtual Value* bitOrIR(LgsCodeGen* codeGen, LgsExpr* other);
    virtual Value* bitXorIR(LgsCodeGen* codeGen, LgsExpr* other);
    virtual Value* rshiftIR(LgsCodeGen* codeGen, LgsExpr* other);
    virtual Value* lshiftIR(LgsCodeGen* codeGen, LgsExpr* other);
    ~LgsExpr() override = default;
};

