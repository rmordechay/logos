#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
#include "CodeGeneration.h"
#include "stmts/LogosVarDec.h"

class LogosExpr;
class LogosStmt;
class LogosType;

class LogosFunc : public CodeGeneration {
public:
    string name;
    LogosType* type;
    vector<LogosVarDec*> params;
    vector<LogosStmt*> stmts;

    explicit LogosFunc(const string& name, LogosType* funcType) : name(name), type(funcType) {}
    virtual FunctionCallee getFuncCallee(CodeGenMetadata* metadata) = 0;
    virtual vector<Value*> getArgs(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) = 0;
    ~LogosFunc() override;
};

inline LogosFunc::~LogosFunc() {
    for (const auto param : params) {
        delete param;
    }
    for (const auto stmt : stmts) {
        delete stmt;
    }
}

#endif //LOGOSFUNC_H
