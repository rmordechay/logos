#include "tools/LgsFormatter.h"
#include "exprs/LgsArrayExpr.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsInstance.h"
#include "exprs/LgsIterIndex.h"
#include "exprs/LgsTernaryExpr.h"
#include "exprs/LgsVariable.h"
#include "exprs/constants/LgsStrConst.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "files/LgsTestFile.h"
#include "logos/LgsApp.h"
#include "loops/LgsMetaVar.h"
#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsVarDec.h"
#define TAB_SIZE 4

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
    LgsApp app;
    app.loadSrcFile(formatted.str());
    const auto oldFileHash = file->hashFile();
    const auto newFileSize = app.srcFiles.front()->hashFile();
    assert(oldFileHash == newFileSize);
    std::ofstream outFile(file->path, std::ios::out | std::ios::trunc);
    outFile << formatted.str();
    outFile.close();
}

void LgsFormatter::formatMainFile(LgsMainFile* mainFile) {
    for (const auto& [funcName, func] : mainFile->funcs) {
        formatFunc(func);
        newLine(false, 2);
    }

    for (const auto obj : mainFile->objects) {
        formatObject(obj);
    }

    for (const auto interface : mainFile->interfaces) {
        formatInterface(interface);
    }

    for (const auto enum_ : mainFile->enums) {
        formatEnum(enum_);
    }

    for (const auto subtype : mainFile->subtypes) {
        formatSubtype(subtype);
    }
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

void LgsFormatter::formatFuncHeader(const LgsFunc* func) {
    insert(func->funcType->name + '(');
    for (size_t i = 0; i < func->funcType->params.size(); ++i) {
        if (i > 0) insert(", ");
        formatParam(func->funcType->params[i]);
    }
    insert(")");
}

void LgsFormatter::formatFunc(const LgsFunc* func) {
    formatFuncHeader(func);
    formatStmtsBlock(func->stmtsBlock);
}

void LgsFormatter::formatParam(LgsParam& param) {
    insert(param.name + ": " + param.type->pname());
    if (param.expr) {
        insert(" = ");
        formatExpr(param.expr);
    }
}

void LgsFormatter::formatIOPair(LgsIOPair* ioPair, LgsObject* obj) {
    assert(0);
}

void LgsFormatter::formatStmt(LgsStmt* stmt) {
    if (const auto pattern = stmt->asSwitch()) formatSwitch(pattern);
    else if (const auto ifStmt = stmt->asIfStmt()) formatIfStmt(ifStmt);
    else if (const auto varDec = stmt->asVarDec()) formatVarDec(varDec);
    else if (const auto loopStmt = stmt->asLoop()) formatLoopStmt(loopStmt);
    else if (const auto coroutine = stmt->asCoroutine()) formatCoroutine(coroutine);
    else if (const auto deferStmt = stmt->asDefer()) formatDeferStmt(deferStmt);
    else if (const auto assignment = stmt->asAssignment()) formatAssignment(assignment);
    else if (const auto funcCall = stmt->asFuncCall()) formatFuncCall(funcCall);
    else if (const auto postfixExpr = stmt->asPostfixExpr()) formatPostfixExpr(postfixExpr);
    else if (const auto selection = stmt->asSelection()) formatSelection(selection);
    else if (const auto returnStmt = stmt->asReturn()) formatReturnStmt(returnStmt);
    else if (const auto continueStmt = stmt->asContinue()) formatContinueStmt(continueStmt);
    else if (const auto ioStmt = stmt->asIOStmt()) formatIOStmt(ioStmt);
    else if (const auto breakStmt = stmt->asBreak()) formatBreakStmt(breakStmt);
    else if (auto expr = stmt->asExpr()) formatExpr(expr);
    else assert(0);
}

void LgsFormatter::formatStmtsBlock(const LgsStmtsBlock* stmtsBlock) {
    if (!stmtsBlock) return;
    insert(" {");
    indentLevel++;
    for (const auto stmt : stmtsBlock->stmts) {
        newLine(true);
        formatStmt(stmt.stmt);
    }
    newLine();
    indentLevel--;
    insert("}");
}

void LgsFormatter::formatVarDec(LgsVarDec* varDec) {
    insert(varDec->name);
    if (varDec->type) {
        insert(": " + varDec->type->pname());
    }
    if (varDec->expr) {
        insert(" = ");
        formatExpr(varDec->expr);
    }
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
    if (!expr) return;
    if (const auto ternaryExpr = dynamic_cast<LgsTernaryExpr*>(expr)) {
        formatTernaryExpr(ternaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(expr)) {
        formatBinaryExpr(binaryExpr);
    } else {
        if (const auto variable = expr->asVariable()) return formatVariable(variable);
        if (const auto lambda = expr->asFunc()) return formatFunc(lambda);
        if (const auto intConst = expr->asIntConst()) return formatIntConst(intConst);
        if (const auto instance = expr->asInstance()) return formatInstance(instance);
        if (const auto funcCall = expr->asFuncCall()) return formatFuncCall(funcCall);
        if (const auto strConst = expr->asStrConst()) return formatStrConst(strConst);
        if (const auto selection = expr->asSelection()) return formatSelection(selection);
        if (const auto arrayExpr = expr->asArrayExpr()) return formatArrayExpr(arrayExpr);
        if (const auto hashMap = expr->asHashMap()) return formatHashMap(hashMap);
        if (const auto iterIndex = expr->asIterIndex()) return formatIterIndex(iterIndex);
        if (const auto postfixExpr = expr->asPostfixExpr()) return formatPostfixExpr(postfixExpr);
        if (const auto prefixExpr = expr->asPrefixExpr()) return formatPrefixExpr(prefixExpr);
        if (const auto forVar = expr->asLoopMetaVar()) return formatLoopMetaVar(forVar);
        if (const auto vecExpr = expr->asVectorExpr()) return formatVectorExpr(vecExpr);
        if (const auto castExpr = expr->asCast()) return formatCast(castExpr);
        if (const auto jsonExpr = expr->asJson()) return formatJson(jsonExpr);
        if (expr->asNull()) return insert(LGS_NULL_LITERAL);
        assert(0);
    }
}

void LgsFormatter::formatBinaryExpr(LgsBinaryExpr* binaryExpr) {
    formatExpr(binaryExpr->left);
    insert(' ' + binaryExpr->op.text + ' ');
    formatExpr(binaryExpr->right);
}

void LgsFormatter::formatTernaryExpr(LgsTernaryExpr* ternary) {
    assert(0);
}

void LgsFormatter::formatCast(LgsCast* cast) {
    assert(0);
}

void LgsFormatter::formatArrayExpr(LgsArrayExpr* arrayExpr) {
    insert("[");
    for (auto element : arrayExpr->elements) {
        formatExpr(element);
    }
    insert("]");
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
    insert(variable->name);
}

void LgsFormatter::formatSelection(const LgsSelection* selection) {
    assert(0);
}

void LgsFormatter::formatFuncCall(LgsFuncCall* funcCall) {
    insert(funcCall->name);
    insert("(");
    auto isFirst = true;
    for (auto arg : funcCall->args) {
        if (!isFirst) insert(", ");
        isFirst = false;
        insert(arg.name + "=");
        formatExpr(arg.expr);
    }
    insert(")");
}

void LgsFormatter::formatPrefixExpr(LgsPrefixExpr* prefixExpr) {
    assert(0);
}

void LgsFormatter::formatPostfixExpr(LgsPostfixExpr* postfixExpr) {
    assert(0);
}

void LgsFormatter::formatStrConst(const LgsStrConst* strConst) {
    insert("\"" + strConst->value + "\"");
}

void LgsFormatter::formatTypeExpr(LgsTypeExpr* typeExpr) {
    assert(0);
}

void LgsFormatter::formatJson(const LgsJson* jsonStmt) {
    assert(0);
}

void LgsFormatter::formatInstance(LgsInstance* instance) {
    insert(instance->name);
    insert("{");
    auto isFirst = true;
    for (auto [name, arg] : instance->args) {
        if (!isFirst) insert(", ");
        isFirst = false;
        insert(name + "=");
        formatExpr(arg.expr);
    }
    insert("}");
}

void LgsFormatter::formatIntConst(const LgsIntConst* intConst) {
    insert(std::to_string(intConst->value));
}

void LgsFormatter::formatInterfaceInstance(LgsInstance* instance, LgsInterface* interface) {
    assert(0);
}

void LgsFormatter::formatIterIndex(LgsIterIndex* iterIndex) {
    formatExpr(iterIndex->baseExpr);
    insert("[");
    formatExpr(iterIndex->index.from);
    if (iterIndex->index.to) {
        insert(":");
        formatExpr(iterIndex->index.to);
    }
    insert("]");
}

void LgsFormatter::formatLoopMetaVar(const LgsMetaVar* metaVar) {
    insert(metaVar->name);
}

void LgsFormatter::insert(const std::string& text) {
    formatted << text;
}

void LgsFormatter::newLine(const bool withIndent, const uint8_t lines) {
    formatted << std::string(lines, '\n');
    if (withIndent) {
        formatted << std::string(indentLevel * TAB_SIZE, ' ');
    }
}
