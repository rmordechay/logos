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
    bool isPublic = false;
    LgsExpr* expr = nullptr;
    LgsType* type = nullptr;

    LgsField(const string& name, string* parentName, LgsType* type, LgsExpr* expr = nullptr) : name(name), parentName(parentName), expr(expr), type(type) {}
    Value* getGEP(LgsModule* runtime, Type* parentType, Value* instance) const;
    void storeIRValue(LgsModule* runtime, Type* parentType, Value* parentIRValue, LgsExpr* expr) const;
    void setZeroValue(LgsModule* runtime, Type* parentType, Value* parentIRValue) const;
    ~LgsField() override;
};

