#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "LgsValue.h"
#include <types/LgsType.h>


class LgsBoolConst;
class LgsCharConst;
class LgsFloatConst;
class LgsIntConst;
class LgsStrConst;
class LgsTypeConst;

class LgsExpr : virtual public LgsValue {
public:
    LgsType* type = nullptr;

    explicit LgsExpr(LgsType* type) : type(type) {}
    Value* getIRValue(CodeGenMetadata* metadata);
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
    LgsTypeConst* asTypeConst();
    virtual Value* createIRValue(CodeGenMetadata* metadata) = 0;
    virtual Value* addIR(CodeGenMetadata* metadata, LgsExpr* other) = 0;
    virtual Value* sub(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* mul(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* div(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* eqIR(CodeGenMetadata* metadata, LgsExpr* other);
    ~LgsExpr() override = default;
};

#endif //LOGOSEXPR_H
