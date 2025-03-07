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
    virtual Value* call(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) = 0;
    void setArgs(CodeGenMetadata* metadata, Function::arg_iterator& args) const;
    ~LogosFunc() override;
};

inline LogosFunc::~LogosFunc() {
    for (const auto param : params) {
        delete param;
    }
    delete stmtBlock;
}

inline void LogosFunc::setArgs(CodeGenMetadata* metadata, Function::arg_iterator& args) const {
    for (const auto& param : params) {
        param->setIRValue(args);
        args++->setName(param->name);
        metadata->logosStack.addLocalSymbol(param->name, LogosSymbol(PARAM, param));
    }
}

#endif //LOGOSFUNC_H
