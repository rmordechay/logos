#pragma once
#include "LgsValue.h"

class LgsEnum;
class LgsObject;
class LgsInstance;
class LgsType;
class LgsExpr;

class LgsField final : public LgsValue {
public:
    string name;
    size_t position = 0;
    string* parentName;
    bool isImmutable = false;
    bool isPublic = false;
    LgsExpr* expr = nullptr;
    LgsType* type = nullptr;

    LgsField(const string& name, string* parentName, LgsType* type, LgsExpr* expr = nullptr) : name(name), parentName(parentName), expr(expr), type(type) {}
    Value* getGEP(LgsRuntime* runtime, Type* parentType, Value* instance);
    void storeIRValue(LgsRuntime* runtime, Type* parentType, Value* parentIRValue, LgsExpr* expr);
    LgsField* clone() const;
    ~LgsField() override;
};

