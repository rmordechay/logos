#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
#include "CodeGeneration.h"
#include "stmts/LogosVarDec.h"
#include "types/LogosType.h"

class LogosFunc : public CodeGeneration {
public:
    string name;
    const LogosType& type;
    vector<const LogosVarDec*> params;
    vector<const LogosStmt*> stmts;

    LogosFunc(const string& name, const LogosType& funcType) : name(name), type(funcType) {}
    ~LogosFunc() override = default;
};

#endif //LOGOSFUNC_H
