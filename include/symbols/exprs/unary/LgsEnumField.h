#pragma once
#include "stmts/LgsField.h"

class LgsEnum;

class LgsEnumField final : public LgsField {
public:
    std::string text;
    LgsEnum* parent;

    LgsEnumField(LgsEnum* parent, const std::string& name, const std::string& text) : LgsField(name, nullptr, nullptr), text(text), parent(parent){}
    Value* getGEP(LgsRuntime* runtime, Value* instance = nullptr) override;
    ~LgsEnumField() override = default;
};


