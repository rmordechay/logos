#include "SemaAnalyser.h"
#include "LgsError.h"
#include "binary/LgsBinaryExpr.h"
#include "constants/LgsStrConst.h"
#include "stmts/LgsField.h"
#include "stmts/LgsReturn.h"
#include "types/LgsBool.h"

#include <ThreadPool.h>
#include <unary/LgsArray.h>
#include <unary/LgsArrayIndex.h>
#include <unary/constants/LgsConst.h>
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
    addLocalSymbol(param->name, LgsSymbol(PARAM, param));
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

void SemaAnalyser::visitField(const LgsField* field) {
    if (!checkExprType(field->expr, field->userType)) return;
}

void SemaAnalyser::visitAssignment(const LgsAssignment* assignment) {
    if (const auto selection = dynamic_cast<LgsSelection*>(assignment->lvalue)) {
        visitSelection(selection);
    }
    visitExpr(assignment->rvalue);
    if (!checkExprType(assignment->rvalue, assignment->lvalue->type)) return;
}

void SemaAnalyser::visitVarDec(LgsVarDec* varDec) {
    const auto userType = varDec->userType;
    const auto expr = varDec->expr;
    if (expr) {
        visitExpr(expr);
        if (!checkExprType(expr, userType)) return;
        varDec->type = expr->type;
    } else {
        varDec->type = userType;
    }
    addLocalSymbol(varDec->name, LgsSymbol(VAR_DEC, varDec));
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
    // TODO free memory
    const auto varDec = new LgsVarDec(rangeLoop->loopVar->name, &LOGOS_INT);
    addLocalSymbol(name, LgsSymbol(VAR_DEC, varDec));
    visitStmtBlock(rangeLoop->stmtBlock);
}

void SemaAnalyser::visitForeachLoop(LgsForeachLoop* foreachLoop) {
    visitExpr(foreachLoop->iterableExpr);
    setForLoopIterable(foreachLoop);
    setLoopVar(foreachLoop);
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
    } else if (const auto constant = dynamic_cast<LgsConst*>(unaryExpr)) {
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
    } else if (const auto funcCall = dynamic_cast<LgsFuncCall*>(firstExpr)) {
        visitFuncCall(funcCall);
    }
    if (!successful) return;

    for (int i = 0; i < exprs.size() - 1; ++i) {
        const auto currentExpr = exprs[i];
        const auto nextExpr = exprs[i + 1];
        if (const auto field = currentExpr->type->getField(nextExpr->getName())) {
            setType(nextExpr, field->type);
        } else if (const auto method = currentExpr->type->getMethod(nextExpr->getName())) {
            const auto methodCall = dynamic_cast<LgsFuncCall*>(nextExpr);
            methodCall->func = method;
            methodCall->args.insert(methodCall->args.begin(), currentExpr);
            setType(nextExpr, method->type);
        }
    }
    setType(selection, selection->lastExpr()->type);
}

void SemaAnalyser::resolveSelectionVariable(LgsVariable* variable) {
    visitVariable(variable);
    const auto currentSymbol = logosStack.getSymbol(variable->name);
    if (currentSymbol->type == VAR_DEC) {
        const auto varDec = currentSymbol->varDec;
        setType(variable, varDec->type);
    }
    if (currentSymbol->type == PARAM) {
        const auto param = currentSymbol->param;
        setType(variable, param->type);
    }
}

void SemaAnalyser::visitInstance(LgsInstance* instance) {
    const auto symbol = getSymbol(instance->name, instance);
    if (!symbol) return;
    instance->obj = new LgsObject(*symbol->object);
    setType(instance, instance->obj);
}

void SemaAnalyser::visitArrayIndex(LgsArrayIndex* arrayIndex) {
    visitExpr(arrayIndex->baseExpr);
    setType(arrayIndex, arrayIndex->baseExpr->type);
}

void SemaAnalyser::visitFuncCall(LgsFuncCall* funcCall) {
    for (const auto& arg : funcCall->args) {
        visitExpr(arg);
    }
    funcCall->setComposedName();
    setFuncCallType(funcCall);
}

void SemaAnalyser::setVariableType(LgsVariable* variable) {
    const auto symbol = getSymbol(variable->name, variable);
    if (!symbol) return;
    switch (symbol->type) {
    case VAR_DEC:
        setType(variable, symbol->varDec->type);
        break;
    case PARAM:
        setType(variable, symbol->param->type);
        break;
    default:
        assert(false && "setVariableType not implemented");
    }
}

