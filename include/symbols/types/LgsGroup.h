#pragma once

#include "exprs/unary/LgsHashMap.h"

class LgsVariable;

class LgsGroup final : public LgsType {
public:
    std::string name;
    std::vector<LgsType*> types;
    std::vector<LgsVariable*> targetSymbols;

    explicit LgsGroup(const std::string& name) : name(name) {}
    Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    std::string pname() override;
    size_t getSizeBytes() override;
    bool equals(LgsType* other) override;

};



