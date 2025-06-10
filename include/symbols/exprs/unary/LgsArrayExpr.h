#pragma once
#include "LgsUnaryExpr.h"
#include "exprs/LgsExpr.h"
#include "types/LgsArray.h"

class LgsArrayExpr final : public LgsUnaryExpr {
public:
    vector<LgsExpr*> initialElements;
    LgsArray* arrType = nullptr;

    explicit LgsArrayExpr(LgsType* baseType = nullptr) {
        arrType = new LgsArray(baseType);
        type = arrType;
    }
    explicit LgsArrayExpr(LgsArray* arrType) : LgsUnaryExpr(arrType) {}
    Value* createIRValue(LgsRuntime* runtime) override;
    Value* createConstArray(LgsRuntime* runtime) const;
    Value* createDynamicArray(LgsRuntime* runtime);
    void free(LgsRuntime* runtime) override;
    ~LgsArrayExpr() override = default;
};
