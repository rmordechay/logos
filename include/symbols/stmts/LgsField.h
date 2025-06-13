#pragma once
#include "LgsValue.h"
#include "utils/LgsUtils.h"

class LgsEnum;
class LgsObject;
class LgsInstance;
class LgsType;
class LgsExpr;

class LgsField : public LgsValue {
public:
    string name;
    size_t position = 0;
    bool isPublic = false;
    bool isConst = false;
    LgsExpr* expr = nullptr;
    LgsType* type = nullptr;
    LgsObject* parent = nullptr;

    LgsField(const string& name, LgsType* type, LgsExpr* expr = nullptr) : name(name), expr(expr), type(type) {}
    virtual Value* getGEP(LgsRuntime* runtime, Value* instance);
    void storeIRValue(LgsRuntime* runtime, Value* parentIRValue, LgsExpr* expr);
    LgsField* clone() const;
    ~LgsField() override;
};

class LgsEnumField final : public LgsField {
public:
    string text;
    LgsEnum* parent;

    LgsEnumField(LgsEnum* parent, const string& name, const string& text) : LgsField(name, nullptr, nullptr), text(text), parent(parent){}
    Value* getGEP(LgsRuntime* runtime, Value* instance) override {
        return getIRStr(runtime, name);
    }

    ~LgsEnumField() override = default;
};
