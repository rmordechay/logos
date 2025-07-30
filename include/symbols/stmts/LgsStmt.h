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
    LgsVarDec* asVarDec();
    LgsAssignment* asAssignment();
    LgsIfStmt* asIfStmt();
    LgsForLoop* asLoop();
    LgsPatternMatch* asPatternMatch();
    LgsReturn* asReturn();
    LgsContinueStmt* asContinue();
    LgsCoroutine* asCoroutine();
    LgsBreakStmt* asBreakStmt();
    LgsFuncCall* asFuncCall();
    LgsSelection* asSelection();
    LgsPostfixExpr* asPostfixExpr();
    virtual void createIRStmt(LgsCodeGen* codeGen) = 0;
    ~LgsStmt() override = default;
};


