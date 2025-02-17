#ifndef LOGOSOBJECT_H
#define LOGOSOBJECT_H
#include <map>
#include "types/LogosType.h"


class LogosUserFunc;
class LogosField;

class LogosObject final : public LogosType {
public:
    Type* IRType = nullptr;
    string typeName;
    map<string, LogosField*> fields;
    map<string, LogosUserFunc*> funcs;

    explicit LogosObject(const string& typeName) : typeName(typeName) {}
    const string name() const override;
    Type* getIRType() override;
    bool operator==(LogosType* other) const override;
    ~LogosObject() override;
};

#endif //LOGOSOBJECT_H
