#pragma once
#include "LgsUnaryExpr.h"
#include "exprs/LgsExpr.h"
#include "types/LgsArray.h"

class LgsArrayExpr final : public LgsUnaryExpr {
public:
    LgsArray* arrType = nullptr;
    vector<LgsExpr*> initialElements;

    explicit LgsArrayExpr(LgsType* baseType = nullptr) {
        arrType = new LgsArray(baseType);
        type = arrType;
    }
    explicit LgsArrayExpr(LgsArray* arrType) : LgsUnaryExpr(arrType), arrType(arrType) {}
    string prettyName() override;
    Value* createIRValue(LgsRuntime* runtime) override;
    Value* createConstArray(LgsRuntime* runtime) const;
    Value* createDynamicArray(LgsRuntime* runtime);
    void free(LgsRuntime* runtime) override;
    ~LgsArrayExpr() override = default;
};
