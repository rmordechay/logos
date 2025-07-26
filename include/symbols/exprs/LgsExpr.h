#pragma once
#include "LgsValue.h"

class LgsPrefixExpr;
class LgsIterator;
class LgsPostfixExpr;
class LgsModule;
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
    BasicBlock* parentBlock = nullptr;

    explicit LgsExpr(LgsType* type) : type(type) {}
    Value* getIRValue(LgsModule* module);
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
    virtual void free(LgsModule* module);
    virtual Value* hashValue(LgsModule* module);
    virtual std::string prettyName() = 0;
    virtual Value* createIRValue(LgsModule* module) = 0;

    virtual Value* addIR(LgsModule* module, LgsExpr* other) = 0;
    virtual Value* subIR(LgsModule* module, LgsExpr* other);
    virtual Value* mulIR(LgsModule* module, LgsExpr* other);
    virtual Value* divIR(LgsModule* module, LgsExpr* other);
    virtual Value* modIR(LgsModule* module, LgsExpr* other);
    virtual Value* eqIR(LgsModule* module, LgsExpr* other);
    virtual Value* neIR(LgsModule* module, LgsExpr* other);
    virtual Value* ltIR(LgsModule* module, LgsExpr* other);
    virtual Value* gtIR(LgsModule* module, LgsExpr* other);
    virtual Value* geIR(LgsModule* module, LgsExpr* other);
    virtual Value* leIR(LgsModule* module, LgsExpr* other);
    virtual Value* andIR(LgsModule* module, LgsExpr* other);
    virtual Value* orIR(LgsModule* module, LgsExpr* other);
    virtual Value* bitAndIR(LgsModule* module, LgsExpr* other);
    virtual Value* bitOrIR(LgsModule* module, LgsExpr* other);
    virtual Value* bitXorIR(LgsModule* module, LgsExpr* other);
    virtual Value* rshiftIR(LgsModule* module, LgsExpr* other);
    virtual Value* lshiftIR(LgsModule* module, LgsExpr* other);
    ~LgsExpr() override = default;
};

