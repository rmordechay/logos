#ifndef LOGOSOBJECT_H
#define LOGOSOBJECT_H
#include "funcs/LogosFunc.h"
#include "stmts/LogosVarDec.h"

class LogosObject final : public LogosType {
public:
    string typeName;
    vector<LogosVarDec*> fields;
    vector<LogosFunc*> funcs;

    LogosObject() = default;
    explicit LogosObject(const string& typeName) : typeName(typeName) {}
    const string name() const override;
    Type* getLLVMType(IRBuilder<>* builder) const override;
    bool operator==(LogosType* other) const override;
    ~LogosObject() override;

};

#endif //LOGOSOBJECT_H
