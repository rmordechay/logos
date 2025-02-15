#ifndef LOGOSSTMTBLOCK_H
#define LOGOSSTMTBLOCK_H
#include "CodeGeneration.h"
#include "stmts/LogosStmt.h"

class LogosStmtBlock final : public CodeGeneration {
public:
    vector<LogosStmt*> stmts;

    explicit LogosStmtBlock(const vector<LogosStmt*>& stmts) : stmts(stmts) {}
    Value* getLLVMValue(CodeGenMetadata* metadata) override;
    ~LogosStmtBlock() override = default;
    LogosStmtBlock();
};


#endif //LOGOSSTMTBLOCK_H
