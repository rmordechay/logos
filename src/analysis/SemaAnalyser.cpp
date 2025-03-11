#include "SemaAnalyser.h"
#include "LogosError.h"
#include "binary/LogosBinaryExpr.h"
#include "unary/LogosMethodCall.h"
#include "loops/LogosLoopVar.h"
#include "stmts/LogosField.h"
#include "stmts/LogosReturn.h"
#include "types/LogosBool.h"

#include <ThreadPool.h>
#include <unary/LogosArray.h>
#include <unary/LogosArrayIndex.h>
#include <unary/constants/LogosConstant.h>
#include <unary/LogosFuncCall.h>
#include <unary/LogosInstance.h>
#include <unary/LogosSelection.h>
#include <unary/LogosVariable.h>
#include <funcs/LogosPrint.h>
#include <loops/LogosForeachLoop.h>
#include <loops/LogosLoop.h>
#include <loops/LogosRangeLoop.h>
#include <stmts/LogosAssignment.h>
#include <stmts/LogosIf.h>

void SemaAnalyser::analyse() {
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
    visitMainFunc(mainFile->mainFunc);
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

void SemaAnalyser::visitMainFunc(const LogosFuncImpl* mainFunc) {
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

void SemaAnalyser::visitMethodImpl(const LogosMethodImpl* method) {
    logosStack.enterScope();
    for (const auto& param : method->params) {
        visitParam(param);
    }
    visitStmtBlock(method->stmtBlock);
    logosStack.exitScope();
}

void SemaAnalyser::visitParam(LogosParam* param) {
    logosStack.addLocalSymbol(param->name, LogosSymbol(PARAM, param));
}

void SemaAnalyser::visitStmt(LogosStmt* stmt) {
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
    } else if (const auto returnStmt = dynamic_cast<LogosReturn*>(stmt)) {
        visitReturnStmt(returnStmt);
    }
}

void SemaAnalyser::visitStmtBlock(const LogosStmtBlock* stmtBlock) {
    for (const auto& stmt : stmtBlock->stmts) {
        visitStmt(stmt);
    }
}

void SemaAnalyser::visitField(LogosField* field) {}

void SemaAnalyser::visitAssignment(const LogosAssignment* assignment) {}

void SemaAnalyser::visitVarDec(LogosVarDec* varDec) {
    const auto userType = varDec->userType;
    const auto expr = varDec->expr;
    if (expr) {
        visitExpr(expr);
        if (!matchTypes(expr->type, userType, expr)) return;
        varDec->type = expr->type;
    } else {
        varDec->type = userType;
    }
    logosStack.addLocalSymbol(varDec->name, LogosSymbol(VAR_DEC, varDec));
}

void SemaAnalyser::visitIfStmt(const LogosIf* ifStmt) {
    visitExpr(ifStmt->ifCond);
    visitStmtBlock(ifStmt->ifStmtBlock);
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
    setForLoopIterable(foreachLoop);
    setLoopVarType(foreachLoop);
    visitStmtBlock(foreachLoop->stmtBlock);
}

void SemaAnalyser::visitReturnStmt(const LogosReturn* returnStmt) {
    visitExpr(returnStmt->expr);
}

void SemaAnalyser::visitExpr(LogosExpr* expr) {
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
    } else if (const auto variable = dynamic_cast<LogosVariable*>(unaryExpr)) {
        visitVariable(variable);
    }
}

void SemaAnalyser::visitBinaryExpr(LogosBinaryExpr* binaryExpr) {
    visitExpr(binaryExpr->left);
    visitExpr(binaryExpr->right);
    setBinaryExprType(binaryExpr);
}

void SemaAnalyser::visitVariable(LogosVariable* variable) {
    setVariableType(variable);
}

void SemaAnalyser::visitSelection(LogosSelection* selection) {
    const auto exprs = selection->exprs;
    for (int i = 0; i < exprs.size(); ++i) {
        if (i == exprs.size() - 1) return;
        const auto currentExpr = exprs[i];
        const auto nextExpr = exprs[i + 1];
        const auto symbol = logosStack.getSymbol(currentExpr->getName());
        const auto logos = symbol->varDec->type;
        auto name = nextExpr->getName();
        auto logosField = logos->getField(name);
        std::cout << "" << '\n';
    }
}

void SemaAnalyser::resolveFirstSelection(const LogosSelection* selection, LogosVariable* variable) {
    visitVariable(variable);
    const auto symbol = getSymbol(variable->name, variable);
    if (!symbol) return;

    switch (symbol->type) {
    case VAR_DEC: {
        const auto varDecExpr = symbol->varDec->expr;
        if (const auto instance = dynamic_cast<LogosInstance*>(varDecExpr)) {
            resolveInnerSelection(selection, 0, instance);
        }
        return;
    }
    case PARAM: {
        const auto paramExpr = symbol->param->expr;
        if (const auto instance = dynamic_cast<LogosInstance*>(paramExpr)) {
            resolveInnerSelection(selection, 0, instance);
        }
        return;
    }
    default:
        break;
    }
}

void SemaAnalyser::resolveFirstSelection(const LogosSelection* selection, LogosFuncCall* funcCall) {
    visitFuncCall(funcCall);
    const auto symbol = getSymbol(funcCall->name, funcCall);
    if (!symbol) return;
    switch (symbol->type) {
    case FUNC_IMPL: {
        return resolveInnerSelection(selection, 0, symbol->funcImpl);
    }
    default:
        break;
    }
}

