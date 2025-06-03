#ifndef LGSNULL_H
#define LGSNULL_H
#include "exprs/unary/LgsUnaryExpr.h"

class LgsNull final : public LgsUnaryExpr {
public:
    explicit LgsNull() : LgsUnaryExpr(nullptr) {
        isNull = true;
    }
    Value* createIRValue(LgsRuntime* runtime) override;
    Value* addIR(LgsRuntime* runtime, LgsExpr* other) override;
};

inline Value* LgsNull::createIRValue(LgsRuntime* runtime) {
    return ConstantPointerNull::get(PointerType::get(context, 0));
}

inline Value* LgsNull::addIR(LgsRuntime* runtime, LgsExpr* other) {
    assert(false && "not implemented");
}

#endif //LGSNULL_H
