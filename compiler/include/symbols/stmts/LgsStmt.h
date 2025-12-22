#pragma once
#include "LgsStmtsBlock.h"

#include <LgsValue.h>

class LgsIOStmt;
class LgsSwitch;
class LgsDeferStmt;
class LgsCoroutine;
class LgsPostfixExpr;
class LgsCgModule;
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
    LgsIfStmt* asIfStmt();
    LgsIOStmt* asIOStmt();
    LgsSwitch* asSwitch();
    LgsBreak* asBreak();
    LgsContinue* asContinue();
    LgsReturn* asReturn();
    LgsVarDec* asVarDec();
    LgsAssignment* asAssignment();
    LgsStmt* clone() override;
};

void freeStmt(const LgsStmt* stmt);
