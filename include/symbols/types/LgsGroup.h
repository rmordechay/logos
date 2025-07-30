#pragma once

#include "exprs/unary/LgsHashMap.h"

class LgsVariable;

class LgsGroup final : public LgsType {
public:
    string name;
    vector<LgsType*> types;
    vector<LgsVariable*> targetSymbols;

    explicit LgsGroup(const string& name) : name(name) {}
    Type* getIRType(LgsCodeGen* codeGen) override;
    string getName() override;
    LgsExpr* getZeroValue() override;
    string prettyName() override;
    bool equals(LgsType* other) override;

};



