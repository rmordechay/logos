#include "SemaAnalyser.h"
#include "LgsErrors.h"
#include "exprs/LgsNull.h"
#include "stmts/LgsField.h"
#include "stmts/LgsReturn.h"
#include "types/LgsArrayType.h"
#include "types/LgsBool.h"

#include <ThreadPool.h>
#include "exprs/unary/LgsArray.h"
#include "exprs/unary/LgsArrayIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/binary/LgsBinaryExpr.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsEnum.h"
#include "stmts/LgsPatternMatching.h"

#include <funcs/LgsPrint.h>
#include <loops/LgsForeachLoop.h>
#include <loops/LgsLoop.h>
#include <loops/LgsRangeLoop.h>
#include <stmts/LgsAssignment.h>
#include <stmts/LgsIfStmt.h>

void SemaAnalyser::analyse() {
    if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
        visitMainFile(mainFile);
    } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
        visitObjectFile(objFile);
    }
}

void SemaAnalyser::visitMainFile(const LgsMainFile* mainFile) {
    for (const auto& lgsEnum : mainFile->enums) {
        visitEnum(lgsEnum);
    }
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
        for (const auto& overload : method) {
            visitMethodImpl(overload, obj);
        }
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
    } else if (const auto ifStmt = dynamic_cast<LgsIfStmt*>(stmt)) {
        visitIfStmt(ifStmt);
    } else if (const auto patternMatching = dynamic_cast<LgsPatternMatching*>(stmt)) {
        visitPatternMatching(patternMatching);
    } else if (const auto loopStmt = dynamic_cast<LgsLoop*>(stmt)) {
        visitLoopStmt(loopStmt);
    } else if (const auto fieldDef = dynamic_cast<LgsAssignment*>(stmt)) {
        visitAssignment(fieldDef);
    } else if (const auto funcCall = dynamic_cast<LgsFuncCall*>(stmt)) {
        visitFuncCall(funcCall);
    } else if (const auto selection = dynamic_cast<LgsSelection*>(stmt)) {
        visitSelection(selection);
    } else if (const auto returnStmt = dynamic_cast<LgsReturn*>(stmt)) {
        visitReturnStmt(returnStmt);
    } else if (const auto enumDec = dynamic_cast<LgsEnum*>(stmt)) {
        visitEnum(enumDec);
    }
}

void SemaAnalyser::visitStmtBlock(const LgsStmtBlock* stmtBlock) {
    if (!stmtBlock) return;
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
    if (!expr) {
        varDec->type = userType;
        varDec->expr = varDec->type->getZeroValue();
    } else if (dynamic_cast<LgsNull*>(expr) && userType->nullable) {
        varDec->type = userType;
    } else {
        visitExpr(expr);
        if (!checkExprType(expr, userType)) return;
        varDec->type = expr->type;
    }
    addLocalSymbol(varDec->name, LgsSymbol(VAR_DEC, varDec));
}

void SemaAnalyser::visitIfStmt(const LgsIfStmt* ifStmt) {
    visitExpr(ifStmt->ifCond);
    visitStmtBlock(ifStmt->ifStmtBlock);
    for (const auto& elseIfStmtBlock : ifStmt->elseIfStmtBlocks) {
        visitStmtBlock(elseIfStmtBlock);
    }
    visitStmtBlock(ifStmt->elseStmtBlock);
}

void SemaAnalyser::visitPatternMatching(const LgsPatternMatching* patternMatching) {
    const auto baseExpr = patternMatching->expr;
    if (!baseExpr) {
        visitBoolPatternMatching(patternMatching);
        return;
    }
    visitExpr(baseExpr);
    const auto baseExprType = baseExpr->type;
    for (const auto patternExpr : patternMatching->patterns) {
        visitExpr(patternExpr);
        if (!patternExpr->type->equals(baseExprType)) {
            handleError(E10014, &patternExpr->location, {patternExpr->type->getName(), baseExprType->getName()});
            return;
        }
    }
    for (const auto& patternsStmtBlock : patternMatching->patternsStmtBlocks) {
        visitStmtBlock(patternsStmtBlock);
    }
    visitStmtBlock(patternMatching->elseStmtBlock);
}

void SemaAnalyser::visitBoolPatternMatching(const LgsPatternMatching* patternMatching) {

}

void SemaAnalyser::visitLoopStmt(LgsLoop* loopStmt) {
    logosStack.enterScope();
    if (const auto rangeLoop = dynamic_cast<LgsRangeLoop*>(loopStmt)) {
        visitRangeLoop(rangeLoop);
    } else if (const auto foreachLoop = dynamic_cast<LgsForeachLoop*>(loopStmt)) {
        visitForeachLoop(foreachLoop);
    }
    logosStack.exitScope();
}

void SemaAnalyser::visitRangeLoop(const LgsRangeLoop* rangeLoop) {
    // TODO check all loop vars
    const auto loopVar = rangeLoop->loopVars[0];
    addLocalSymbol(loopVar->name, LgsSymbol(VAR_DEC, loopVar));
    visitStmtBlock(rangeLoop->stmtBlock);
}

void SemaAnalyser::visitForeachLoop(const LgsForeachLoop* foreachLoop) {
    const auto iterableExpr = foreachLoop->iterableExpr;
    visitUnaryExpr(iterableExpr);
    if (!foreachLoop->getExprAsIterable()) {
        handleError(E10002, &iterableExpr->location, {iterableExpr->getName()});
        return;
    }
    // TODO check all loop vars
    const auto loopVar = foreachLoop->loopVars[0];
    loopVar->type = dynamic_cast<LgsArrayType*>(iterableExpr->type)->underlyingType;
    addLocalSymbol(loopVar->name, LgsSymbol(VAR_DEC, loopVar));
    visitStmtBlock(foreachLoop->stmtBlock);
}

