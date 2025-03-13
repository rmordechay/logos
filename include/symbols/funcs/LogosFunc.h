#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
#include "LogosParam.h"
#include "LogosValue.h"
#include "constants/LogosConstant.h"
#include "stmts/LogosStmtBlock.h"

class LogosParam;
class LogosExpr;
class LogosStmt;
class LogosType;

class LogosFunc : public LogosValue {
public:
    string name;
    string combinedName;
    LogosType* type;
    vector<LogosParam*> params;
    LogosStmtBlock* stmtBlock = nullptr;

    vector<Type*> IRParamsTypes;
    Function* IRFunc = nullptr;

    explicit LogosFunc(const string& name, LogosType* funcType) : name(name), type(funcType) {}
    explicit LogosFunc(const string& name, LogosType* funcType, const vector<LogosParam*>& params) : name(name), type(funcType), params(params) {}
    virtual Value* call(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) = 0;
    ~LogosFunc() override;
};

#endif //LOGOSFUNC_H
