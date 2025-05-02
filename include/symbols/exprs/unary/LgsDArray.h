#ifndef LOGOSARRAY_H
#define LOGOSARRAY_H

#include "LgsUnaryExpr.h"
#include "exprs/LgsExpr.h"
#include "types/LgsDArrType.h"

class LgsDArray final : public LgsUnaryExpr {
public:
    vector<LgsExpr*> initialElements;

    explicit LgsDArray(LgsType* underlyingType, const vector<LgsExpr*>& initialElements = {}) : initialElements(initialElements) {
        type = new LgsDArrType(underlyingType);
    }
    size_t length() const;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void free(CodeGenMetadata* metadata) override;
    ~LgsDArray() override = default;
};

#endif //LOGOSARRAY_H
