#ifndef LOGOSOBJECT_H
#define LOGOSOBJECT_H
#include "LgsAny.h"
#include "LgsDefinitions.h"
#include "LgsStr.h"
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
    LgsHashMap vtable = LgsHashMap(&LGS_STR, &LGS_ANY);

    explicit LgsObject() : name(LOGOS_PARENT_OBJ), path("") {}
    explicit LgsObject(const string& name) : name(name), path("") {}
    explicit LgsObject(const string& name, const string& path) : name(name), path(path) {}
    void setVirtualFuncs(vector<Type*>& elementTypes) const;
    string prettyName() const override;
    Type* getIRType() override;
    string getIRName() override;
    json asJSON() const override;
    LgsInterface* getInterface(const string& interfaceName) const;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) override;
    LgsObject* clone();
    ~LgsObject() override = default;
};

#endif //LOGOSOBJECT_H
