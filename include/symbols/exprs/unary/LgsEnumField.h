#pragma once
#include "data/LgsDefinitions.h"
#include "exprs/unary/LgsUnaryExpr.h"
#include "utils/LgsUtils.h"

class LgsEnumField : public LgsUnaryExpr {
public:
    string name;
    string text;

    LgsEnumField(LgsType* type, const string& name, const string& text) : LgsUnaryExpr(type), name(name), text(text) {}
    Value* createIRValue(LgsRuntime* runtime) override;
    string prettyName() override;
    ~LgsEnumField() override = default;
};

