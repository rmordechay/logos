#include "parser/LgsFormatter.h"

#include "files/LgsInterfaceFile.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "files/LgsTestFile.h"

void LgsFormatter::formatFile(LgsFile* file) {
    if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
        formatMainFile(mainFile);
    } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
        formatObject(objFile->obj);
    } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
        formatInterface(interfaceFile->interface);
    } else if (const auto testFile = dynamic_cast<LgsTestFile*>(file)) {
        formatTestFile(testFile);
    } else {
        assert(0);
    }

}

void LgsFormatter::formatMainFile(LgsMainFile* mainFile) {
    assert(0);
}

void LgsFormatter::formatTestFile(LgsTestFile* testFile) {
    assert(0);
}

void LgsFormatter::formatObjectFile(LgsObjectFile* objFile) {
    assert(0);
}

void LgsFormatter::formatInterfaceFile(LgsInterfaceFile* interfaceFile) {
    assert(0);
}

void LgsFormatter::formatObject(LgsObject* obj) {
    assert(0);
}

void LgsFormatter::formatInterface(LgsInterface* interface) {
    assert(0);
}

void LgsFormatter::formatEnum(const LgsEnum* enum_) {
    assert(0);
}

void LgsFormatter::formatSubtype(LgsSubType * subtype) {
    assert(0);
}

void LgsFormatter::formatField(const LgsField* field) {
    assert(0);
}

void LgsFormatter::formatFunc(const LgsFunc* func) {
    assert(0);
}

void LgsFormatter::formatParam(const LgsParam* param) {
    assert(0);
}

void LgsFormatter::formatIOPair(LgsIOPair* ioPair, LgsObject* obj) {
    assert(0);
}

void LgsFormatter::formatStmt(LgsStmt* stmt) {
    assert(0);
}

void LgsFormatter::formatStmtsBlock(const LgsStmtsBlock* stmtsBlock) {
    assert(0);
}

void LgsFormatter::formatVarDec(const LgsVarDec* varDec) {
    assert(0);
}

void LgsFormatter::formatAssignment(LgsAssignment* assignment) {
    assert(0);
}

void LgsFormatter::formatIfStmt(LgsIfStmt* ifStmt) {
    assert(0);
}

void LgsFormatter::formatSwitch(LgsSwitch* switchStmt) {
    assert(0);
}

void LgsFormatter::formatWhileLoop(LgsWhileLoop* whileLoop) {
    assert(0);
}

void LgsFormatter::formatLoopStmt(LgsForLoop* loopStmt) {
    assert(0);
}

void LgsFormatter::formatRangeLoop(LgsRangeLoop* rangeLoop) {
    assert(0);
}

void LgsFormatter::formatForeachLoop(LgsForeachLoop* foreachLoop) {
    assert(0);
}

void LgsFormatter::formatInfiniteLoop(const LgsInfiniteLoop* infiniteLoop) {
    assert(0);
}

void LgsFormatter::formatReturnStmt(LgsReturn* returnStmt) {
    assert(0);
}

void LgsFormatter::formatContinueStmt(const LgsContinue* continueStmt) {
    assert(0);
}

void LgsFormatter::formatBreakStmt(const LgsBreak* breakStmt) {
    assert(0);
}

void LgsFormatter::formatCoroutine(const LgsCoroutine* coroutine) {
    assert(0);
}

void LgsFormatter::formatDeferStmt(const LgsDeferStmt* deferStmt) {
    assert(0);
}

void LgsFormatter::formatIOStmt(const LgsIOStmt* ioStmt) {
    assert(0);
}

void LgsFormatter::formatExpr(LgsExpr*& expr) {
    assert(0);
}

void LgsFormatter::formatBinaryExpr(const LgsBinaryExpr* binaryExpr) {
    assert(0);
}

void LgsFormatter::formatTernaryExpr(LgsTernaryExpr* ternary) {
    assert(0);
}

void LgsFormatter::formatCast(LgsCast* cast) {
    assert(0);
}

void LgsFormatter::formatArrayExpr(LgsArrayExpr* arrayExpr) {
    assert(0);
}

void LgsFormatter::formatStaticArray(const LgsArrayExpr* arrayExpr) {
    assert(0);
}

void LgsFormatter::formatDynamicArray(LgsArrayExpr* arrayExpr) {
    assert(0);
}

void LgsFormatter::formatHashMap(LgsHashMap* hashMap) {
    assert(0);
}

void LgsFormatter::formatVectorExpr(const LgsVectorExpr* vectorExpr) {
    assert(0);
}

void LgsFormatter::formatVariable(const LgsVariable* variable) {
    assert(0);
}

void LgsFormatter::formatSelection(const LgsSelection* selection) {
    assert(0);
}

void LgsFormatter::formatFuncCall(const LgsFuncCall* funcCall) {
    assert(0);
}

void LgsFormatter::formatPrefixExpr(LgsPrefixExpr* prefixExpr) {
    assert(0);
}

void LgsFormatter::formatPostfixExpr(LgsPostfixExpr* postfixExpr) {
    assert(0);
}

void LgsFormatter::formatStrConst(const LgsStrConst* strConst) {
    assert(0);
}

void LgsFormatter::formatTypeExpr(LgsTypeExpr* typeExpr) {
    assert(0);
}

void LgsFormatter::formatJson(const LgsJson* jsonStmt) {
    assert(0);
}

void LgsFormatter::formatInstance(LgsInstance* instance) {
    assert(0);
}

void LgsFormatter::formatNull(LgsNull* null) {
    assert(0);
}

void LgsFormatter::formatIntConst(const LgsIntConst* intConst) {
    assert(0);
}

void LgsFormatter::formatInterfaceInstance(LgsInstance* instance, LgsInterface* interface) {
    assert(0);
}

void LgsFormatter::formatIterIndex(LgsIterIndex* iterIndex) {
    assert(0);
}

void LgsFormatter::formatIndex(LgsIterIndex* iterIndex) {
    assert(0);
}

void LgsFormatter::formatSlice(LgsIterIndex* iterIndex) {
    assert(0);
}

void LgsFormatter::formatLoopMetaVar(LgsLoopMetaVar* metaVar) {
    assert(0);
}

