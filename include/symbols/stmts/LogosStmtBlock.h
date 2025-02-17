#ifndef LOGOSSTMTBLOCK_H
#define LOGOSSTMTBLOCK_H
#include "LogosValue.h"
#include "stmts/LogosStmt.h"

class LogosStmtBlock final : public LogosValue {
public:
    vector<LogosStmt*> stmts;

    explicit LogosStmtBlock(const vector<LogosStmt*>& stmts) : stmts(stmts) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    ~LogosStmtBlock() override = default;
    LogosStmtBlock();
};


#endif //LOGOSSTMTBLOCK_H
