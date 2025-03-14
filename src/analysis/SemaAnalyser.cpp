#include "SemaAnalyser.h"
#include "LgsError.h"
#include "binary/LgsBinaryExpr.h"
#include "constants/LgsStringConst.h"
#include "unary/LgsMethodCall.h"
#include "loops/LgsLoopVar.h"
#include "stmts/LgsField.h"
#include "stmts/LgsReturn.h"
#include "types/LgsBool.h"

#include <ThreadPool.h>
#include <unary/LgsArray.h>
#include <unary/LgsArrayIndex.h>
#include <unary/constants/LgsConstant.h>
#include <unary/LgsFuncCall.h>
#include <unary/LgsInstance.h>
#include <unary/LgsSelection.h>
#include <unary/LgsVariable.h>
#include <funcs/LgsPrint.h>
#include <loops/LgsForeachLoop.h>
#include <loops/LogosLoop.h>
#include <loops/LgsRangeLoop.h>
#include <stmts/LgsAssignment.h>
#include <stmts/LgsIf.h>

void SemaAnalyser::analyse() {
    if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
        visitMainFile(mainFile);
    } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
        visitObjectFile(objFile);
    }
}

void SemaAnalyser::visitMainFile(const LgsMainFile* mainFile) {
    for (const auto& func : mainFile->funcs) {
        visitFuncImpl(func);
    }
    visitMainFunc(mainFile->mainFunc);
}

void SemaAnalyser::visitObjectFile(const LgsObjectFile* objectFile) {
    visitObject(objectFile->obj);
}

void SemaAnalyser::visitObject(LgsObject* obj) {
    for (const auto& [_, field] : obj->fields) {
        visitField(field);
    }
    for (const auto& [_, method] : obj->methods) {
        visitMethodImpl(method, obj);
    }
}

void SemaAnalyser::visitMainFunc(const LgsFuncImpl* mainFunc) {
    visitFuncImpl(mainFunc);
}

void SemaAnalyser::visitFuncImpl(const LgsFuncImpl* func) {
    logosStack.enterScope();
    for (const auto& param : func->params) {
        visitParam(param);
    }
    visitStmtBlock(func->stmtBlock);
    logosStack.exitScope();
}

void SemaAnalyser::visitMethodImpl(LgsMethodImpl* method, LgsObject* obj) {
    logosStack.enterScope();
    const auto self = new LgsParam(LOGOS_SELF, obj, new LgsInstance(obj->name));
    method->params.insert(method->params.begin(), self);
    for (const auto& param : method->params) {
        visitParam(param);
    }
    visitStmtBlock(method->stmtBlock);
    logosStack.exitScope();
}

void SemaAnalyser::visitParam(LgsParam* param) {
    logosStack.addLocalSymbol(param->name, LgsSymbol(PARAM, param));
}

void SemaAnalyser::visitStmt(LgsStmt* stmt) {
    if (const auto varDec = dynamic_cast<LgsVarDec*>(stmt)) {
        visitVarDec(varDec);
    } else if (const auto ifStmt = dynamic_cast<LgsIf*>(stmt)) {
        visitIfStmt(ifStmt);
    } else if (const auto loopStmt = dynamic_cast<LgsLoop*>(stmt)) {
        visitLoopStmt(loopStmt);
    } else if (const auto fieldDef = dynamic_cast<LgsAssignment*>(stmt)) {
        visitAssignment(fieldDef);
    } else if (const auto funcCall = dynamic_cast<LgsFuncCall*>(stmt)) {
        visitFuncCall(funcCall);
    } else if (const auto returnStmt = dynamic_cast<LgsReturn*>(stmt)) {
        visitReturnStmt(returnStmt);
    }
}

void SemaAnalyser::visitStmtBlock(const LgsStmtBlock* stmtBlock) {
    for (const auto& stmt : stmtBlock->stmts) {
        visitStmt(stmt);
    }
}

void SemaAnalyser::visitField(LgsField* field) {}

void SemaAnalyser::visitAssignment(const LgsAssignment* assignment) {}

void SemaAnalyser::visitVarDec(LgsVarDec* varDec) {
    const auto userType = varDec->userType;
    const auto expr = varDec->expr;
    if (expr) {
        visitExpr(expr);
        if (!matchTypes(expr->type, userType, expr)) return;
        varDec->type = expr->type;
    } else {
        varDec->type = userType;
    }
    logosStack.addLocalSymbol(varDec->name, LgsSymbol(VAR_DEC, varDec));
}

void SemaAnalyser::visitIfStmt(const LgsIf* ifStmt) {
    visitExpr(ifStmt->ifCond);
    visitStmtBlock(ifStmt->ifStmtBlock);
}

