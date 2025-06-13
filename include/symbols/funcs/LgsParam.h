#pragma once
#include "exprs/LgsExpr.h"

#include <LgsValue.h>

class LgsVariable;
class LgsExpr;
class LgsType;

class LgsParam final : public LgsValue {
public:
    string name;
    uint32_t position = 0;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    bool isSelf = false;
    bool isVariadic = false;
    AllocaInst* vaList = nullptr;
    vector<LgsVariable*> refs;

    explicit LgsParam(LgsType* type = nullptr, const string& name = "", LgsExpr* expr = nullptr) : name(name), type(type), expr(expr) {
        isConst = true;
    }
    string format(string& indentStr) override;
    Value* getIRValue(LgsRuntime* runtime);
    string getIRName();
    ~LgsParam() override;
};
