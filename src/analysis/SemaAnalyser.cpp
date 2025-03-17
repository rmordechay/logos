#include "SemaAnalyser.h"
#include "LgsErrors.h"
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

void SemaAnalyser::visitMainFunc(LgsFuncImpl* mainFunc) {
    visitFuncImpl(mainFunc);
}

void SemaAnalyser::visitFuncImpl(LgsFuncImpl* func) {
    logosStack.enterScope();
    setFuncType(func);
    for (const auto& param : func->params) {
        visitParam(param);
    }
    visitStmtBlock(func->stmtBlock);
    logosStack.exitScope();
}

void SemaAnalyser::visitMethodImpl(LgsMethodImpl* method, LgsObject* obj) {
    logosStack.enterScope();
    setFuncType(method);
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
    // TODO check all loop vars
    const auto loopVar = rangeLoop->loopVars[0];
    addLocalSymbol(loopVar->name, LgsSymbol(VAR_DEC, loopVar));
    visitStmtBlock(rangeLoop->stmtBlock);
}

void SemaAnalyser::visitForeachLoop(const LgsForeachLoop* foreachLoop) {
    visitExpr(foreachLoop->iterable);
    if (foreachLoop->getExprAsIterable() == nullptr) {
        printError(E10002, &foreachLoop->iterable->location, {foreachLoop->iterable->getName()});
        return;
    }
    // TODO check all loop vars
    const auto loopVar = foreachLoop->loopVars[0];
    addLocalSymbol(loopVar->name, LgsSymbol(VAR_DEC, loopVar));
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
    setExprType(array, array->elements[0]->type);
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
            setExprType(nextExpr, field->type);
        } else if (const auto method = currentExpr->type->getMethod(nextExpr->getName())) {
            const auto methodCall = dynamic_cast<LgsFuncCall*>(nextExpr);
            methodCall->func = method;
            methodCall->args.insert(methodCall->args.begin(), currentExpr);
            setExprType(nextExpr, method->type);
        }
    }
    setExprType(selection, selection->lastExpr()->type);
}

void SemaAnalyser::resolveSelectionVariable(LgsVariable* variable) {
    visitVariable(variable);
    const auto currentSymbol = logosStack.getSymbol(variable->name);
    if (currentSymbol->type == VAR_DEC) {
        const auto varDec = currentSymbol->varDec;
        setExprType(variable, varDec->type);
    }
    if (currentSymbol->type == PARAM) {
        const auto param = currentSymbol->param;
        setExprType(variable, param->type);
    }
}

void SemaAnalyser::visitInstance(LgsInstance* instance) {
    const auto symbol = getSymbol(instance->name, instance);
    if (!symbol) return;

    instance->obj = symbol->object;
    instance->type = instance->obj;
    for (const auto& [name, field] : instance->obj->fields) {
        instance->fields[name] = new LgsField(*field);
    }
}

void SemaAnalyser::visitArrayIndex(LgsArrayIndex* arrayIndex) {
    visitExpr(arrayIndex->baseExpr);
    setExprType(arrayIndex, arrayIndex->baseExpr->type);
}

void SemaAnalyser::visitFuncCall(LgsFuncCall* funcCall) {
    for (const auto& arg : funcCall->args) {
        visitExpr(arg);
    }
    funcCall->setComposedName();
    const auto symbol = getSymbol(funcCall->composedName, funcCall);
    if (!symbol || symbol->type != FUNC) return;
    funcCall->func = symbol->func;
    setExprType(funcCall, symbol->func->type);
}

void SemaAnalyser::setVariableType(LgsVariable* variable) {
    const auto symbol = getSymbol(variable->name, variable);
    if (!symbol) return;
    switch (symbol->type) {
    case VAR_DEC:
        setExprType(variable, symbol->varDec->type);
        break;
    case PARAM:
        setExprType(variable, symbol->param->type);
        break;
    default:
        assert(false && "setVariableType not implemented");
    }
}

void SemaAnalyser::visitConstant(const LgsConst* constant) const {}

void SemaAnalyser::setFuncType(LgsFunc* func) {
    const auto symbol = logosStack.getSymbol(func->type->getName());
    if (symbol && symbol->type == OBJECT && symbol->object != func->type) {
        delete func->type;
        func->type = symbol->object;
    }
}

void SemaAnalyser::setExprType(LgsExpr* expr, LgsType* type) {
    const auto symbol = logosStack.getSymbol(type->getName());
    if (symbol && symbol->type == OBJECT && symbol->object != type) {
        delete type;
        expr->type = symbol->object;
    } else {
        expr->type = type;
    }
}

void SemaAnalyser::setBinaryExprType(LgsBinaryExpr* binaryExpr) {
    switch (binaryExpr->op) {
    case ADD:
    case SUB:
    case MUL:
    case DIV: {
        const auto lType = binaryExpr->left->type;
        const auto rType = binaryExpr->right->type;
        setExprType(binaryExpr, lType->inferBinaryType(rType));
        break;
    }
    case NE:
    case EQ:
    case LT:
    case GT:
    case GE:
    case LE: {
        setExprType(binaryExpr, &LOGOS_BOOL);
        return;
    }
    case NOOP:
        break;
    }
}

bool SemaAnalyser::checkExprType(const LgsExpr* expr, const LgsType* otherType) {
    if (expr && otherType && !otherType->equals(expr->type)) {
        printError(E10001, &expr->location, {otherType->getName(), expr->type->getName()});
        return false;
    }
    return true;
}

void SemaAnalyser::printError(const LgsErrCode code, const Location* location, const vector<string>& args) {
    auto errMsg = formatErrorMsg(code, args);
    const auto lineNumber = to_string(location->lineNumber);
    const auto pos = to_string(location->posInLine);
    const auto path = file->absPath + ":" + lineNumber + ":" + pos;
    errMsg += "\tat " + path + '\n';
    cout << errMsg << endl;
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