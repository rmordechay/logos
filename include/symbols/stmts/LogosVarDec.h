#ifndef LOGOSVARDEFINITION_H
#define LOGOSVARDEFINITION_H
#include "LogosStmt.h"
#include "LogosExpr.h"

class LogosVarDec final : public LogosStmt {
public:
    string name;
    LogosType* type = nullptr;
    LogosType* userType = nullptr;
    LogosExpr* expr = nullptr;

    LogosVarDec(const string& name, LogosType* userType, LogosExpr* expr) : name(name), userType(userType), expr(expr) {}
    LogosVarDec(const string& name, LogosType* inferredType) : name(name), type(inferredType){}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LogosVarDec() override;
};




#endif //LOGOSVARDEFINITION_H
