#pragma once
#include "exprs/LgsExpr.h"
#include "types/LgsNullable.h"

class LgsNull final : public LgsExpr {
public:
    explicit LgsNull() {
        setType(new LgsNullable(nullptr));
    }

    void castImplicitly(LgsType* toType) override;
    std::string asText() override;
    bool equals(LgsExpr* other) override;
    Value* castIR(LgsCgModule& cg, LgsType* toType) override;
    ~LgsNull() override;
};

