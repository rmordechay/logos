#pragma once
#include "LgsUnaryExpr.h"
#include "types/LgsObject.h"

class LgsInstance final : public LgsUnaryExpr {
public:
    string name;
    LgsObject* obj = nullptr;
    map<string, LgsField*> fields;
    map<string, LgsVarDec*> args;

    explicit LgsInstance(LgsObject* obj) : LgsUnaryExpr(obj), name(obj->name), obj(obj) {}
    explicit LgsInstance(const string& name) : name(name) {}
    Value* createIRValue(LgsModule* module) override;
    void setVirtualFuncs(LgsModule* module) const;
    string getExprName() override;
    string prettyName() override;
    void free(LgsModule* module) override;
    ~LgsInstance() override;
};