void SemaAnalyser::visitConstant(const LgsConst* constant) const {
}

void SemaAnalyser::setLoopVar(const LgsForeachLoop* foreachLoop) {
    setType(foreachLoop->loopVar, foreachLoop->iterableExpr->type);
    // TODO free memory
    const auto varDec = new LgsVarDec(foreachLoop->loopVar->name, &LOGOS_INT);
    addLocalSymbol(foreachLoop->loopVar->name, LgsSymbol(VAR_DEC, varDec));
}

void SemaAnalyser::setArrayType(LgsArray* array) {
    // TODO add proper check for array type
    setType(array, array->elements[0]->type);
}

void SemaAnalyser::setBinaryExprType(LgsBinaryExpr* binaryExpr) {
    switch (binaryExpr->op) {
    case ADD:
    case SUB:
    case MUL:
    case DIV: {
        const auto lType = binaryExpr->left->type;
        const auto rType = binaryExpr->right->type;
        setType(binaryExpr, lType->inferBinaryType(rType));
    }
    break;
    case NE:
    case EQ:
    case LT:
    case GT:
    case GE:
    case LE:
        setType(binaryExpr, &LOGOS_BOOL);
    case NOOP:
        break;
    }
}

void SemaAnalyser::setFuncCallType(LgsFuncCall* funcCall) {
    const auto symbol = getSymbol(funcCall->composedName, funcCall);
    if (!symbol || symbol->type != FUNC) return;
    funcCall->func = symbol->func;
    setType(funcCall, symbol->func->type);
}

void SemaAnalyser::setType(LgsExpr* expr, LgsType* type) const {
    expr->type = type;
}

void SemaAnalyser::setForLoopIterable(LgsForeachLoop* foreachLoop) {
    if (const auto variable = dynamic_cast<LgsVariable*>(foreachLoop->iterableExpr)) {
        setForLoopIterable(foreachLoop, variable);
    } else if (const auto array = dynamic_cast<LgsArray*>(foreachLoop->iterableExpr)) {
        foreachLoop->iterable = array;
    } else if (const auto str = dynamic_cast<LgsStrConst*>(foreachLoop->iterableExpr)) {
        foreachLoop->iterable = str;
    }
}

void SemaAnalyser::setForLoopIterable(LgsForeachLoop* foreachLoop, const LgsVariable* const variable) {
    const auto symbol = getSymbol(variable->name, variable);
    if (!symbol) return;
    switch (symbol->type) {
    case VAR_DEC: {
        return;
    }
    case PARAM: {
        return;
    }
    default:
        return;
    }
}

LgsSymbol* SemaAnalyser::getSymbol(const string& name, const LgsValue* value) {
    const auto symbol = logosStack.getSymbol(name);
    if (!symbol) printError(E10006, &value->location, {name});
    return symbol;
}

void SemaAnalyser::addLocalSymbol(const string&name, const LgsSymbol& symbol) {
    if (const auto s = logosStack.getSymbol(name)) {
        const auto symbolPosition = getSymbolLocation(s);
        printError(E10011, &symbol.varDec->location, {name, to_string(symbolPosition->lineNumber)});
        return;
    }
    logosStack.addLocalSymbol(name, symbol);
}

bool SemaAnalyser::checkExprType(const LgsExpr* expr, const LgsType* otherType) {
    if (expr && otherType && !otherType->equals(expr->type)) {
        printError(E10001, &expr->location, {otherType->getName(), expr->type->getName()});
        return false;
    }
    return true;
}

void SemaAnalyser::printError(const LgsErrCode code, const Location* location, const vector<string>& args) {
    LgsAnalyser::printError(code, args);
    const auto lineNumber = to_string(location->lineNumber);
    const auto pos = to_string(location->posInLine);
    const auto path = file->absPath + ":" + lineNumber + ":" + pos;
    cout << "\tat " << path << '\n';
}

Location* SemaAnalyser::getSymbolLocation(const LgsSymbol* s) const {
    switch (s->type) {
    case VAR_DEC:
        return &s->varDec->location;
    case PARAM:
        return &s->param->location;
    case FUNC:
        return &s->func->location;
    default:
        return nullptr;
    }
}
