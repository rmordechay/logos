#pragma once
#include "LgsUnaryExpr.h"
#include "types/LgsObject.h"

class LgsInstance final : public LgsUnaryExpr {
public:
    string name;
    LgsObject* obj = nullptr;
    vector<LgsVarDec*> args;

    explicit LgsInstance(LgsObject* obj) : LgsUnaryExpr(obj), name(obj->name), obj(obj) {}
    explicit LgsInstance(const string& name) : name(name) {}
    Value* createIRValue(LgsRuntime* runtime) override;
    void setZeroField(LgsRuntime* runtime, LgsField* field, Value* parentIRValue) const;
    void free(LgsRuntime* runtime) override;
    string getExprName() override;
    string prettyName() override;
    void setReturnExpr(LgsRuntime* runtime, Type* objIRType);
    ~LgsInstance() override = default;
};
