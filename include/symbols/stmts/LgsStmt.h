#pragma once
#include <LgsValue.h>

class LgsCoroutine;
class LgsPostfixExpr;
class LgsCodeGen;
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
    LgsForLoop* asLoop();
    LgsCoroutine* asCoroutine();
    LgsFuncCall* asFuncCall();
    LgsIfStmt* asIfStmt();
    LgsPatternMatch* asPatternMatch();
    LgsPostfixExpr* asPostfixExpr();
    LgsSelection* asSelection();
    LgsBreakStmt* asBreakStmt();
    LgsContinueStmt* asContinue();
    LgsReturn* asReturn();
    LgsVarDec* asVarDec();
    LgsAssignment* asAssignment();
    virtual void createIRStmt(LgsCodeGen* codeGen) = 0;
    ~LgsStmt() override = default;
};


