#pragma once
#include "LgsType.h"

class LgsRuntime;
class LgsField;

class LgsObject : public LgsType {
public:
    string name;
    string path;
    bool isSingleton = false;
    vector<LgsType*> interfaces;

    explicit LgsObject(const string& name, const string& path = "") : name(name), path(path) {}
    LgsInterface* getInterface(const string& interfaceName) const;
    string pName() const override;
    Type* getIRType() override;
    string getIRName() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    string getStrFormatPart() const override;
    void setVFuncs(LgsRuntime* runtime) const;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) override;
    ~LgsObject() override = default;
};


