#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
#include "CodeGeneration.h"
#include "exprs/LogosFuncCall.h"
#include "stmts/LogosVarDec.h"
#include "types/LogosType.h"

class LogosFunc : public CodeGeneration {
public:
    string name;
    LogosType* type;
    vector<LogosVarDec*> params;
    vector<LogosStmt*> stmts;

    explicit LogosFunc(const string& name, LogosType* funcType) : name(name), type(funcType) {}
    virtual FunctionCallee getFuncCallee(IRBuilder<>* builder, LogosStack* theStack, Module* module) = 0;
    virtual vector<Value*> getArgs(IRBuilder<>* builder, LogosStack* theStack, Module* module, const vector<LogosExpr*>& args) = 0;
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
