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
    string* parentName;
    size_t position = 0;
    bool isPublic = false;
    bool isVirtual = false;
    bool isOptional = false;
    LgsExpr* expr = nullptr;
    LgsType* type = nullptr;
    Type* parentIRType = nullptr;
    Value* parentIRValue = nullptr;

    LgsField(const string& name, string* parentName, LgsType* type, LgsExpr* expr = nullptr) : name(name), parentName(parentName), expr(expr), type(type) {}
    Value* getGEP(LgsModule* module) const;
    void storeIRValue(LgsModule* module, LgsExpr* value) const;
    void setZeroValue(LgsModule* module) const;
    LgsField* clone() const;
    ~LgsField() override;
};
