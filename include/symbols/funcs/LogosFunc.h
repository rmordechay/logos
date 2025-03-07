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
    LogosStmtBlock* stmtBlock = nullptr;
    BasicBlock* const funcEntry = BasicBlock::Create(context, "entry");

    explicit LogosFunc(const string& name, LogosType* funcType) : name(name), type(funcType) {}
    virtual Value* callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) = 0;
    void setIRParams(CodeGenMetadata* metadata, Value* args) const;
    ~LogosFunc() override;
};

inline void LogosFunc::setIRParams(CodeGenMetadata* metadata, Value* args) const {
    for (const auto& param : params) {
        LogosSymbol symbol(VAR_DEC, param);
        if (param->expr) {
            param->expr->setIRValue(args);
            metadata->logosStack.addLocalSymbol(param->name, symbol);
        } else {
            const auto constant = param->type->getZeroValue();
            constant->setIRValue(args);
            metadata->logosStack.addLocalSymbol(param->name, symbol);
        }
        args++;
    }
}

inline LogosFunc::~LogosFunc() {
    for (const auto param : params) {
        delete param;
    }
    delete stmtBlock;
}

#endif //LOGOSFUNC_H
