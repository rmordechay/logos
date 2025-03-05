#include "SemaAnalyser.h"
#include "LogosErrors.h"
#include "exprs/LogosBinaryExpr.h"

#include <ThreadPool.h>
#include <exprs/LogosArray.h>
#include <exprs/LogosArrayIndex.h>
#include <exprs/LogosConstant.h>
#include <exprs/LogosFuncCall.h>
#include <exprs/LogosInstance.h>
#include <exprs/LogosSelection.h>
#include <exprs/LogosVariable.h>
#include <funcs/LogosPrint.h>
#include <loops/LogosForeachLoop.h>
#include <loops/LogosLoop.h>
#include <loops/LogosRangeLoop.h>
#include <stmts/LogosAssignment.h>
#include <stmts/LogosIf.h>

void SemaAnalyser::analyse(const map<string, LogosFile*>& files, const map<string, LogosSymbol>& globalSymbols) {
    ThreadPool threadPool;
    for (const auto& pair : files) {
        threadPool.runTask([=, &globalSymbols] {
            SemaAnalyser semaAnalyser;
            semaAnalyser.logosStack.globalSymbols = globalSymbols;
            semaAnalyser.visitLogosFile(pair.second);
        });
    }
    threadPool.wait();
}

void SemaAnalyser::visitLogosFile(LogosFile* file) {
    if (const auto mainFile = dynamic_cast<LogosMainFile*>(file)) {
        visitMainFile(mainFile);
    } else if (const auto objFile = dynamic_cast<LogosObjectFile*>(file)) {
        visitObjectFile(objFile);
    }
}

void SemaAnalyser::visitMainFile(const LogosMainFile* mainFile) {
    for (const auto& func : mainFile->funcs) {
        visitUserFunc(func);
    }
    visitMainFunc(mainFile->mainFunc, mainFile->path);
}

void SemaAnalyser::visitObjectFile(const LogosObjectFile* objectFile) {
    if (!objectFile) return;
    visitObject(objectFile->obj);
}

void SemaAnalyser::visitObject(const LogosObject* object) {
    if (!object) return;
    for (const auto& entry : object->fields) {
        visitField(entry.second);
    }
}

void SemaAnalyser::visitMainFunc(const LogosFuncImpl* mainFunc, const std::string& path) {
    visitUserFunc(mainFunc);
}

void SemaAnalyser::visitUserFunc(const LogosFuncImpl* func) {
    logosStack.enterScope();
    for (const auto& param : func->params) {
        visitVarDec(param);
    }
    visitStmtBlock(func->stmtBlock);
    logosStack.exitScope();
}


void SemaAnalyser::visitStmt(LogosStmt* stmt) {
    if (!stmt) return;
    if (const auto varDec = dynamic_cast<LogosVarDec*>(stmt)) {
        visitVarDec(varDec);
    } else if (const auto ifStmt = dynamic_cast<LogosIf*>(stmt)) {
        visitIfStmt(ifStmt);
    } else if (const auto loopStmt = dynamic_cast<LogosLoop*>(stmt)) {
        visitLoopStmt(loopStmt);
    } else if (const auto fieldDef = dynamic_cast<LogosAssignment*>(stmt)) {
        visitFieldDef(fieldDef);
    } else if (const auto funcCall = dynamic_cast<LogosFuncCall*>(stmt)) {
        visitFuncCall(funcCall);
    }
}

void SemaAnalyser::visitStmtBlock(const LogosStmtBlock* stmtBlock) {
    for (const auto& stmt : stmtBlock->stmts) {
        visitStmt(stmt);
    }
}

void SemaAnalyser::visitField(LogosField* field) {

}

void SemaAnalyser::visitFieldDef(const LogosAssignment* fieldDef) {
    const auto names = fieldDef->names;
    for (const auto& name : names) {

    }
}


void SemaAnalyser::visitVarDec(LogosVarDec* varDec) {
    if (varDec->expr) {
        visitExpr(varDec->expr);
        varDec->inferredType = varDec->expr->type;
        logosStack.addLocalSymbol(varDec->name, LogosSymbol::createSymbol(varDec->expr));
    } else {
        varDec->inferredType = varDec->userType;
        // TODO potential memory leak
        auto const constant = new LogosConstant(&LOGOS_INT_TYPE, 0);
        logosStack.addLocalSymbol(varDec->name, LogosSymbol(CONSTANT, constant));
    }
}

void SemaAnalyser::visitIfStmt(const LogosIf* ifStmt) {
    visitExpr(ifStmt->ifCond);
}

void SemaAnalyser::visitLoopStmt(LogosLoop* loopStmt) {
    if (const auto rangeLoop = dynamic_cast<LogosRangeLoop*>(loopStmt)) {
        visitRangeLoop(rangeLoop);
    } else if (const auto foreachLoop = dynamic_cast<LogosForeachLoop*>(loopStmt)) {
        visitForeachLoop(foreachLoop);
    }
}

void SemaAnalyser::visitRangeLoop(LogosRangeLoop* rangeLoop) {}

