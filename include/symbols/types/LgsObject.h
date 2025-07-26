#pragma once
#include "LgsType.h"

class LgsInstance;
class LgsModule;
class LgsField;

class LgsObject final : public LgsType {
public:
    string name;
    bool hasVirtuals = false;
    vector<LgsType*> interfaces;
    LgsInstance* singleton = nullptr;

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
