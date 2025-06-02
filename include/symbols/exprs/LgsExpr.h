#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "LgsValue.h"

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
    // TODO free type
    LgsType* type = nullptr;
    bool isNull = false;

    explicit LgsExpr(LgsType* type) : type(type) {}
    Value* getIRValue(Module* module);
    void setType(LgsType* type);

    LgsFunc* asFunc();
    LgsVariable* asVariable();
    LgsFuncCall* asFuncCall();
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

    virtual void free(Module* module);
    virtual LgsExpr* clone();
    virtual std::string prettyName();
    virtual LgsExpr* convertExpr(LgsType* type);
    virtual Value* getLength(Module* module);
    virtual uint32_t hashValue(Module* module);
    virtual Value* createIRValue(Module* module) = 0;
    virtual Value* addIR(Module* module, LgsExpr* other) = 0;
    virtual Value* subIR(Module* module, LgsExpr* other);
    virtual Value* mulIR(Module* module, LgsExpr* other);
    virtual Value* divIR(Module* module, LgsExpr* other);
    virtual Value* eqIR(Module* module, LgsExpr* other);
    virtual Value* neIR(Module* module, LgsExpr* other);
    virtual Value* ltIR(Module* module, LgsExpr* other);
    virtual Value* gtIR(Module* module, LgsExpr* other);
    virtual Value* geIR(Module* module, LgsExpr* other);
    virtual Value* leIR(Module* module, LgsExpr* other);
    virtual Value* andIR(Module* module, LgsExpr* other);
    virtual Value* orIR(Module* module, LgsExpr* other);
    virtual Value* bitAndIR(Module* module, LgsExpr* other);
    virtual Value* bitOrIR(Module* module, LgsExpr* other);
    virtual Value* bitXorIR(Module* module, LgsExpr* other);
    virtual Value* rshiftIR(Module* module, LgsExpr* other);
    virtual Value* lshiftIR(Module* module, LgsExpr* other);
    virtual ~LgsExpr() override = default;
};

#endif //LOGOSEXPR_H