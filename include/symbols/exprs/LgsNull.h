#ifndef LGSNULL_H
#define LGSNULL_H
#include "exprs/unary/LgsUnaryExpr.h"

class LgsNull final : public LgsUnaryExpr {
public:
    explicit LgsNull() : LgsUnaryExpr(nullptr) {
        isNull = true;
    }
    Value* createIRValue(CodegenMetadata* metadata) override;
    Value* addIR(CodegenMetadata* metadata, LgsExpr* other) override;
};

inline Value* LgsNull::createIRValue(CodegenMetadata* metadata) {
    return ConstantPointerNull::get(PointerType::get(context, 0));
}

inline Value* LgsNull::addIR(CodegenMetadata* metadata, LgsExpr* other) {
    assert(false && "not implemented");
}

#endif //LGSNULL_H
