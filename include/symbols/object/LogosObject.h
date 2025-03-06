#ifndef LOGOSOBJECT_H
#define LOGOSOBJECT_H
#include "types/LogosType.h"
#include <map>

#include <funcs/LogosMethodImpl.h>


class LogosFuncImpl;
class LogosField;

class LogosObject final : public LogosType {
public:
    Type* IRType = nullptr;
    string typeName;
    map<string, LogosField*> fields;
    map<string, LogosMethodImpl*> methods;

    explicit LogosObject(const string& typeName) : typeName(typeName) {}
    const string name() const override;
    Type* getIRType() override;
    LogosConstant* getConstant() override;
    bool operator==(LogosType* other) const override;
    ~LogosObject() override;
};

#endif //LOGOSOBJECT_H
