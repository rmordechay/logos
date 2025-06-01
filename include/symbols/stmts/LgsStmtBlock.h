#ifndef LOGOSSTMTBLOCK_H
#define LOGOSSTMTBLOCK_H
#include "stmts/LgsStmt.h"

class LgsStmtBlock final : public LgsValue {
public:
    std::vector<LgsStmt*> stmts;
    bool hasReturn = false;

    explicit LgsStmtBlock(const std::vector<LgsStmt*>& stmts = {}) : stmts(stmts) {}
    void createIRValue(Module* module) const;
    LgsStmt* lastStmt() const;
    std::string format(std::string& indentStr) override;
    nlohmann::json asJSON() override;
    ~LgsStmtBlock() override;
};


#endif //LOGOSSTMTBLOCK_H
