#ifndef LGSNULL_H
#define LGSNULL_H
#include "exprs/unary/LgsUnaryExpr.h"

class LgsNull final : public LgsUnaryExpr {
public:
    explicit LgsNull() : LgsUnaryExpr(nullptr) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* add(CodeGenMetadata* metadata, LgsExpr* other) override;
};

inline Value* LgsNull::createIRValue(CodeGenMetadata* metadata) {
    return ConstantPointerNull::get(PointerType::get(context, 0));
}

inline Value* LgsNull::add(CodeGenMetadata* metadata, LgsExpr* other) {
    assert(false && "not implemented");
}

#endif //LGSNULL_H
