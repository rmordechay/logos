#ifndef LOGOSARRAY_H
#define LOGOSARRAY_H

#include "LgsIterable.h"
#include "LgsUnaryExpr.h"
#include "exprs/LgsExpr.h"
#include "types/LgsArrayType.h"
#include "types/LgsVoid.h"

class LgsArray final : public LgsUnaryExpr, public LgsIterable {
public:
    vector<LgsExpr*> initialElements;

    explicit LgsArray(LgsType* type, const vector<LgsExpr*>& elements = {}) : LgsUnaryExpr(type), initialElements(elements) {
        setFields(type);
    }
    size_t size() override;
    Value* sizeIR(CodeGenMetadata* metadata) override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void free(CodeGenMetadata* metadata) override;
    LgsArrayType* asArrayType() const;
    ~LgsArray() override = default;
};

#endif //LOGOSARRAY_H
