#pragma once
#include "LgsConstExpr.h"


class LgsCharConst final : public LgsConstExpr {
public:
    char value;

    explicit LgsCharConst(const char value) : LgsConstExpr(&LGS_CHAR), value(value) {}
    Value* createIRValue(LgsRuntime* runtime) override;
};