void SemaAnalyser::visitReturnStmt(const LgsReturn* returnStmt) {
    visitExpr(returnStmt->expr);
}

void SemaAnalyser::visitEnum(LgsEnum* lgsEnum) {

}

void SemaAnalyser::visitExpr(LgsExpr* expr) {
    if (const auto unaryExpr = dynamic_cast<LgsUnaryExpr*>(expr)) {
        visitUnaryExpr(unaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
    }
}

void SemaAnalyser::visitArray(const LgsArray* array) {
    for (const auto& element : array->elements) {
        visitExpr(element);
    }
    if (const auto arrayType = dynamic_cast<LgsArrayType*>(array->type)) {
        arrayType->underlyingType = array->elements[0]->type;
    }
}

void SemaAnalyser::visitUnaryExpr(LgsUnaryExpr* unaryExpr) {
    if (const auto instance = dynamic_cast<LgsInstance*>(unaryExpr)) {
        visitInstance(instance);
    } else if (const auto funcCall = dynamic_cast<LgsFuncCall*>(unaryExpr)) {
        visitFuncCall(funcCall);
    } else if (const auto selection = dynamic_cast<LgsSelection*>(unaryExpr)) {
        visitSelection(selection);
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
    } else {
        assert(false && "first selection case not implemented");
    }
    if (!successful) return;

    for (int i = 0; i < exprs.size() - 1; ++i) {
        const auto currentExpr = exprs[i];
        const auto nextExpr = exprs[i + 1];
        if (const auto field = currentExpr->type->getField(nextExpr->getName())) {
            setExprType(nextExpr, field->type);
            continue;
        }
        if (const auto methodCall = dynamic_cast<LgsFuncCall*>(nextExpr)) {
            methodCall->setComposedName();
            const auto method = currentExpr->type->getMethod(methodCall);
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
    const auto arrType = dynamic_cast<LgsArrayType*>(arrayIndex->baseExpr->type);
    if (!arrType) {
        handleError(E10002, &arrayIndex->location, {arrayIndex->getName()});
        return;
    }
    setExprType(arrayIndex, arrType->underlyingType);
}

void SemaAnalyser::visitFuncCall(LgsFuncCall* funcCall) {
    for (const auto& arg : funcCall->args) {
        visitExpr(arg);
    }
    funcCall->setComposedName();
    const auto func = getFunc(funcCall);
    if (!func) return;
    funcCall->func = func;
    setExprType(funcCall, func->type);
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

void SemaAnalyser::setFuncType(LgsFunc* func) {
    if (dynamic_cast<LgsUnknownType*>(func->type)) {
        const auto symbol = logosStack.getSymbol(func->type->getName());
        delete func->type;
        func->type = symbol->object;
    }
}

void SemaAnalyser::setExprType(LgsExpr* expr, LgsType* type) {
    if (dynamic_cast<LgsUnknownType*>(type)) {
        const auto symbol = logosStack.getSymbol(type->getName());
        expr->type = symbol->object;
        delete type;
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
        if (!lType || !rType) return;
        setExprType(binaryExpr, lType->inferBinaryType(rType));
        break;
    }
    case NE:
    case EQ:
    case LT:
    case GT:
    case GE:
    case LE: {
        setExprType(binaryExpr, new LgsBool());
        return;
    }
    case NOOP:
        break;
    }
}

bool SemaAnalyser::checkExprType(LgsExpr* expr, LgsType* userType) {
    if (expr && userType) {
        if (expr->type && !expr->type->equals(userType)) {
            handleError(E10001, &expr->location, {userType->getName(), expr->type->getName()});
            return false;
        }
    }
    return true;
}

void SemaAnalyser::handleError(const LgsError& lgsErr, const Location* location, const vector<string>& args) {
    const auto errMsg = formatErrorMsg(lgsErr.msg, args);
    errors.emplace_back(LgsError{.errCode = lgsErr.errCode, .msg = errMsg});

    const auto lineNumber = to_string(location->lineNumber);
    const auto pos = to_string(location->posInLine);
    const auto path = "\tat " + file->absPath + ":" + lineNumber + ":" + pos;

    cout << errMsg << '\n' << path << '\n';
}

LgsSymbol* SemaAnalyser::getSymbol(const string& name, const LgsValue* value) {
    const auto symbol = logosStack.getSymbol(name);
    if (!symbol) {
        handleError(E10006, &value->location, {name});
    }
    return symbol;
}

LgsFunc* SemaAnalyser::getFunc(const LgsFuncCall* funcCall) {
    const auto symbol = logosStack.getFunc(funcCall);
    if (!symbol) {
        handleError(E10006, &funcCall->location, {funcCall->name});
    }
    return symbol;
}

void SemaAnalyser::addLocalSymbol(const string&name, const LgsSymbol& symbol) {
    if (const auto s = logosStack.getSymbol(name)) {
        const auto symbolPosition = getSymbolLocation(s);
        handleError(E10011, &symbol.varDec->location, {name, to_string(symbolPosition->lineNumber)});
        return;
    }
    logosStack.addLocalSymbol(name, symbol);
}

Location* SemaAnalyser::getSymbolLocation(const LgsSymbol* symbol) const {
    switch (symbol->type) {
    case VAR_DEC:
        return &symbol->varDec->location;
    case PARAM:
        return &symbol->param->location;
    case FUNC:
        return &symbol->func->location;
    default:
        return nullptr;
    }
}