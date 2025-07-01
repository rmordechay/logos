#pragma once
#include "LgsValue.h"

class LgsPrefixExpr;
class LgsIterator;
class LgsPostfixExpr;
class LgsModule;
class LgsEnumField;
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
    bool isStatic = false;
    // TODO removed from visitVariable. Should be inferred from some refs.
    bool isReturnExpr = false;

    explicit LgsExpr(LgsType* type) : type(type) {}
    Value* getIRValue(LgsModule* runtime);
    void setType(LgsType* type);
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
    LgsEnumField* asEnumField();
    LgsTypeConst* asTypeConst();

    virtual LgsExpr* clone();
    virtual bool equals(LgsExpr* other);
    virtual LgsExpr* convertExpr(LgsType* toType);
    virtual void free(LgsModule* runtime);
    virtual Value* hashValue(LgsModule* runtime);
    virtual std::string prettyName() = 0;
    virtual Value* createIRValue(LgsModule* runtime) = 0;

    virtual Value* addIR(LgsModule* runtime, LgsExpr* other) = 0;
    virtual Value* subIR(LgsModule* runtime, LgsExpr* other);
    virtual Value* mulIR(LgsModule* runtime, LgsExpr* other);
    virtual Value* divIR(LgsModule* runtime, LgsExpr* other);
    virtual Value* modIR(LgsModule* runtime, LgsExpr* other);
    virtual Value* eqIR(LgsModule* runtime, LgsExpr* other);
    virtual Value* neIR(LgsModule* runtime, LgsExpr* other);
    virtual Value* ltIR(LgsModule* runtime, LgsExpr* other);
    virtual Value* gtIR(LgsModule* runtime, LgsExpr* other);
    virtual Value* geIR(LgsModule* runtime, LgsExpr* other);
    virtual Value* leIR(LgsModule* runtime, LgsExpr* other);
    virtual Value* andIR(LgsModule* runtime, LgsExpr* other);
    virtual Value* orIR(LgsModule* runtime, LgsExpr* other);
    virtual Value* bitAndIR(LgsModule* runtime, LgsExpr* other);
    virtual Value* bitOrIR(LgsModule* runtime, LgsExpr* other);
    virtual Value* bitXorIR(LgsModule* runtime, LgsExpr* other);
    virtual Value* rshiftIR(LgsModule* runtime, LgsExpr* other);
    virtual Value* lshiftIR(LgsModule* runtime, LgsExpr* other);
    ~LgsExpr() override = default;
};

