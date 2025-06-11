#pragma once
#include "LgsArray.h"
#include "data/LgsDefinitions.h"

class LgsField;

class LgsObject : public LgsType {
public:
    string name;
    string path;
    bool isSingleton = false;
    vector<LgsType*> interfaces;

    explicit LgsObject(const string& name, const string& path) : name(name), path(path) {}
    explicit LgsObject(const string& name) : LgsObject(name, "") {}
    string prettyName() const override;
    Type* getIRType() override;
    string getIRName() override;
    size_t getSizeBytes() override;
    json asJSON() const override;
    LgsInterface* getInterface(const string& interfaceName) const;
    void setVFuncs(LgsRuntime* runtime) const;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) override;
    LgsObject* clone() override;
    ~LgsObject() override = default;
};


