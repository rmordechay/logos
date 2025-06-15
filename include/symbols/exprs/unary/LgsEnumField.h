#pragma once
#include "data/LgsDefinitions.h"
#include "exprs/unary/LgsUnaryExpr.h"

class LgsEnumField : public LgsUnaryExpr {
public:
    string name;
    string text;

    LgsEnumField(LgsType* type, const string& name, const string& text) : LgsUnaryExpr(type), name(name), text(text) {}
    Value* createIRValue(LgsRuntime* runtime) override;
    ~LgsEnumField() override = default;
};

class LgsDefaultEnumField final : public LgsEnumField {
public:
    explicit LgsDefaultEnumField(LgsType* type) : LgsEnumField(type, LOGOS_DEFAULT_ENUM, "") {}
    ~LgsDefaultEnumField() override = default;
};