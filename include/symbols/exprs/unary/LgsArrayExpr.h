#pragma once
#include "LgsUnaryExpr.h"
#include "exprs/LgsExpr.h"
#include "types/LgsArray.h"

class LgsArrayExpr final : public LgsUnaryExpr {
public:
    vector<LgsExpr*> initialElements;

    explicit LgsArrayExpr(LgsType* baseType = nullptr) {
        type = new LgsArray(baseType);
    }
    explicit LgsArrayExpr(LgsArray* arrType) : LgsUnaryExpr(arrType) {}
    string prettyName() override;
    Value* createIRValue(LgsRuntime* runtime) override;
    Value* createConstArray(LgsRuntime* runtime) const;
    Constant* createInnerConstArray(LgsRuntime* runtime) const;
    Value* createDynamicArray(LgsRuntime* runtime);
    void free(LgsRuntime* runtime) override;
    ~LgsArrayExpr() override = default;
};
