#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
#include "LogosValue.h"
#include "exprs/LogosConstant.h"
#include "stmts/LogosStmtBlock.h"
#include "stmts/LogosVarDec.h"

class LogosExpr;
class LogosStmt;
class LogosType;

class LogosFunc : public LogosValue {
public:
    string name;
    LogosType* type;
    vector<LogosVarDec*> params;
    LogosStmtBlock* stmtBlock = nullptr;
    BasicBlock* const funcEntry = BasicBlock::Create(context, "entry");

    explicit LogosFunc(const string& name, LogosType* funcType) : name(name), type(funcType) {}
    virtual Value* callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) = 0;
    static void setIRArgs(CodeGenMetadata* metadata, const vector<LogosVarDec*>& params, Value* args);
    ~LogosFunc() override;
};

inline LogosFunc::~LogosFunc() {
    for (const auto param : params) {
        delete param;
    }
    delete stmtBlock;
}

inline void LogosFunc::setIRArgs(CodeGenMetadata* metadata, const vector<LogosVarDec*>& params, Value* args) {
    for (const auto& param : params) {
        if (param->expr) {
            param->expr->setIRValue(args);
            metadata->logosStack.addLocalSymbol(param->name, LogosSymbol::createSymbol(param->expr));
        } else {
            const auto constant = param->inferredType->getZeroValue();
            constant->setIRValue(args);
            auto symbol = LogosSymbol(CONSTANT, constant);
            metadata->logosStack.addLocalSymbol(param->name, symbol);
        }
        args++;
    }
}

#endif //LOGOSFUNC_H
