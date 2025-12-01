#include "stmts/LgsStmt.h"
#include "funcs/LgsCoroutine.h"
#include "exprs/LgsFuncCall.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsBreak.h"
#include "stmts/LgsContinue.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsReturn.h"
#include "stmts/LgsVarDec.h"
#include "loops/LgsForLoop.h"
#include "stmts/LgsDeferStmt.h"
#include "stmts/LgsIOStmt.h"
#include "stmts/LgsSwitch.h"

LgsForLoop* LgsStmt::asLoop() { return dynamic_cast<LgsForLoop*>(this); }
LgsCoroutine* LgsStmt::asCoroutine() { return dynamic_cast<LgsCoroutine*>(this); }
LgsDeferStmt* LgsStmt::asDefer() { return dynamic_cast<LgsDeferStmt*>(this); }
LgsIfStmt* LgsStmt::asIfStmt() { return dynamic_cast<LgsIfStmt*>(this); }
LgsIOStmt* LgsStmt::asIOStmt() { return dynamic_cast<LgsIOStmt*>(this); }
LgsSwitch* LgsStmt::asSwitch() { return dynamic_cast<LgsSwitch*>(this); }
LgsExpr* LgsStmt::asExpr() { return dynamic_cast<LgsExpr*>(this); }
LgsBreak* LgsStmt::asBreak() { return dynamic_cast<LgsBreak*>(this); }
LgsContinue* LgsStmt::asContinue() { return dynamic_cast<LgsContinue*>(this); }
LgsReturn* LgsStmt::asReturn() { return dynamic_cast<LgsReturn*>(this); }
LgsVarDec* LgsStmt::asVarDec() { return dynamic_cast<LgsVarDec*>(this); }
LgsAssignment* LgsStmt::asAssignment() { return dynamic_cast<LgsAssignment*>(this); }

void freeStmt(const LgsStmt* stmt) {
    if (!stmt) return;
    delete stmt;
}
