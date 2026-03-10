#pragma once
#include "LgsStmt.h"
#include "LgsValue.h"

class LgsStmtsBlock;
class LgsExpr;
class LgsFuncCall;

class LgsDeferStmt final : public LgsStmt {
public:
    LgsExpr* expr = nullptr;

    void setDebugValue(LgsCodeGen& cg) override;
    LgsFuncCall* getAsFuncCall() const;
    ~LgsDeferStmt() override;
};
