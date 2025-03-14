#ifndef LOGOSARRAY_H
#define LOGOSARRAY_H

#include "LgsIterable.h"
#include "LogosUnaryExpr.h"
#include "LogosExpr.h"

class LgsArray final : public LgsUnaryExpr, public LgsIterable {
public:
    vector<LgsExpr*> elements;

    explicit LgsArray() : LgsUnaryExpr(nullptr) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    size_t size() override;
    ~LgsArray() override = default;
};

#endif //LOGOSARRAY_H
