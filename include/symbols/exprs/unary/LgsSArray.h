#ifndef LGSSARRAY_H
#define LGSSARRAY_H
#include "LgsUnaryExpr.h"
#include "types/array/LgsArray.h"

class LgsSArray final : public LgsUnaryExpr {
public:
    LgsArray arrType;
    vector<LgsExpr*> initialElements;

    explicit LgsSArray(LgsType* underlyingType = nullptr) {
        type = &arrType;
        arrType.isStatic = true;
        arrType.underlyingType = underlyingType;
    }
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsSArray() override = default;
};

#endif //LGSSARRAY_H
