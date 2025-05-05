#ifndef LOGOSARRAY_H
#define LOGOSARRAY_H

#include "LgsUnaryExpr.h"
#include "exprs/LgsExpr.h"
#include "types/LgsArray.h"

class LgsDArray final : public LgsUnaryExpr {
public:
    LgsArray arrType;
    vector<LgsExpr*> initialElements;

    explicit LgsDArray(LgsType* underlyingType) {
        arrType.underlyingType = underlyingType;
        type = &arrType;
    }
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsDArray() override = default;
};

#endif //LOGOSARRAY_H
