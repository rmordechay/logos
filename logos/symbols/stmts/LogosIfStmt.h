#ifndef LOGOSIFSTMT_H
#define LOGOSIFSTMT_H
#include "LogosStmt.h"

class LogosIfStmt final : public LogosStmt {
public:
    LogosExpr *cond;
    vector<CodeGeneration*> codeNodes;

    explicit LogosIfStmt(LogosExpr* cond) : cond(cond) {}
    const LogosType& getType() const override;
    Value* getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) override;
    ~LogosIfStmt() override = default;
};



#endif //LOGOSIFSTMT_H
