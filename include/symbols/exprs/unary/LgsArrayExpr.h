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
    Value* createIRValue(LgsModule* module) override;
    Value* createConstArray(LgsModule* module) const;
    Constant* createIRConstArray(LgsModule* module, const vector<LgsExpr*>& elements) const;
    Value* createDynamicArray(LgsModule* module);
    void free(LgsModule* module) override;
    ~LgsArrayExpr() override = default;
};
