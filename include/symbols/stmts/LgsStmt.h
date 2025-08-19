#pragma once
#include <LgsValue.h>

class LgsDeferStmt;
class LgsCoroutine;
class LgsPostfixExpr;
class LgsCodeGen;
class LgsForLoop;
class LgsVarDec;
class LgsSelection;
class LgsFuncCall;
class LgsReturn;
class LgsIfStmt;
class LgsContinue;
class LgsBreak;
class LgsAssignment;

class LgsStmt : virtual public LgsValue {
public:
    LgsForLoop* asLoop();
    LgsCoroutine* asCoroutine();
    LgsDeferStmt* asDefer();
    LgsFuncCall* asFuncCall();
    LgsIfStmt* asIfStmt();
    LgsPostfixExpr* asPostfixExpr();
    LgsSelection* asSelection();
    LgsBreak* asBreak();
    LgsContinue* asContinue();
    LgsReturn* asReturn();
    LgsVarDec* asVarDec();
    LgsAssignment* asAssignment();
};
