#ifndef LOGOSLOOP_H
#define LOGOSLOOP_H

#include "stmts/LogosStmt.h"


class LogosStmtBlock;
class LogosExpr;

class LogosLoop final : public LogosStmt {
public:
    LogosExpr *cond = nullptr;
    LogosStmtBlock* stmtBlock = nullptr;

    LogosLoop(LogosExpr* cond, LogosStmtBlock* stmtBlock) : cond(cond), stmtBlock(stmtBlock) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    ~LogosLoop() override = default;
};



#endif //LOGOSLOOP_H
