#pragma once
#include <LgsValue.h>

class LgsPostfixExpr;
class LgsRuntime;
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
    LgsIfStmt* asIfStmt();
    LgsAssignment* asAssignment();
    LgsForLoop* asLoop();
    LgsPatternMatch* asPatternMatch();
    LgsReturn* asReturn();
    LgsContinueStmt* asContinue();
    LgsBreakStmt* asBreakStmt();
    LgsFuncCall* asFuncCall();
    LgsSelection* asSelection();
    LgsPostfixExpr* asPostfixExpr();
    virtual void createIRStmt(LgsRuntime* runtime) = 0;
    ~LgsStmt() override = default;
};