void SemaAnalyser::visitForeachLoop(LogosForeachLoop* foreachLoop) {
    const auto iterableExpr = foreachLoop->iterableExpr;
    if (const auto variable = dynamic_cast<LogosVariable*>(iterableExpr)) {
        const auto symbol = logosStack.getSymbol(variable->name);
        foreachLoop->iterable = symbol->array;
        foreachLoop->iterable->type = inferArrayType(foreachLoop->iterable);
        foreachLoop->arrayIndex = new LogosArrayIndex(variable);
        foreachLoop->arrayIndex->type = foreachLoop->iterable->type;
        foreachLoop->arrayIndex->exprs.emplace_back(&LOGOS_INT_CONST);
        logosStack.addLocalSymbol(foreachLoop->loopVar->name, LogosSymbol(ARRAY_INDEX, foreachLoop->arrayIndex));
    }
    visitStmtBlock(foreachLoop->stmtBlock);
}

void SemaAnalyser::visitExpr(LogosExpr* expr) {
    if (!expr) return;
    if (const auto unaryExpr = dynamic_cast<LogosUnaryExpr*>(expr)) {
        visitUnaryExpr(unaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LogosBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
    } else if (const auto array = dynamic_cast<LogosArray*>(expr)) {
        visitArray(array);
    }
}

void SemaAnalyser::visitArray(LogosArray* array) {
    for (const auto& element : array->elements) {
        visitExpr(element);
    }
    array->type = inferArrayType(array);
}

void SemaAnalyser::visitUnaryExpr(LogosUnaryExpr* unaryExpr) {
    if (!unaryExpr) return;
    if (const auto instance = dynamic_cast<LogosInstance*>(unaryExpr)) {
        visitInstance(instance);
    } else if (const auto funcCall = dynamic_cast<LogosFuncCall*>(unaryExpr)) {
        visitFuncCall(funcCall);
    } else if (const auto selection = dynamic_cast<LogosSelection*>(unaryExpr)) {
        visitSelection(selection);
    } else if (const auto constant = dynamic_cast<LogosConstant*>(unaryExpr)) {
        visitConstant(constant);
    } else if (const auto arrIndex = dynamic_cast<LogosArrayIndex*>(unaryExpr)) {
        visitArrayIndex(arrIndex);
    } else if (const auto var = dynamic_cast<LogosVariable*>(unaryExpr)) {
        visitVariable(var);
    }
}

void SemaAnalyser::visitBinaryExpr(const LogosBinaryExpr* binaryExpr) {
    visitExpr(binaryExpr->left);
    visitExpr(binaryExpr->right);
}

void SemaAnalyser::visitSelection(LogosSelection* selection) {
    if (!selection) return;
    selection->type = inferSelectionType(selection);
}

void SemaAnalyser::visitInstance(LogosInstance* instance) {
    if (!instance) return;
    const auto obj = logosStack.getSymbol(instance->name)->object;
    instance->type = obj;
    instance->obj = obj;
}

void SemaAnalyser::visitArrayIndex(LogosArrayIndex* arrayIndex) {
    visitExpr(arrayIndex->baseExpr);
    arrayIndex->type = arrayIndex->baseExpr->type;
}

void SemaAnalyser::visitFuncCall(const LogosFuncCall* funcCallExpr) {
    auto logosSymbol = logosStack.getSymbol(funcCallExpr->name);
    for (const auto &arg : funcCallExpr->args) {
        visitExpr(arg);
    }
}

void SemaAnalyser::visitVariable(LogosVariable* variable) {
    const auto symbol = logosStack.getSymbol(variable->name);
    switch (symbol->type) {
    case ARRAY:
        variable->type = symbol->array->type;
        break;
    case ARRAY_INDEX:
        variable->type = symbol->arrayIndex->type;
        break;
    default:
        break;
    }
}

void SemaAnalyser::visitConstant(const LogosConstant* constant) {

}

void SemaAnalyser::setUnsuccessful() {
    unique_lock lock(mtx);
    successful = false;
}

LogosType* SemaAnalyser::inferSelectionType(LogosSelection* selection) {
    auto previousExpr = selection->exprs[0];
    LogosUnaryExpr* nextExpr = nullptr;
    for (int i = 1; i < selection->exprs.size(); ++i) {
        nextExpr = selection->exprs[i];
        resolveSelection(previousExpr, nextExpr);
        previousExpr = nextExpr;
    }
    if (nextExpr) { // If true, nextExpr is the last element
        selection->type = nextExpr->type;
    }
    return nullptr;
}

LogosType* SemaAnalyser::inferArrayType(const LogosArray* array) {
    // TODO add proper check for array type
    return array->elements[0]->type;
}

void SemaAnalyser::resolveSelection(LogosUnaryExpr* previousExpr, LogosUnaryExpr* nextExpr) {
    const auto symbol = logosStack.getSymbol(previousExpr->getName());
    switch (symbol->type) {
    case INSTANCE: {
        const auto obj = symbol->instance->obj;
        const auto func = obj->funcs[nextExpr->getName()];
        nextExpr->type = func->type;
        break;
    }
    default:
        break;
    }
}