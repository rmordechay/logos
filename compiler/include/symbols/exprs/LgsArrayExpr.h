#pragma once
#include "exprs/LgsExpr.h"
#include "types/iterables/LgsDArray.h"
#include "types/iterables/LgsSArray.h"
#include "types/iterables/LgsSet.h"

class LgsArrayExpr final : public LgsExpr {
public:
    LgsIterable* iterable = nullptr;
    std::vector<LgsExpr*> elements;

    LgsArrayExpr() = default;
    explicit LgsArrayExpr(LgsSArray* arrType) {
        setType(arrType);
    }
    explicit LgsArrayExpr(LgsDArray* arrType) {
        setType(arrType);
    }

    LgsExpr* cast(LgsType* toType, bool explicitly) override;
    void setType(LgsType* newType) override;
    void setDebugValue(LgsCodeGen& cg) override;
    std::string asText() override;
    LgsExpr* clone() override;
    ~LgsArrayExpr() override;
};
