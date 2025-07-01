#pragma once
#include "LgsType.h"

class LgsModule;
class LgsField;

class LgsObject : public LgsType {
public:
    string name;
    bool isSingleton = false;
    vector<LgsType*> interfaces;

    explicit LgsObject(const string& name) : name(name) {}
    LgsInterface* getInterface(const string& interfaceName) const;
    string prettyName() const override;
    Type* getIRType(LLVMContext& context) override;
    string getIRName() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    string getStrFormatPart() const override;
    void setVFuncs(LgsModule* runtime) const;
    bool equals(LgsType* other) override;
    ~LgsObject() override = default;
};


