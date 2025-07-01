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
    Value* createIRValue(LgsModule* runtime) override;
    Value* createConstArray(LgsModule* runtime) const;
    Constant* createIRConstArray(LgsModule* runtime, const vector<LgsExpr*>& elements) const;
    Value* createDynamicArray(LgsModule* runtime);
    void free(LgsModule* runtime) override;
    ~LgsArrayExpr() override = default;
};
