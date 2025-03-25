#ifndef LOGOSARRAY_H
#define LOGOSARRAY_H

#include "LgsIterable.h"
#include "LgsUnaryExpr.h"
#include "exprs/LgsExpr.h"

class LgsArray final : public LgsUnaryExpr, public LgsIterable {
public:
    vector<LgsExpr*> elements;

    explicit LgsArray() : LgsUnaryExpr(nullptr) {}
    explicit LgsArray(LgsType* type) : LgsUnaryExpr(type) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    size_t size() override;
    ~LgsArray() override = default;
};

#endif //LOGOSARRAY_H
