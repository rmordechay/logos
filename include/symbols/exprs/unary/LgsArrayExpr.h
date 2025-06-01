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
    Value* getLength(CodegenMetadata* metadata) override;
    Value* createIRValue(CodegenMetadata* metadata) override;
    Value* createConstArray(CodegenMetadata* metadata) const;
    Value* createDynArray(CodegenMetadata* metadata);
    void free() override;
    ~LgsArrayExpr() override = default;
};

#endif //LOGOSARRAY_H
