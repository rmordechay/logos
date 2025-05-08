#ifndef LGSSARRAY_H
#define LGSSARRAY_H
#include "LgsUnaryExpr.h"
#include "types/LgsArray.h"

class LgsSArray final : public LgsUnaryExpr {
public:
    LgsArray arrType;
    vector<LgsExpr*> initialElements;

    explicit LgsSArray(LgsType* underlyingType = nullptr) {
        type = &arrType;
        arrType.isStaticIter = true;
        arrType.underlyingType = underlyingType;
    }
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsSArray() override = default;
};

#endif //LGSSARRAY_H
