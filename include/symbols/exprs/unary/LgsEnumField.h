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

class LgsDefaultEnumField final : public LgsEnumField {
public:
    uint32_t hashedValue;

    explicit LgsDefaultEnumField(LgsType* type) : LgsEnumField(type, LOGOS_DEFAULT_ENUM, "") {
        hashedValue = hashString(LOGOS_DEFAULT_ENUM);
    }
    uint32_t hashValue(LgsRuntime* runtime) override;
    ~LgsDefaultEnumField() override = default;
};
