#pragma once
#include "exprs/LgsExpr.h"
#include "types/LgsNullable.h"

class LgsNull final : public LgsExpr {
public:
    explicit LgsNull() {
        type = new LgsNullable(nullptr);
        isMutable = false;
    }
    std::string asText() override;
    ~LgsNull() override;
};

