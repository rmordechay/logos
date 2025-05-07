#ifndef LGSNULL_H
#define LGSNULL_H
#include "exprs/unary/LgsUnaryExpr.h"

class LgsNull final : public LgsUnaryExpr {
public:
    explicit LgsNull() : LgsUnaryExpr(nullptr) {
        isNull = true;
    }
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* addIR(CodeGenMetadata* metadata, LgsExpr* other) override;
};

inline Value* LgsNull::createIRValue(CodeGenMetadata* metadata) {
    return ConstantPointerNull::get(PointerType::get(context, 0));
}

inline Value* LgsNull::addIR(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "not implemented");
}

#endif //LGSNULL_H
