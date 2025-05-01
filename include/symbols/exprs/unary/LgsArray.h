#ifndef LOGOSARRAY_H
#define LOGOSARRAY_H

#include "LgsIterable.h"
#include "LgsUnaryExpr.h"
#include "exprs/LgsExpr.h"
#include "types/LgsArrayType.h"

class LgsArray final : public LgsUnaryExpr {
public:
    vector<LgsExpr*> initialElements;
    LgsIterable iterable;

    explicit LgsArray(const vector<LgsExpr*>& elements = {}) : LgsUnaryExpr(new LgsArrayType()), initialElements(elements) {
        iterable.length = elements.size();
        iterable.type = type;
        iterable.underlyingType = type;
        iterable.setFields();
    }
    size_t length() const;
    LgsArrayType* getArrayType() const;
    bool isIterable() override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void free(CodeGenMetadata* metadata) override;
    ~LgsArray() override = default;
};

#endif //LOGOSARRAY_H
