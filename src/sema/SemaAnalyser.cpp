#include "SemaAnalyser.h"
#include "LogosErrors.h"
#include "exprs/LogosBinaryExpr.h"
#include "loops/LogosLoopVar.h"
#include "object/LogosField.h"

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
        visitFuncImpl(func);
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
    for (const auto& entry : object->methods) {
        visitMethodImpl(entry.second);
    }
}

void SemaAnalyser::visitMainFunc(const LogosFuncImpl* mainFunc, const std::string& path) {
    visitFuncImpl(mainFunc);
}

void SemaAnalyser::visitFuncImpl(const LogosFuncImpl* func) {
    logosStack.enterScope();
    for (const auto& param : func->params) {
        visitParam(param);
    }
    visitStmtBlock(func->stmtBlock);
    logosStack.exitScope();
}

void SemaAnalyser::visitParam(LogosParam* param) {}

void SemaAnalyser::visitStmt(LogosStmt* stmt) {
    if (!stmt) return;
    if (const auto varDec = dynamic_cast<LogosVarDec*>(stmt)) {
        visitVarDec(varDec);
    } else if (const auto ifStmt = dynamic_cast<LogosIf*>(stmt)) {
        visitIfStmt(ifStmt);
    } else if (const auto loopStmt = dynamic_cast<LogosLoop*>(stmt)) {
        visitLoopStmt(loopStmt);
    } else if (const auto fieldDef = dynamic_cast<LogosAssignment*>(stmt)) {
        visitAssignment(fieldDef);
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

void SemaAnalyser::visitMethodImpl(const LogosMethodImpl* method) {
    logosStack.enterScope();
    for (const auto& param : method->params) {
        visitParam(param);
    }
    visitStmtBlock(method->stmtBlock);
    logosStack.exitScope();
}

void SemaAnalyser::visitAssignment(const LogosAssignment* fieldDef) {

}

void SemaAnalyser::visitVarDec(LogosVarDec* varDec) {
    if (varDec->expr) {
        visitExpr(varDec->expr);
        varDec->type = varDec->expr->type;
    } else {
        varDec->type = varDec->userType;
    }
    logosStack.addLocalSymbol(varDec->name, LogosSymbol(VAR_DEC, varDec));
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

void SemaAnalyser::visitRangeLoop(const LogosRangeLoop* rangeLoop) {
    const auto name = rangeLoop->loopVar->name;
    logosStack.addLocalSymbol(name, LogosSymbol(LOOP_VAR, rangeLoop->loopVar));
    visitStmtBlock(rangeLoop->stmtBlock);
}

void SemaAnalyser::visitForeachLoop(LogosForeachLoop* foreachLoop) {
    visitExpr(foreachLoop->iterableExpr);
    setIterable(foreachLoop);

    foreachLoop->loopVar->type = foreachLoop->iterableExpr->type;
    foreachLoop->loopVar->element->type = foreachLoop->loopVar->type;
    logosStack.addLocalSymbol(foreachLoop->loopVar->name, LogosSymbol(LOOP_VAR, foreachLoop->loopVar));

    visitStmtBlock(foreachLoop->stmtBlock);
}

void SemaAnalyser::visitExpr(LogosExpr* expr) {
    if (!expr) return;
    if (const auto unaryExpr = dynamic_cast<LogosUnaryExpr*>(expr)) {
        visitUnaryExpr(unaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LogosBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
    }
}

void SemaAnalyser::visitArray(LogosArray* array) {
    for (const auto& element : array->elements) {
        visitExpr(element);
    }
    setArrayType(array);
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
    } else if (const auto array = dynamic_cast<LogosArray*>(unaryExpr)) {
        visitArray(array);
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
    for (int i = 0; i < selection->exprs.size() - 1; ++i) {
        const auto prevExpr = selection->exprs[i];
        const auto nextExpr = selection->exprs[i + 1];
        if (const auto variable = dynamic_cast<LogosVariable*>(prevExpr)) {
            resolveSelection(variable, nextExpr);
        }
    }
    selection->type = selection->lastExpr()->type;
}

void SemaAnalyser::resolveSelection(const LogosVariable* variable, LogosUnaryExpr* nextExpr) {
    const auto symbol = logosStack.getSymbol(variable->name);
    switch (symbol->type) {
    case VAR_DEC:
        if (const auto instance = dynamic_cast<LogosInstance*>(symbol->varDec->expr)) {
            if (const auto funcCall = dynamic_cast<LogosFuncCall*>(nextExpr)) {
                const auto method = instance->obj->methods[funcCall->name];
                nextExpr->type = method->type;
            }
            if (const auto nextVariable = dynamic_cast<LogosVariable*>(nextExpr)) {
                const auto field = instance->obj->fields[nextVariable->name];
                nextExpr->type = field->type;
            }
        }
        break;
    default:
        break;;
    }
}

void SemaAnalyser::visitInstance(LogosInstance* instance) {
    const auto obj = logosStack.getSymbol(instance->name)->object;
    instance->type = obj;
    instance->obj = obj;
}

void SemaAnalyser::visitArrayIndex(LogosArrayIndex* arrayIndex) {
    visitExpr(arrayIndex->baseExpr);
    arrayIndex->type = arrayIndex->baseExpr->type;
}

void SemaAnalyser::visitFuncCall(LogosFuncCall* funcCall) {
    const auto symbol = logosStack.getSymbol(funcCall->name);
    if (symbol->type == BUILTIN_FUNC) {
        funcCall->type = symbol->builtinFunc->type;
    } else if (symbol->type == FUNC_IMPL) {
        funcCall->type = symbol->funcImpl->type;
    } else if (symbol->type == METHOD_IMPL) {
        funcCall->type = symbol->methodImpl->type;
    }
    for (const auto& arg : funcCall->args) {
        visitExpr(arg);
    }
}

void SemaAnalyser::visitVariable(LogosVariable* variable) {
    const auto symbol = logosStack.getSymbol(variable->name);
    switch (symbol->type) {
    case VAR_DEC:
        variable->type = symbol->varDec->type;
        break;
    case LOOP_VAR:
        variable->type = symbol->loopVar->type;
        break;
    default:
        break;
    }
}

void SemaAnalyser::visitConstant(const LogosConstant* constant) {

}

void SemaAnalyser::setArrayType(LogosArray* array) {
    // TODO add proper check for array type
    array->type = array->elements[0]->type;
}

void SemaAnalyser::setIterable(LogosForeachLoop* foreachLoop) {
    if (const auto variable = dynamic_cast<LogosVariable*>(foreachLoop->iterableExpr)) {
        setIterable(foreachLoop, variable);
    } else if (const auto array = dynamic_cast<LogosArray*>(foreachLoop->iterableExpr)) {
        foreachLoop->iterable = array;
    }
}

void SemaAnalyser::setIterable(LogosForeachLoop* foreachLoop, const LogosVariable* const variable) {
    const auto symbol = logosStack.getSymbol(variable->name);
    switch (symbol->type) {
    case VAR_DEC: {
        foreachLoop->iterable = dynamic_cast<LogosIterable*>(symbol->varDec->expr);
        return;
    }
    case LOOP_VAR: {
        foreachLoop->iterable = dynamic_cast<LogosIterable*>(symbol->loopVar->element);
        return;
    }
    case FIELD: {
        foreachLoop->iterable = dynamic_cast<LogosIterable*>(symbol->field->expr);
        return;
    }
    case SELECTION: {
        foreachLoop->iterable = dynamic_cast<LogosIterable*>(symbol->selection->lastExpr());
        return;
    }
    default:
        return;
    }
}

void SemaAnalyser::setUnsuccessful() {
    unique_lock lock(mtx);
    successful = false;
}
