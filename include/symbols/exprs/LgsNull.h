#ifndef LGSNULL_H
#define LGSNULL_H
#include "exprs/unary/LgsUnaryExpr.h"

class LgsNull final : public LgsUnaryExpr {
public:
    explicit LgsNull() : LgsUnaryExpr(nullptr) {
        isNull = true;
    }
    Value* createIRValue(Module* module) override;
    Value* addIR(Module* module, LgsExpr* other) override;
};

inline Value* LgsNull::createIRValue(Module* module) {
    return ConstantPointerNull::get(PointerType::get(context, 0));
}

inline Value* LgsNull::addIR(Module* module, LgsExpr* other) {
    assert(false && "not implemented");
}

#endif //LGSNULL_H
