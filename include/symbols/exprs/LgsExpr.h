#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "LgsValue.h"
#include <LgsType.h>

class LgsExpr: virtual public LgsValue {
public:
    LgsType* type = nullptr;

    explicit LgsExpr(LgsType* type) : type(type) {}
    virtual Value* add(CodeGenMetadata* metadata, LgsExpr* other) = 0;
    virtual Value* sub(CodeGenMetadata* metadata, LgsExpr* other) = 0;
    virtual Value* mul(CodeGenMetadata* metadata, LgsExpr* other) = 0;
    virtual Value* div(CodeGenMetadata* metadata, LgsExpr* other) = 0;
    virtual Value* gt(CodeGenMetadata* metadata, LgsExpr* other) = 0;
    virtual Value* lt(CodeGenMetadata* metadata, LgsExpr* other) = 0;
    virtual Value* eq(CodeGenMetadata* metadata, LgsExpr* other) = 0;
    virtual Value* ne(CodeGenMetadata* metadata, LgsExpr* other) = 0;
    virtual Value* le(CodeGenMetadata* metadata, LgsExpr* other) = 0;
    virtual Value* ge(CodeGenMetadata* metadata, LgsExpr* other) = 0;

    ~LgsExpr() override = default;
};

#endif //LOGOSEXPR_H

