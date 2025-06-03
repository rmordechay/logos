#ifndef LOGOSARRAY_H
#define LOGOSARRAY_H

#include "LgsUnaryExpr.h"
#include "exprs/LgsExpr.h"
#include "types/LgsArray.h"

class LgsArrayExpr final : public LgsUnaryExpr {
public:
    LgsArray arrType;
    vector<LgsExpr*> initialElements;

    explicit LgsArrayExpr(LgsType* baseType = nullptr) {
        setType(&arrType);
        arrType.baseType = baseType;
    }
    Value* getLength(LgsRuntime* runtime) override;
    Value* createIRValue(LgsRuntime* runtime) override;
    Value* createConstArray(LgsRuntime* runtime) const;
    Value* createDynArray(LgsRuntime* runtime);
    void free(LgsRuntime* runtime) override;
    ~LgsArrayExpr() override = default;
};

#endif //LOGOSARRAY_H
