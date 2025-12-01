#pragma once
#include "exprs/LgsExpr.h"
#include "types/LgsNullable.h"

class LgsNull final : public LgsExpr {
public:
    LgsNull() {
        isMutable = false;
    }
    Value* loadIR(LgsCgModule& cg) override;
    void castImplicitly(LgsType* toType) override;
    std::string asText() override;
    bool equals(LgsExpr* other) override;
    void setDebugValue(LgsCgModule& cg) override;
    ~LgsNull() override;
};

