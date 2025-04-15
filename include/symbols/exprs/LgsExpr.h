#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "LgsValue.h"
#include <types/LgsType.h>


class LgsVariable;
class LgsSelection;
class LgsInstance;
class LgsArrayIndex;
class LgsArray;
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

    explicit LgsExpr(LgsType* type) : type(type) {}
    Value* getIRValue(CodeGenMetadata* metadata);
    virtual LgsExpr* castStatically(LgsType* other);
    virtual uint32_t hashValue();
    virtual Value* createIRValue(CodeGenMetadata* metadata) = 0;
    virtual Value* addIR(CodeGenMetadata* metadata, LgsExpr* other) = 0;
    virtual Value* subIR(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* mulIR(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* divIR(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* eqIR(CodeGenMetadata* metadata, LgsExpr* other);

    bool isNull();
    LgsArray* asArray();
    LgsArrayIndex* asArrayIndex();
    LgsFuncCall* asFuncCall();
    LgsInstance* asInstance();
    LgsSelection* asSelection();
    LgsVariable* asVariable();
    LgsBoolConst* asBoolConst();
    LgsCharConst* asCharConst();
    LgsFloatConst* asFloatConst();
    LgsIntConst* asIntConst();
    LgsStrConst* asStrConst();
    LgsEnumField* asEnumField();
    LgsTypeConst* asTypeConst();
    ~LgsExpr() override = default;
};

#endif //LOGOSEXPR_H