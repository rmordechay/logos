#pragma once
#include "LgsUnaryExpr.h"
#include "types/LgsObject.h"

class LgsInstance final : public LgsUnaryExpr {
public:
    string name;
    LgsObject* obj = nullptr;
    map<string, LgsVarDec*> args;

    explicit LgsInstance(LgsObject* obj) : LgsUnaryExpr(obj), name(obj->name), obj(obj) {}
    explicit LgsInstance(const string& name) : name(name) {}
    void setReturnExpr(LgsModule* module, Type* objIRType);
    void setZeroField(LgsModule* module, const LgsField* field, Value* parentIRValue) const;
    Value* createIRValue(LgsModule* module) override;
    string getExprName() override;
    string prettyName() override;
    void free(LgsModule* module) override;
    ~LgsInstance() override = default;
};