void SemaAnalyser::resolveInnerSelection(const LogosSelection* selection, const int i, LogosInstance* instance) {
    if (selection->innerExprs.size() == i) return;
    const auto nextExpr = selection->innerExprs[i];
    if (const auto variable = dynamic_cast<LogosVariable*>(nextExpr)) {
        const auto field = instance->obj->getField(variable->name);
        if (!field) return printError(E10005, variable, {variable->name, instance->obj->name});
        selection->innerExprs[i]->type = field->type;
        resolveInnerSelection(selection, i + 1, field);
    } else if (const auto methodCall = dynamic_cast<LogosMethodCall*>(nextExpr)) {
        methodCall->args.insert(methodCall->args.begin(), instance);
        visitMethodCall(methodCall);
        const auto method = instance->obj->getMethod(methodCall->name);
        methodCall->methodImpl = method;
        if (!method) return printError(E10005, methodCall, {methodCall->name, instance->name});
        selection->innerExprs[i]->type = method->type;
        resolveInnerSelection(selection, i + 1, methodCall);
    }
}

void SemaAnalyser::resolveInnerSelection(const LogosSelection* selection, const int i, LogosMethodCall* methodCall) {}

void SemaAnalyser::resolveInnerSelection(const LogosSelection* selection, const int i, LogosField* field) {}

void SemaAnalyser::resolveInnerSelection(const LogosSelection* selection, int i, LogosFuncImpl* funcImpl) {}

void SemaAnalyser::visitInstance(LogosInstance* instance) {
    const auto symbol = getSymbol(instance->name, instance);
    if (!symbol) return;
    const auto logosObject = new LogosObject(*symbol->object);
    instance->type = logosObject;
    instance->obj = logosObject;
}

void SemaAnalyser::visitArrayIndex(LogosArrayIndex* arrayIndex) {
    visitExpr(arrayIndex->baseExpr);
    arrayIndex->type = arrayIndex->baseExpr->type;
}

void SemaAnalyser::visitFuncCall(LogosFuncCall* funcCall) {
    setFuncCallType(funcCall);
    for (const auto& arg : funcCall->args) {
        visitExpr(arg);
    }
}

void SemaAnalyser::visitMethodCall(LogosMethodCall* methodCall) {
    for (const auto& arg : methodCall->args) {
        visitExpr(arg);
    }
}

void SemaAnalyser::setVariableType(LogosVariable* variable) {
    const auto symbol = getSymbol(variable->name, variable);
    if (!symbol) return;
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

void SemaAnalyser::visitConstant(const LogosConstant* constant) {}

void SemaAnalyser::setLoopVarType(const LogosForeachLoop* foreachLoop) {
    foreachLoop->loopVar->type = foreachLoop->iterableExpr->type;
    foreachLoop->loopVar->element->type = foreachLoop->loopVar->type;
    logosStack.addLocalSymbol(foreachLoop->loopVar->name, LogosSymbol(LOOP_VAR, foreachLoop->loopVar));
}

void SemaAnalyser::setArrayType(LogosArray* array) {
    // TODO add proper check for array type
    array->type = array->elements[0]->type;
}

void SemaAnalyser::setBinaryExprType(LogosBinaryExpr* binaryExpr) {
    switch (binaryExpr->op) {
    case PLUS:
    case MINUS:
    case STAR:
    case SLASH:
        binaryExpr->type = binaryExpr->left->type;
        break;
    case NOT_EQUAL:
    case DOUBLE_EQUAL:
    case LANGLE:
    case RANGLE:
    case GE:
    case LE:
        binaryExpr->type = &LOGOS_BOOL;
    case NOOP:
        break;
    }
}

void SemaAnalyser::setFuncCallType(LogosFuncCall* funcCall) {
    const auto symbol = getSymbol(funcCall->name, funcCall);
    if (!symbol) return;
    if (symbol->type == BUILTIN_FUNC) {
        funcCall->type = symbol->builtinFunc->type;
    } else if (symbol->type == FUNC_IMPL) {
        funcCall->type = symbol->funcImpl->type;
    }
}

void SemaAnalyser::setForLoopIterable(LogosForeachLoop* foreachLoop) {
    if (const auto variable = dynamic_cast<LogosVariable*>(foreachLoop->iterableExpr)) {
        setForLoopIterable(foreachLoop, variable);
    } else if (const auto array = dynamic_cast<LogosArray*>(foreachLoop->iterableExpr)) {
        foreachLoop->iterable = array;
    }
}

void SemaAnalyser::setForLoopIterable(LogosForeachLoop* foreachLoop, const LogosVariable* const variable) {
    const auto symbol = getSymbol(variable->name, variable);
    if (!symbol) return;
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
        if (const auto lastExpr = symbol->selection->lastExpr()) {
            foreachLoop->iterable = dynamic_cast<LogosIterable*>(lastExpr);
        }
        return;
    }
    default:
        return;
    }
}

void SemaAnalyser::printError(const LogosErrCode code, const LogosValue* value, const vector<string>& args) {
    LogosAnalyser::printError(code, args);
    const auto lineNumber = to_string(value->position.lineNumber);
    const auto pos = to_string(value->position.posInLine);
    const auto path = file->absPath + ":" + lineNumber + ":" + pos;
    cout << "\tat " << path << '\n';
}

LogosSymbol* SemaAnalyser::getSymbol(const string& name, const LogosValue* value) {
    const auto symbol = logosStack.getSymbol(name);
    if (!symbol) {
        printError(E10006, value, {name});
    }
    return symbol;
}

bool SemaAnalyser::matchTypes(const LogosType* first, const LogosType* second, const LogosValue* value) {
    if (second && first != second) {
        printError(E10001, value, {first->getName(), second->getName()});
        return false;
    }
    return true;
}