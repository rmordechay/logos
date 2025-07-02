#pragma once
#include <LgsValue.h>

class LgsPostfixExpr;
class LgsModule;
class LgsForLoop;
class LgsVarDec;
class LgsSelection;
class LgsFuncCall;
class LgsReturn;
class LgsPatternMatch;
class LgsIfStmt;
class LgsContinueStmt;
class LgsBreakStmt;
class LgsAssignment;

class LgsStmt : virtual public LgsValue {
public:
    LgsVarDec* asVarDec();
    LgsAssignment* asAssignment();
    LgsIfStmt* asIfStmt();
    LgsForLoop* asLoop();
    LgsPatternMatch* asPatternMatch();
    LgsReturn* asReturn();
    LgsContinueStmt* asContinue();
    LgsBreakStmt* asBreakStmt();
    LgsFuncCall* asFuncCall();
    LgsSelection* asSelection();
    LgsPostfixExpr* asPostfixExpr();
    virtual void createIRStmt(LgsModule* module) = 0;
    ~LgsStmt() override = default;
};


