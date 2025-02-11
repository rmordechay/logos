#ifndef LOGOSOBJECT_H
#define LOGOSOBJECT_H
#include "funcs/LogosFunc.h"
#include "stmts/LogosVarDec.h"
#include "LogosField.h"
#include "types/LogosType.h"

class LogosField;

class LogosObject final : public LogosType {
public:
    string typeName;
    map<string, LogosField*> fields;
    map<string, LogosFunc*> funcs;

    LogosObject() = default;
    explicit LogosObject(const string& typeName) : typeName(typeName) {}
    const string name() const override;
    Type* getLLVMType(IRBuilder<>* builder, LogosStack* theStack) const override;
    bool operator==(LogosType* other) const override;
    ~LogosObject() override;

};

#endif //LOGOSOBJECT_H
