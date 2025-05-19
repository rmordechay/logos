#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "LgsValue.h"

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
    bool isReturnValue = false;
    bool isNull = false;

    explicit LgsExpr(LgsType* type) : type(type) {}
    Value* getIRValue(CodeGenMetadata* metadata);
    void initIRValue(CodeGenMetadata* metadata);
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

    virtual string prettyName();
    virtual LgsExpr* convertExpr(LgsType* type);
    virtual Value* getLength(CodeGenMetadata* metadata);
    virtual uint32_t hashValue(CodeGenMetadata* metadata);
    virtual Value* createIRValue(CodeGenMetadata* metadata) = 0;
    virtual Value* addIR(CodeGenMetadata* metadata, LgsExpr* other) = 0;
    virtual Value* subIR(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* mulIR(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* divIR(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* eqIR(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* neIR(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* ltIR(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* gtIR(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* geIR(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* leIR(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* andIR(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* orIR(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* bitAndIR(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* bitOrIR(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* bitXorIR(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* rshiftIR(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* lshiftIR(CodeGenMetadata* metadata, LgsExpr* other);
    virtual LgsExpr* clone();
    ~LgsExpr() override = default;
};

#endif //LOGOSEXPR_H