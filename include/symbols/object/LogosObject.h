#ifndef LOGOSOBJECT_H
#define LOGOSOBJECT_H
#include "LogosType.h"

#include <map>
#include <funcs/LogosMethodImpl.h>

class LogosField;

class LogosObject final : public LogosType {
public:
    Type* IRType = nullptr;
    string typeName;
    map<string, LogosField*> fields;
    map<string, LogosMethodImpl*> methods;

    explicit LogosObject(const string& typeName) : typeName(typeName) {}
    const string getName() const override;
    Type* getIRType() override;
    LogosConstant* getZeroValue() override;
    bool equals(LogosType* other) const override;
    ~LogosObject() override;
};

#endif //LOGOSOBJECT_H
