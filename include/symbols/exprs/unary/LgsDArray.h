#ifndef LOGOSARRAY_H
#define LOGOSARRAY_H

#include "LgsUnaryExpr.h"
#include "exprs/LgsExpr.h"
#include "types/LgsArrayType.h"

class LgsDArray final : public LgsUnaryExpr {
public:
    LgsArrayType arrType;
    vector<LgsExpr*> initialElements;

    explicit LgsDArray(LgsType* underlyingType, const vector<LgsExpr*>& initialElements = {}) : initialElements(initialElements) {
        arrType.sizes.emplace_back(initialElements.size());
        arrType.underlyingType = underlyingType;
        type = &arrType;
    }
    size_t length() const;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void free(CodeGenMetadata* metadata) override;
    ~LgsDArray() override = default;
};

#endif //LOGOSARRAY_H
