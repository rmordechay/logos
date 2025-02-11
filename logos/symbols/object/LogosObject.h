#ifndef LOGOSOBJECT_H
#define LOGOSOBJECT_H
#include "funcs/LogosFunc.h"
#include "stmts/LogosVarDec.h"
#include "LogosField.h"

class LogosField;

class LogosObject final : public LogosType {
public:
    string typeName;
    vector<LogosField*> fields;
    vector<LogosFunc*> funcs;

    LogosObject() = default;
    explicit LogosObject(const string& typeName) : typeName(typeName) {}
    const string name() const override;
    Type* getLLVMType(IRBuilder<>* builder, LogosStack* theStack) const override;
    bool operator==(LogosType* other) const override;
    ~LogosObject() override;

};

#endif //LOGOSOBJECT_H
