#ifndef LOGOSARRAY_H
#define LOGOSARRAY_H

#include "LgsUnaryExpr.h"
#include "exprs/LgsExpr.h"
#include "types/array/LgsArray.h"

#define INITIAL_ARRAY_SIZE 2

class LgsDArray final : public LgsUnaryExpr {
public:
    LgsArray arrType;
    vector<LgsExpr*> initialElements;

    explicit LgsDArray(LgsType* underlyingType = nullptr) {
        type = &arrType;
        arrType.underlyingType = underlyingType;
    }
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsDArray() override = default;
};

#endif //LOGOSARRAY_H
