#pragma once
#include "LgsUnaryExpr.h"
#include "types/LgsObject.h"

class LgsInstance final : public LgsUnaryExpr {
public:
    string name;
    LgsObject* obj = nullptr;

    map<string, LgsVarDec*> args;
    explicit LgsInstance(const string& name): name(name) {}
    explicit LgsInstance(LgsObject* obj) : LgsUnaryExpr(obj), name(obj->name), obj(obj) {}
    Value* createIRValue(LgsCodeGen* codeGen) override;
    void setObject(LgsObject* newObj);
    void setVirtuals(LgsCodeGen* codeGen) const;
    string prettyName() override;
    void initFields(LgsCodeGen* codeGen, const map<string, LgsField*>& fields);
    ~LgsInstance() override;
};
