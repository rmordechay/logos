#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
#include "LogosParam.h"
#include "LogosValue.h"
#include "exprs/LogosConstant.h"
#include "stmts/LogosStmtBlock.h"
#include "stmts/LogosVarDec.h"

class LogosParam;
class LogosExpr;
class LogosStmt;
class LogosType;


class LogosFunc : public LogosValue {
public:
    string name;
    LogosType* type;
    vector<LogosParam*> params;
    vector<Type*> IRParamsTypes;
    Function* IRFunc = nullptr;
    LogosStmtBlock* stmtBlock = nullptr;

    BasicBlock* const entryBlock = BasicBlock::Create(context, "entry");

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
