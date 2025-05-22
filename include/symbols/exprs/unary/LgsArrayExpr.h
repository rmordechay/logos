#ifndef LOGOSARRAY_H
#define LOGOSARRAY_H

#include "LgsUnaryExpr.h"
#include "exprs/LgsExpr.h"
#include "types/array/LgsArray.h"

class LgsArrayExpr final : public LgsUnaryExpr {
public:
    LgsArray arrType;
    vector<LgsExpr*> initialElements;

    explicit LgsArrayExpr(LgsType* baseType = nullptr) {
        setType(&arrType);
        arrType.baseType = baseType;
    }
    Value* getLength(CodeGenMetadata* metadata) override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* createConstArray(CodeGenMetadata* metadata) const;
    Value* createDynArray(CodeGenMetadata* metadata);
    ~LgsArrayExpr() override = default;
};

#endif //LOGOSARRAY_H