void SemaAnalyser::visitLoopStmt(LgsLoop* loopStmt) {
    if (const auto rangeLoop = dynamic_cast<LgsRangeLoop*>(loopStmt)) {
        visitRangeLoop(rangeLoop);
    } else if (const auto foreachLoop = dynamic_cast<LgsForeachLoop*>(loopStmt)) {
        visitForeachLoop(foreachLoop);
    }
}

void SemaAnalyser::visitRangeLoop(const LgsRangeLoop* rangeLoop) {
    const auto name = rangeLoop->loopVar->name;
    logosStack.addLocalSymbol(name, LgsSymbol(LOOP_VAR, rangeLoop->loopVar));
    visitStmtBlock(rangeLoop->stmtBlock);
}

void SemaAnalyser::visitForeachLoop(LgsForeachLoop* foreachLoop) {
    visitExpr(foreachLoop->iterableExpr);
    setForLoopIterable(foreachLoop);
    setLoopVarType(foreachLoop);
    visitStmtBlock(foreachLoop->stmtBlock);
}

void SemaAnalyser::visitReturnStmt(const LgsReturn* returnStmt) {
    visitExpr(returnStmt->expr);
}

void SemaAnalyser::visitExpr(LgsExpr* expr) {
    if (const auto unaryExpr = dynamic_cast<LgsUnaryExpr*>(expr)) {
        visitUnaryExpr(unaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
    }
}

void SemaAnalyser::visitArray(LgsArray* array) {
    for (const auto& element : array->elements) {
        visitExpr(element);
    }
    setArrayType(array);
}

void SemaAnalyser::visitUnaryExpr(LgsUnaryExpr* unaryExpr) {
    if (const auto instance = dynamic_cast<LgsInstance*>(unaryExpr)) {
        visitInstance(instance);
    } else if (const auto funcCall = dynamic_cast<LgsFuncCall*>(unaryExpr)) {
        visitFuncCall(funcCall);
    } else if (const auto selection = dynamic_cast<LgsSelection*>(unaryExpr)) {
        visitSelection(selection);
    } else if (const auto constant = dynamic_cast<LgsConstant*>(unaryExpr)) {
        visitConstant(constant);
    } else if (const auto array = dynamic_cast<LgsArray*>(unaryExpr)) {
        visitArray(array);
    } else if (const auto arrIndex = dynamic_cast<LgsArrayIndex*>(unaryExpr)) {
        visitArrayIndex(arrIndex);
    } else if (const auto variable = dynamic_cast<LgsVariable*>(unaryExpr)) {
        visitVariable(variable);
    }
}

void SemaAnalyser::visitBinaryExpr(LgsBinaryExpr* binaryExpr) {
    visitExpr(binaryExpr->left);
    visitExpr(binaryExpr->right);
    setBinaryExprType(binaryExpr);
}

void SemaAnalyser::visitVariable(LgsVariable* variable) {
    setVariableType(variable);
}

void SemaAnalyser::visitSelection(LgsSelection* selection) {
    const auto exprs = selection->exprs;
    const auto firstExpr = exprs[0];
    if (const auto variable = dynamic_cast<LgsVariable*>(firstExpr)) {
        visitVariable(variable);
    }

    for (int i = 0; i < exprs.size() - 1; ++i) {
        const auto currentExpr = exprs[i];
        const auto nextExpr = exprs[i + 1];
        if (const auto field = currentExpr->type->getField(nextExpr->getName())) {
            nextExpr->type = field->type;
        } else if (const auto method = currentExpr->type->getMethod(nextExpr->getName())) {
            const auto methodCall = dynamic_cast<LgsMethodCall*>(nextExpr);
            methodCall->args.insert(methodCall->args.begin(), currentExpr);
            nextExpr->type = method->type;
        }
    }
    selection->type = selection->lastExpr()->type;
}

void SemaAnalyser::resolveSelectionVariable(LgsVariable* variable) {
    visitVariable(variable);
    const auto currentSymbol = logosStack.getSymbol(variable->name);
    if (currentSymbol->type == VAR_DEC) {
        const auto varDec = currentSymbol->varDec;
        variable->type = varDec->type;
    }
    if (currentSymbol->type == PARAM) {
        const auto param = currentSymbol->param;
        variable->type = param->type;
    }
}

void SemaAnalyser::visitInstance(LgsInstance* instance) {
    const auto symbol = getSymbol(instance->name, instance);
    if (!symbol) return;
    instance->obj = new LgsObject(*symbol->object);
    instance->type = instance->obj;
}

void SemaAnalyser::visitArrayIndex(LgsArrayIndex* arrayIndex) {
    visitExpr(arrayIndex->baseExpr);
    arrayIndex->type = arrayIndex->baseExpr->type;
}

void SemaAnalyser::visitFuncCall(LgsFuncCall* funcCall) {
    setFuncCallType(funcCall);
    for (const auto& arg : funcCall->args) {
        visitExpr(arg);
    }
}

void SemaAnalyser::setVariableType(LgsVariable* variable) {
    const auto symbol = getSymbol(variable->name, variable);
    if (!symbol) return;
    switch (symbol->type) {
    case VAR_DEC:
        variable->type = symbol->varDec->type;
        break;
    case LOOP_VAR:
        variable->type = symbol->loopVar->type;
        break;
    case PARAM:
        variable->type = symbol->param->type;
        break;
    default:
        assert(false && "setVariableType not implemented");
    }
}

void SemaAnalyser::visitConstant(const LgsConstant* constant) {
}

void SemaAnalyser::setLoopVarType(const LgsForeachLoop* foreachLoop) {
    foreachLoop->loopVar->type = foreachLoop->iterableExpr->type;
    foreachLoop->loopVar->element->type = foreachLoop->loopVar->type;
    logosStack.addLocalSymbol(foreachLoop->loopVar->name, LgsSymbol(LOOP_VAR, foreachLoop->loopVar));
}

void SemaAnalyser::setArrayType(LgsArray* array) {
    // TODO add proper check for array type
    array->type = array->elements[0]->type;
}

void SemaAnalyser::setBinaryExprType(LgsBinaryExpr* binaryExpr) {
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

void SemaAnalyser::setFuncCallType(LgsFuncCall* funcCall) {
    const auto symbol = getSymbol(funcCall->name, funcCall);
    if (!symbol) return;
    if (symbol->type == BUILTIN_FUNC) {
        funcCall->type = symbol->builtinFunc->type;
    } else if (symbol->type == FUNC_IMPL) {
        funcCall->type = symbol->funcImpl->type;
    }
}

void SemaAnalyser::setForLoopIterable(LgsForeachLoop* foreachLoop) {
    if (const auto variable = dynamic_cast<LgsVariable*>(foreachLoop->iterableExpr)) {
        setForLoopIterable(foreachLoop, variable);
    } else if (const auto array = dynamic_cast<LgsArray*>(foreachLoop->iterableExpr)) {
        foreachLoop->iterable = array;
    } else if (const auto str = dynamic_cast<LgsStringConst*>(foreachLoop->iterableExpr)) {
        foreachLoop->iterable = str;
    }
}

void SemaAnalyser::setForLoopIterable(LgsForeachLoop* foreachLoop, const LgsVariable* const variable) {
    const auto symbol = getSymbol(variable->name, variable);
    if (!symbol) return;
    switch (symbol->type) {
    case VAR_DEC: {
        const auto a = dynamic_cast<LgsConstant*>(symbol->varDec->expr);
        const auto lgsStringConst = get_if<LgsStringConst*>(&a->value);
        foreachLoop->iterable = *lgsStringConst;
        return;
    }
    case LOOP_VAR: {
        foreachLoop->iterable = dynamic_cast<LgsIterable*>(symbol->loopVar->element);
        return;
    }
    case FIELD: {
        foreachLoop->iterable = dynamic_cast<LgsIterable*>(symbol->field->expr);
        return;
    }
    case SELECTION: {
        if (const auto lastExpr = symbol->selection->lastExpr()) {
            foreachLoop->iterable = dynamic_cast<LgsIterable*>(lastExpr);
        }
        return;
    }
    default:
        return;
    }
}

void SemaAnalyser::printError(const LgsErrCode code, const LgsValue* value, const vector<string>& args) {
    LgsAnalyser::printError(code, args);
    const auto lineNumber = to_string(value->position.lineNumber);
    const auto pos = to_string(value->position.posInLine);
    const auto path = file->absPath + ":" + lineNumber + ":" + pos;
    cout << "\tat " << path << '\n';
}

LgsSymbol* SemaAnalyser::getSymbol(const string& name, const LgsValue* value) {
    const auto symbol = logosStack.getSymbol(name);
    if (!symbol) {
        printError(E10006, value, {name});
    }
    return symbol;
}

bool SemaAnalyser::matchTypes(const LgsType* first, const LgsType* second, const LgsValue* value) {
    if (second && first != second) {
        printError(E10001, value, {first->getName(), second->getName()});
        return false;
    }
    return true;
}
