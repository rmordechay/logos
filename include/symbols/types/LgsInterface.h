#pragma once
#include "LgsType.h"

class LgsInterface final : public LgsType {
public:
    string name;
    vector<LgsType*> interfaces;

    explicit LgsInterface(const string& name) : name(name) {}
    string prettyName() override;
    string getName() override;
    Type* getIRType(LgsCodeGen* codeGen) override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    size_t getSizeBytes() override;
    ~LgsInterface() override;
};
