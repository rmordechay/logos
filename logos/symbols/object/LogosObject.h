#ifndef LOGOSOBJECT_H
#define LOGOSOBJECT_H
#include "funcs/LogosFunc.h"
#include "stmts/LogosVarDec.h"

class LogosObject final : public LogosType {
public:
    string name;
    vector<LogosVarDec*> fields;
    vector<LogosFunc*> funcs;

    Type* getLLVMType(IRBuilder<>* builder) const override;
    ~LogosObject() override;

};

#endif //LOGOSOBJECT_H
