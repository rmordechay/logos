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
    Value* getGEP(LgsCodeGen* codeGen, Value* instance) const;
    Value* getIRValue(LgsCodeGen* codeGen, LgsExpr* parentInstance);
    void storeIRValue(LgsCodeGen* codeGen, Value* instance, LgsExpr* value);
    Value* resolveVirtualField(LgsCodeGen* codeGen, LgsExpr* parentExpr) const;
    LgsField* clone() const;
    ~LgsField() override;
};
