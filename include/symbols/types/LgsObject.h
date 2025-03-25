#ifndef LOGOSOBJECT_H
#define LOGOSOBJECT_H
#include "LgsType.h"
#include <funcs/LgsMethodImpl.h>

class LgsField;

class LgsObject final : public LgsType {
public:
    string name;
    Type* IRType = nullptr;

    explicit LgsObject(const string& typeName) : name(typeName) {}
    const string getName() const override;
    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) const override;
    ~LgsObject() override = default;
};

#endif //LOGOSOBJECT_H
