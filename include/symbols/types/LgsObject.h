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
    string prettyName() const override;
    Type* getIRType(LgsModule* module) override;
    string getIRName() override;
    size_t getSizeBytes() override;
    void setVirtualFuncs(LgsModule* module);
    LgsExpr* getZeroValue() override;
    string getStrFormatPart() const override;
    bool equals(LgsType* other) override;
    ~LgsObject() override;
};


