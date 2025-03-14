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
    LgsObject(const LgsObject& other);
    const string getName() const override;
    Type* getIRType() override;
    LgsConst* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) const override;
    bool equals(LgsType* other) const override;
    ~LgsObject() override;

};



#endif //LOGOSOBJECT_H
