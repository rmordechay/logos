#pragma once
#include "LgsConstExpr.h"


class LgsLongConst final : public LgsConstExpr {
public:
    long value;

    explicit LgsLongConst(const int value) : LgsConstExpr(&LGS_LONG), value(value) {}
    Value* createIRValue(LgsRuntime* runtime) override;
    ~LgsLongConst() override = default;
};




