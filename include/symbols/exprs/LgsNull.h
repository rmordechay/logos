#ifndef LGSNULL_H
#define LGSNULL_H
#include "exprs/unary/LgsUnaryExpr.h"

class LgsNull final : public LgsUnaryExpr {
public:
    explicit LgsNull() : LgsUnaryExpr(nullptr) {
        isNull = true;
    }
    Value* createIRValue(LgsRuntime* runtime) override;
};

inline Value* LgsNull::createIRValue(LgsRuntime* runtime) {
    return ConstantPointerNull::get(PointerType::get(context, 0));
}

#endif //LGSNULL_H
