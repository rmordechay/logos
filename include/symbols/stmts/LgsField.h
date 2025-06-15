#pragma once
#include "LgsValue.h"
#include "types/LgsEnum.h"
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
    string* parentName;
    bool isImmutable = false;
    bool isPublic = false;
    LgsExpr* expr = nullptr;
    LgsType* type = nullptr;

    LgsField(const string& name, string* parentName, LgsType* type, LgsExpr* expr = nullptr) : name(name), parentName(parentName), expr(expr), type(type) {}
    virtual Value* getGEP(LgsRuntime* runtime, Type* parentType, Value* instance);
    void storeIRValue(LgsRuntime* runtime, Type* parentType, Value* parentIRValue, LgsExpr* expr);
    LgsField* clone() const;
    ~LgsField() override;
};

class LgsEnumField final : public LgsField {
public:
    string text;
    LgsEnum* parent;

    LgsEnumField(LgsEnum* parent, const string& name, const string& text) : LgsField(name, &parent->name, parent, nullptr), text(text), parent(parent){}
    Value* getGEP(LgsRuntime* runtime, Type* parentType, Value* instance) override {
        return getIRStr(runtime, name);
    }

    ~LgsEnumField() override = default;
};
