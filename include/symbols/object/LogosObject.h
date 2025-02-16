#ifndef LOGOSOBJECT_H
#define LOGOSOBJECT_H
#include "LogosField.h"
#include "types/LogosType.h"

class LogosUserFunc;
class LogosField;

class LogosObject final : public LogosType {
public:
    Type* llvmType = nullptr;
    string typeName;
    map<string, LogosField*> fields;
    map<string, LogosUserFunc*> funcs;

    explicit LogosObject(const string& typeName) : typeName(typeName) {}
    const string name() const override;
    Type* getLLVMType() override;
    bool operator==(LogosType* other) const override;
    ~LogosObject() override;
};

#endif //LOGOSOBJECT_H
