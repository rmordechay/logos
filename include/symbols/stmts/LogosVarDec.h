#ifndef LOGOSVARDEFINITION_H
#define LOGOSVARDEFINITION_H
#include "LogosStmt.h"
#include "exprs/LogosExpr.h"

class LogosVarDec final : public LogosStmt {
public:
    string name;
    LogosType* inferredType = nullptr;
    LogosType* userType = nullptr;
    LogosExpr* expr = nullptr;

    LogosVarDec(const string& name, LogosType* userType, LogosExpr* expr) : name(name), userType(userType), expr(expr) {}
    LogosVarDec(const string& name, LogosType* inferredType) : name(name), inferredType(inferredType){}
    Value* writeLLVMValue(CodeGenMetadata* metadata) override;
    ~LogosVarDec() override;
};




#endif //LOGOSVARDEFINITION_H
