#pragma once
#include "LgsUnaryExpr.h"
#include "types/LgsObject.h"

class LgsInstance final : public LgsUnaryExpr {
public:
    LgsObject* obj = nullptr;
    map<string, LgsField*> fields;
    map<string, LgsVarDec*> args;

    LgsInstance() = default;
    explicit LgsInstance(LgsObject* obj) : LgsUnaryExpr(obj), obj(obj) {
        copyFields();
    }
    Value* createIRValue(LgsModule* module) override;
    Value* createSingletonIRValue(LgsModule* module) const;
    void setVirtualFuncs(LgsModule* module) const;
    string getName() override;
    string prettyName() override;
    void copyFields();
    void free(LgsModule* module) override;
    ~LgsInstance() override;
};
