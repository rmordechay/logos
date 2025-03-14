#ifndef LOGOSOBJECT_H
#define LOGOSOBJECT_H
#include "LgsType.h"
#include <funcs/LgsMethodImpl.h>

class LgsField;

class LgsObject final : public LgsType {
public:
    Type* IRType = nullptr;
    string name;

    explicit LgsObject(const string& typeName) : name(typeName) {}
    LgsObject(const LgsObject& other);
    const string getName() const override;
    Type* getIRType() override;
    LgsConstant* getZeroValue() override;
    bool equals(LgsType* other) const override;
    ~LgsObject() override;

};



#endif //LOGOSOBJECT_H
