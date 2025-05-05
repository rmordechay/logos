#ifndef LOGOSOBJECT_H
#define LOGOSOBJECT_H
#include "LgsData.h"
#include "LgsStr.h"
#include "LgsType.h"
#include "stmts/LgsField.h"

class LgsField;

class LgsObject : public LgsType {
public:
    string name;
    string path;
    bool isSingleton = false;
    vector<LgsType*> implements;

    explicit LgsObject() : name(LOGOS_PARENT_OBJ), path("") {}
    explicit LgsObject(const string& name) : name(name), path("") {}
    explicit LgsObject(const string& name, const string& path) : name(name), path(path) {}
    string prettyName() const override;
    Type* getIRType() override;
    string getIRName() override;
    json asJSON() const override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) const override;
    LgsObject* clone();
    ~LgsObject() override = default;
};

#endif //LOGOSOBJECT_H
