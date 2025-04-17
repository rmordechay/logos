#ifndef LOGOSOBJECT_H
#define LOGOSOBJECT_H
#include "LgsStr.h"
#include "LgsType.h"
#include "stmts/LgsField.h"

class LgsField;

class LgsObject : public LgsType {
public:
    string name;
    Type* IRType = nullptr;
    vector<LgsType*> implements;

    explicit LgsObject(const string& typeName) : name(typeName) {}
    LgsObject(LgsObject& other);
    const string getName() const override;
    size_t size() override;
    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) const override;
    ~LgsObject() override = default;
};

#endif //LOGOSOBJECT_H
