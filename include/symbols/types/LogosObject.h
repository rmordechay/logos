#ifndef LOGOSOBJECT_H
#define LOGOSOBJECT_H
#include "LogosType.h"
#include "stmts/LogosField.h"

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
    LogosObject(const LogosObject& other);
    const string getName() const override;
    Type* getIRType() override;
    LogosConstant* getZeroValue() override;
    LogosField* getField(const string& name) override;
    LogosMethodImpl* getMethod(const string& name) override;
    bool equals(LogosType* other) const override;
    ~LogosObject() override;

};



#endif //LOGOSOBJECT_H
