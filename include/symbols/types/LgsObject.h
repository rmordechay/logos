#pragma once
#include "LgsType.h"

class LgsModule;
class LgsField;

class LgsObject final : public LgsType {
public:
    string name;
    bool isSingleton = false;
    vector<LgsType*> interfaces;

    explicit LgsObject(const string& name) : name(name) {}
    string prettyName() override;
    Type* getIRType(LgsModule* module) override;
    string getName() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    string getStrFormatPart() const override;
    bool equals(LgsType* other) override;
    ~LgsObject() override;
};


