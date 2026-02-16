#pragma once
#include "exprs/LgsExpr.h"
#include "types/primitives/LgsChar.h"

class LgsCharConst final : public LgsExpr {
public:
    char value;
    explicit LgsCharConst(const char value) : LgsExpr(&LGS_CHAR), value(value) {}
    std::string asText() override;
    LgsExpr* cast(LgsType* toType, bool explicitly) override;
    void setDebugValue(LgsCodeGen& cg) override;
};
