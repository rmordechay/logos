#pragma once

#include "LgsUnaryExpr.h"
#include "exprs/LgsExpr.h"
#include "types/LgsArray.h"

class LgsArrayExpr final : public LgsUnaryExpr {
public:
    LgsArray arrType;
    vector<LgsExpr*> initialElements;
    LgsFunc* initArgsFunc = nullptr;

    explicit LgsArrayExpr(LgsType* baseType = nullptr) {
        setType(&arrType);
        arrType.baseType = baseType;
    }
    Value* createIRValue(LgsRuntime* runtime) override;
    Value* createConstArray(LgsRuntime* runtime) const;
    Value* createDynamicArray(LgsRuntime* runtime);
    void free(LgsRuntime* runtime) override;
    ~LgsArrayExpr() override = default;
};
