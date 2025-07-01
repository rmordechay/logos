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
    Value* createIRValue(LgsModule* runtime) override;
    void setZeroField(LgsModule* runtime, const LgsField* field, Value* parentIRValue) const;
    void free(LgsModule* runtime) override;
    string getExprName() override;
    string prettyName() override;
    void setReturnExpr(LgsModule* runtime, Type* objIRType);
    ~LgsInstance() override = default;
};
