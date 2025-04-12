#ifndef LOGOSUNARYEXPR_H
#define LOGOSUNARYEXPR_H
#include "exprs/LgsExpr.h"

#include <string>
#include <types/LgsType.h>

class LgsUnaryExpr : public LgsExpr {
public:
    explicit LgsUnaryExpr() : LgsExpr(nullptr) {}
    explicit LgsUnaryExpr(LgsType* type) : LgsExpr(type) {}
    virtual string getName();
    Value* addIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* subIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* mulIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* divIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    virtual LgsExpr* add(LgsExpr* other);
    ~LgsUnaryExpr() override = default;
};

inline string LgsUnaryExpr::getName() {
    return "";
}

inline Value* LgsUnaryExpr::addIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto l = this->getIRValue(metadata);
    const auto r = other->getIRValue(metadata);
    return metadata->builder.CreateAdd(l, r);
}

inline Value* LgsUnaryExpr::subIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto l = this->getIRValue(metadata);
    const auto r = other->getIRValue(metadata);
    return metadata->builder.CreateSub(l, r);
}

inline Value* LgsUnaryExpr::mulIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto l = this->getIRValue(metadata);
    const auto r = other->getIRValue(metadata);
    return metadata->builder.CreateMul(l, r);
}

inline Value* LgsUnaryExpr::divIR(CodeGenMetadata* metadata, LgsExpr* other) {
    const auto l = this->getIRValue(metadata);
    const auto r = other->getIRValue(metadata);
    return metadata->builder.CreateSDiv(l, r);
}

inline LgsExpr* LgsUnaryExpr::add(LgsExpr* other) {
    return nullptr;
}

#endif //LOGOSUNARYEXPR_H
