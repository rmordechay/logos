#pragma once
#include "methods/LgsObjMethods.h"

class LgsField;

class LgsObject : public LgsType {
public:
    string name;
    string path;
    bool isSingleton = false;
    vector<LgsType*> interfaces;
    LgsObjFieldsFunc fieldsF{this};

    explicit LgsObject(const string& name, const string& path) : name(name), path(path) {
        setVTable();
    }
    explicit LgsObject(const string& name) : LgsObject(name, "") {}
    explicit LgsObject() : LgsObject(LOGOS_PARENT_OBJ, "") {}
    string prettyName() const override;
    Type* getIRType() override;
    string getIRName() override;
    size_t getSizeBytes() override;
    json asJSON() const override;
    LgsInterface* getInterface(const string& interfaceName) const;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) override;
    LgsObject* clone() override;
    void setVFuncs(LgsRuntime* runtime) const;
    ~LgsObject() override = default;
};


