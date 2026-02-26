#include "stmts/LgsStmt.h"

#include <assert.h>

#include "LgsType.h"
#include "funcs/LgsCoroutine.h"
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
LgsBreak* LgsStmt::asBreak() { return dynamic_cast<LgsBreak*>(this); }
LgsContinue* LgsStmt::asContinue() { return dynamic_cast<LgsContinue*>(this); }
LgsReturn* LgsStmt::asReturn() { return dynamic_cast<LgsReturn*>(this); }
LgsVarDec* LgsStmt::asVarDec() { return dynamic_cast<LgsVarDec*>(this); }
LgsAssignment* LgsStmt::asAssignment() { return dynamic_cast<LgsAssignment*>(this); }

LgsStmt* LgsStmt::clone() const {
    assert(0);
}

void freeStmt(LgsStmt* stmt) {
    if (!stmt) return;
    if (const auto loop = stmt->asLoop()) {
        delete loop;
    } else if (const auto coroutine = stmt->asCoroutine()) {
        delete coroutine;
    } else if (const auto defer = stmt->asDefer()) {
        delete defer;
    } else if (const auto ifStmt = stmt->asIfStmt()) {
        delete ifStmt;
    } else if (const auto iOStmt = stmt->asIOStmt()) {
        delete iOStmt;
    } else if (const auto switch_ = stmt->asSwitch()) {
        delete switch_;
    } else if (const auto break_ = stmt->asBreak()) {
        delete break_;
    } else if (const auto continue_ = stmt->asContinue()) {
        delete continue_;
    } else if (const auto return_ = stmt->asReturn()) {
        delete return_;
    } else if (const auto varDec = stmt->asVarDec()) {
        if (varDec->expr) {
            if (varDec->type && varDec->expr->type && varDec->type == varDec->expr->type) {
                freeExpr(varDec->expr);
            } else {
                freeType(varDec->type);
                freeExpr(varDec->expr);
            }
        } else {
            freeType(varDec->type);
        }
        varDec->setType(nullptr);
        varDec->expr = nullptr;
    } else if (const auto assignment = stmt->asAssignment()) {
        delete assignment;
    }
}
