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
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    Type* parentIRType = nullptr;
    bool isPublic = false;
    bool isVirtual = false;
    bool isOptional = false;

    LgsField(const string& name, string* parentName, LgsType* type, LgsExpr* expr = nullptr) : name(name), parentName(parentName), type(type), expr(expr) {}
    Value* getGEP(LgsModule* module, Value* instance) const;
    Value* getIRValue(LgsModule* module, LgsExpr* parentInstance) const;
    LgsField* clone() const;
    static void storeIRValue(LgsModule* module, Value* instance, LgsExpr* value);
    Value* resolveVirtualField(LgsModule* module, LgsExpr* parentExpr) const;
    ~LgsField() override;
};
