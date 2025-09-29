#pragma once
#include <LgsValue.h>

class LgsIOStmt;
class LgsPatternMatching;
class LgsDeferStmt;
class LgsCoroutine;
class LgsPostfixExpr;
class LgsLLVMGen;
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
    bool isTerminator();
    LgsForLoop* asLoop();
    LgsCoroutine* asCoroutine();
    LgsDeferStmt* asDefer();
    LgsFuncCall* asFuncCall();
    LgsIfStmt* asIfStmt();
    LgsIOStmt* asIOStmt();
    LgsPatternMatching* asPattern();
    LgsPostfixExpr* asPostfixExpr();
    LgsExpr* asExpr();
    LgsSelection* asSelection();
    LgsBreak* asBreak();
    LgsContinue* asContinue();
    LgsReturn* asReturn();
    LgsVarDec* asVarDec();
    LgsAssignment* asAssignment();
};
