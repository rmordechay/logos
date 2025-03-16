#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "LgsValue.h"
#include <LgsType.h>

class LgsExpr: virtual public LgsValue {
public:
    LgsType* type = nullptr;

    explicit LgsExpr(LgsType* type) : type(type) {}
    virtual Value* add(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* sub(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* mul(CodeGenMetadata* metadata, LgsExpr* other);
    virtual Value* div(CodeGenMetadata* metadata, LgsExpr* other);
    ~LgsExpr() override = default;
};

inline Value* LgsExpr::add(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto l = this->getIRValue(metadata);
    const auto r = other->getIRValue(metadata);
    return metadata->builder.CreateAdd(l, r);
}

inline Value* LgsExpr::sub(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto l = this->getIRValue(metadata);
    const auto r = other->getIRValue(metadata);
    return metadata->builder.CreateSub(l, r);
}

inline Value* LgsExpr::mul(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto l = this->getIRValue(metadata);
    const auto r = other->getIRValue(metadata);
    return metadata->builder.CreateMul(l, r);
}

inline Value* LgsExpr::div(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto l = this->getIRValue(metadata);
    const auto r = other->getIRValue(metadata);
    return metadata->builder.CreateSDiv(l, r);
}

#endif //LOGOSEXPR_H

