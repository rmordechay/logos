#pragma once
#include "LgsConstExpr.h"


class LgsFloatConst final : public LgsConstExpr {
public:
    double value;

    explicit LgsFloatConst(const float value) : LgsConstExpr(&LGS_FLOAT), value(value) {}
    Value* createIRValue(LgsRuntime* runtime) override;
    ~LgsFloatConst() override = default;
};


