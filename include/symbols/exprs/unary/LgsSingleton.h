#pragma once
#include "LgsUnaryExpr.h"
#include "types/LgsObject.h"

class LgsSingleton final : public LgsUnaryExpr {
public:
    string name;
    LgsObject* obj;
    explicit LgsSingleton(LgsObject* obj) : obj(obj) {
        auto symbolName = obj->name;
        symbolName[0] = tolower(symbolName[0]);
    }
    Value* createIRValue(LgsModule* module) override;
    string prettyName() override;
    ~LgsSingleton() override = default;
};
