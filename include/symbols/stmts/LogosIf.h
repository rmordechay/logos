#ifndef LOGOSIFSTMT_H
#define LOGOSIFSTMT_H
#include "LogosStmt.h"
#include "LogosStmtBlock.h"
#include "LogosExpr.h"

inline auto BB_IF_START = "if_start";
inline auto BB_IF_END = "if_end";
inline auto BB_ELSE = "else";
inline auto BB_ELSE_IF_START = "else_if_start";
inline auto BB_ELSE_IF_CHECK = "else_if_check";

class LogosIf final : public LogosStmt {
public:
    LogosExpr* ifCond;
    LogosStmtBlock* ifStmtBlock;
    vector<LogosExpr*> elseIfConds;
    vector<LogosStmtBlock*> elseIfStmtBlocks;
    LogosStmtBlock* elseStmtBlock = nullptr;

    LogosIf(LogosExpr* ifCond, LogosStmtBlock* ifStmtBlock) : ifCond(ifCond), ifStmtBlock(ifStmtBlock) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    void computeSimpleIf(CodeGenMetadata* metadata) const;
    void createElseBlock(CodeGenMetadata* metadata, BasicBlock* elseBlock, BasicBlock* ifEndBlock) const;
    void computeComplexIf(CodeGenMetadata* metadata) const;
    ~LogosIf() override;
};



#endif //LOGOSIFSTMT_H
