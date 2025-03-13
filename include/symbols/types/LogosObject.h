#ifndef LOGOSOBJECT_H
#define LOGOSOBJECT_H
#include "LogosType.h"
#include <funcs/LogosMethodImpl.h>

class LogosField;

class LogosObject final : public LogosType {
public:
    Type* IRType = nullptr;
    string name;

    explicit LogosObject(const string& typeName) : name(typeName) {}
    LogosObject(const LogosObject& other);
    const string getName() const override;
    Type* getIRType() override;
    LogosConstant* getZeroValue() override;
    bool equals(LogosType* other) const override;
    ~LogosObject() override;

};



#endif //LOGOSOBJECT_H
