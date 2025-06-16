#pragma once
#include "LgsValue.h"

class LgsIterator;
class LgsPostfixExpr;
class LgsRuntime;
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
    bool isImmutable = false;
    // TODO removed from visitVariable. Should be inferred from some refs.
    bool isReturnExpr = false;

    explicit LgsExpr(LgsType* type) : type(type) {}
    Value* getIRValue(LgsRuntime* runtime);
    void setType(LgsType* type);
    int getConstInt();
    string getConstStr();
    LgsIterator toIterator();

    LgsFunc* asFunc();
    LgsVariable* asVariable();
    LgsFuncCall* asFuncCall();
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
    virtual void free(LgsRuntime* runtime);
    virtual uint32_t hashValue(LgsRuntime* runtime);
    virtual std::string pName() = 0;
    virtual Value* createIRValue(LgsRuntime* runtime) = 0;

    virtual Value* addIR(LgsRuntime* runtime, LgsExpr* other) = 0;
    virtual Value* subIR(LgsRuntime* runtime, LgsExpr* other);
    virtual Value* mulIR(LgsRuntime* runtime, LgsExpr* other);
    virtual Value* divIR(LgsRuntime* runtime, LgsExpr* other);
    virtual Value* modIR(LgsRuntime* runtime, LgsExpr* other);
    virtual Value* eqIR(LgsRuntime* runtime, LgsExpr* other);
    virtual Value* neIR(LgsRuntime* runtime, LgsExpr* other);
    virtual Value* ltIR(LgsRuntime* runtime, LgsExpr* other);
    virtual Value* gtIR(LgsRuntime* runtime, LgsExpr* other);
    virtual Value* geIR(LgsRuntime* runtime, LgsExpr* other);
    virtual Value* leIR(LgsRuntime* runtime, LgsExpr* other);
    virtual Value* andIR(LgsRuntime* runtime, LgsExpr* other);
    virtual Value* orIR(LgsRuntime* runtime, LgsExpr* other);
    virtual Value* bitAndIR(LgsRuntime* runtime, LgsExpr* other);
    virtual Value* bitOrIR(LgsRuntime* runtime, LgsExpr* other);
    virtual Value* bitXorIR(LgsRuntime* runtime, LgsExpr* other);
    virtual Value* rshiftIR(LgsRuntime* runtime, LgsExpr* other);
    virtual Value* lshiftIR(LgsRuntime* runtime, LgsExpr* other);
    ~LgsExpr() override = default;
};

