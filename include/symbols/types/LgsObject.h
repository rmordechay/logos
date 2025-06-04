#ifndef LOGOSOBJECT_H
#define LOGOSOBJECT_H
#include "LgsAny.h"
#include "data/LgsDefinitions.h"
#include "LgsType.h"
#include "exprs/unary/LgsHashMap.h"
#include "stmts/LgsField.h"

class LgsField;

class LgsObject : public LgsType {
public:
    string name;
    string path;
    bool isSingleton = false;
    vector<LgsType*> implements;
    LgsHashMap vtable = LgsHashMap(new LgsStr(), &LGS_ANY);

    explicit LgsObject() : name(LOGOS_PARENT_OBJ), path("") {}
    explicit LgsObject(const string& name) : name(name), path("") {}
    explicit LgsObject(const string& name, const string& path) : name(name), path(path) {}
    string prettyName() const override;
    Type* getIRType(LgsRuntime* runtime) override;
    string getIRName() override;
    json asJSON() const override;
    LgsInterface* getInterface(const string& interfaceName) const;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) override;
    LgsObject* clone() override;
    ~LgsObject() override = default;
};

#endif //LOGOSOBJECT_H
