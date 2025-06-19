#pragma once
#include "LgsType.h"

class LgsRuntime;
class LgsField;

class LgsObject : public LgsType {
public:
    string name;
    bool isSingleton = false;
    vector<LgsType*> interfaces;

    explicit LgsObject(const string& name) : name(name) {}
    LgsInterface* getInterface(const string& interfaceName) const;
    string prettyName() const override;
    Type* getIRType() override;
    string getIRName() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    string getStrFormatPart() const override;
    void setVFuncs(LgsRuntime* runtime) const;
    bool equals(LgsType* other) override;
    ~LgsObject() override = default;
};


