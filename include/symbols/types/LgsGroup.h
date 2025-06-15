#pragma once

#include "exprs/unary/LgsHashMap.h"

class LgsVariable;

class LgsGroup final : public LgsType {
public:
    string name;
    vector<LgsType*> types;
    vector<LgsVariable*> targetSymbols;

    explicit LgsGroup(const string& name) : name(name) {}
    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    string pName() const override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;

};



