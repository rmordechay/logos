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
    Value* getLength(Module* module) override;
    Value* createIRValue(Module* module) override;
    Value* createConstArray(Module* module) const;
    Value* createDynArray(Module* module);
    void free(Module* module) override;
    ~LgsArrayExpr() override = default;
};

#endif //LOGOSARRAY_H
