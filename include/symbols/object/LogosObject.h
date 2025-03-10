#ifndef LOGOSOBJECT_H
#define LOGOSOBJECT_H
#include "LogosType.h"

#include <map>
#include <funcs/LogosMethodImpl.h>

class LogosField;

class LogosObject final : public LogosType {
public:
    Type* IRType = nullptr;
    string name;
    map<string, LogosField*> fields;
    map<string, LogosMethodImpl*> methods;

    explicit LogosObject(const string& typeName) : name(typeName) {}
    const string getName() const override;
    Type* getIRType() override;
    LogosConstant* getZeroValue() override;
    bool containsField(const string& name) const;
    bool containsMethod(const string& name) const;
    LogosField* getField(const string& name) const;
    LogosMethodImpl* getMethod(const string& name) const;
    bool equals(LogosType* other) const override;
    ~LogosObject() override;
};

#endif //LOGOSOBJECT_H
