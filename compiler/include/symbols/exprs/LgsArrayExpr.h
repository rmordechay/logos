#pragma once
#include "exprs/LgsExpr.h"
#include "types/iterables/LgsDArray.h"
#include "types/iterables/LgsSArray.h"
#include "types/iterables/LgsSet.h"

class LgsArrayExpr final : public LgsExpr {
public:
    std::vector<LgsExpr*> elements;

    LgsArrayExpr() = default;
    explicit LgsArrayExpr(LgsSArray* arrType) : LgsExpr(arrType) {}
    explicit LgsArrayExpr(LgsDArray* arrType) : LgsExpr(arrType) {}
    explicit LgsArrayExpr(LgsSet* setType) : LgsExpr(setType) {}
    Value* loadIR(LgsCgModule& cg) override;
    void initIRArray(LgsCgModule& cg);
    void castImplicitly(LgsType* toType) override;
    void setDebugValue(LgsCgModule& cg) override;
    std::string asText() override;
    ~LgsArrayExpr() override;
};
