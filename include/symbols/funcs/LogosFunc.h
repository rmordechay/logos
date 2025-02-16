#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
#include "CodeGeneration.h"
#include "stmts/LogosStmtBlock.h"
#include "stmts/LogosVarDec.h"

class LogosExpr;
class LogosStmt;
class LogosType;

class LogosFunc : public CodeGeneration {
public:
    string name;
    LogosType* type;
    vector<LogosVarDec*> params;
    LogosStmtBlock* stmtBlock = nullptr;

    explicit LogosFunc(const string& name, LogosType* funcType) : name(name), type(funcType) {}
    virtual Value* callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) = 0;
    ~LogosFunc() override;
};

inline LogosFunc::~LogosFunc() {
    for (const auto param : params) {
        delete param;
    }
    delete stmtBlock;
}

#endif //LOGOSFUNC_H
