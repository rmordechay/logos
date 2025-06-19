#pragma once
#include "LgsUnaryExpr.h"
#include "exprs/LgsExpr.h"
#include "types/LgsArray.h"

class LgsArrayExpr final : public LgsUnaryExpr {
public:
    vector<LgsExpr*> elements;
    bool elementsAreStatic = false;

    explicit LgsArrayExpr(LgsType* baseType = nullptr) {
        type = new LgsArray(baseType);
    }
    explicit LgsArrayExpr(LgsArray* arrType) : LgsUnaryExpr(arrType) {}
    string prettyName() override;
    Value* createIRValue(LgsRuntime* runtime) override;
    Value* createConstArray(LgsRuntime* runtime) const;
    Constant* createIRConstArray(LgsRuntime* runtime, const vector<LgsExpr*>& elements) const;
    Value* createDynamicArray(LgsRuntime* runtime);
    void free(LgsRuntime* runtime) override;
    ~LgsArrayExpr() override = default;
};
