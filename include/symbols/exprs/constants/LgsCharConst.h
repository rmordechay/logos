#pragma once
#include "exprs/LgsExpr.h"
#include "types/primitives/LgsChar.h"

class LgsCharConst final : public LgsExpr {
public:
    char value;
    explicit LgsCharConst(const char value) : LgsExpr(&LGS_CHAR), value(value) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    std::string asText() override;
};


