#ifndef LGSSARRAY_H
#define LGSSARRAY_H
#include "LgsUnaryExpr.h"
#include "types/array/LgsArray.h"

class LgsSArray final : public LgsUnaryExpr {
public:
    LgsArray arrType;
    vector<LgsExpr*> initialElements;

    explicit LgsSArray(LgsType* baseType = nullptr) {
        type = &arrType;
        arrType.isStatic = true;
        arrType.baseType = baseType;
    }
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsSArray() override = default;
};

#endif //LGSSARRAY_H
