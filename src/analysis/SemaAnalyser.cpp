#include "analysis/SemaAnalyser.h"
#include "funcs/LgsCoroutine.h"
#include "configs/LgsErrors.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsObjectFile.h"
#include "exprs/unary/LgsCast.h"
#include "stmts/LgsField.h"
#include "stmts/LgsReturn.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/LgsBinaryExpr.h"
#include "types/LgsEnum.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsPostfixExpr.h"
#include "exprs/unary/LgsPrefixExpr.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "files/LgsMainFile.h"
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/unary/constants/LgsLongConst.h"
#include "utils/LgsErrHandler.h"
#include "loops/LgsInfiniteLoop.h"
#include "loops/LgsWhileLoop.h"
#include "stmts/LgsBreak.h"
#include "stmts/LgsContinue.h"
#include "stmts/LgsDeferStmt.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsDArray.h"
#include "types/LgsGroup.h"
#include "types/LgsInterface.h"
#include "types/LgsNullable.h"
#include "types/LgsUnknownType.h"
#include "utils/LgsUtils.h"
#include "loops/LgsForeachLoop.h"
#include "loops/LgsForLoop.h"
#include "loops/LgsRangeLoop.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsIfStmt.h"

void SemaAnalyser::analyse() {
    if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
        visitMainFile(mainFile);
    } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
        visitObject(objFile->obj);
    } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
        visitInterface(interfaceFile->interface);
    }
}

void SemaAnalyser::visitMainFile(LgsMainFile* mainFile) {
    for (const auto obj : mainFile->objects) {
        visitObject(obj);
    }
    for (const auto group : mainFile->groups) {
        visitGroup(group);
    }
    for (const auto& [_, func] : mainFile->funcs) {
        visitFunc(func);
    }
    if (mainFile->funcs.find(LGS_MAIN_FUNC_NAME) == mainFile->funcs.end()) {
        errHandler.addError(E10000, &file->location);
    }
}

void SemaAnalyser::visitObject(LgsObject* obj) {
    for (const auto& [_, field] : obj->fields) {
        visitField(field);
    }
    for (const auto& [_, method] : obj->methods) {
        visitFunc(method);
    }
    validateObjImplements(obj, obj->interfaces);
}

void SemaAnalyser::visitInterface(LgsInterface* interface) {
    for (const auto& [_, field] : interface->fields) {
        visitField(field);
    }
    for (const auto& [_, method] : interface->methods) {
        visitFunc(method);
    }
}

void SemaAnalyser::visitFunc(LgsFunc* func) {
    stack.enterScope(func, func->stmtsBlock);
    auto defaultParamsStarted = false;
    for (auto& param : func->funcType->params) {
        visitParam(&param);
        if (defaultParamsStarted && !param.expr) {
            errHandler.addError(E10028, &param.location);
        }
        defaultParamsStarted = !!param.expr;
    }
    visitStmtsBlock(func->stmtsBlock);
    if (func->funcType->isVariadic && func->funcType->hasDefaults) {
        errHandler.addError(E10043, &func->location);
    }
    validateFuncControlFlow(func);
    stack.exitScope();
}

void SemaAnalyser::visitParam(LgsParam* param) {
    if (param->expr) {
        visitExpr(param->expr);
        validateExprType(param->expr, param->type);
    } else if (param->isVariadic) {
        if (param->expr) {
            errHandler.addError(E10045, &param->location);
        }
        assert(0);
    }
    addLocalSymbol(LgsSymbol(param));
}

void SemaAnalyser::visitField(LgsField* field) {
    if (field->expr) {
        visitExpr(field->expr);
        validateExprType(field->expr, field->type);
    }
    if (field->type && field->type->asFuncType()) {
        errHandler.addError(E10013, &field->location, {field->name});
    }
}

bool isTerminator(LgsValue* value) {
    if (dynamic_cast<LgsBreak*>(value) || dynamic_cast<LgsContinue*>(value) || dynamic_cast<LgsReturn*>(value)) {
        return true;
    }
    const auto fc = dynamic_cast<LgsFuncCall*>(value);
    if (fc && fc->func && fc->func->funcType->isTerminator) return true;
    const auto selection = dynamic_cast<LgsSelection*>(value);
    if (!selection) return false;
    const auto methodCall = selection->lastExpr()->asFuncCall();
    if (!methodCall) return false;
    return methodCall->func && methodCall->func->funcType->isTerminator;
}

void SemaAnalyser::visitStmtsBlock(LgsStmtsBlock* stmtsBlock) {
    if (!stmtsBlock || stmtsBlock->stmts.empty()) return;
    for (const auto& stmt : stmtsBlock->stmts) {
        visitStmt(stmt);
    }
    const auto lastStmt = stmtsBlock->lastStmt();
    stmtsBlock->returnExpr = lastStmt->asReturn();
    for (int i = 0; i < stmtsBlock->stmts.size() - 1; ++i) {
        if (isTerminator(stmtsBlock->stmts[i])) {
            return errHandler.addError(E10059, &lastStmt->location);
        }
    }
}

void SemaAnalyser::visitStmt(LgsStmt* stmt) {
    if (const auto ifStmt = stmt->asIfStmt()) ifStmt->isPatternMatching ? visitPatternMatching(ifStmt) : visitIfStmt(ifStmt);
    else if (const auto varDec = stmt->asVarDec()) visitVarDec(varDec);
    else if (const auto loopStmt = stmt->asLoop()) visitLoopStmt(loopStmt);
    else if (const auto coroutine = stmt->asCoroutine()) visitCoroutine(coroutine);
    else if (const auto deferStmt = stmt->asDefer()) visitDeferStmt(deferStmt);
    else if (const auto assignment = stmt->asAssignment()) visitAssignment(assignment);
    else if (const auto funcCall = stmt->asFuncCall()) visitFuncCall(funcCall);
    else if (const auto postfixExpr = stmt->asPostfixExpr()) visitPostfixExpr(postfixExpr);
    else if (const auto selection = stmt->asSelection()) visitSelection(selection);
    else if (const auto returnStmt = stmt->asReturn()) visitReturnStmt(returnStmt);
}

void SemaAnalyser::visitVarDec(LgsVarDec* varDec) {
    if (varDec->type) {
        varDec->type = resolveType(varDec->type);
        if (!varDec->expr) {
            varDec->expr = varDec->type->getZeroValue();
            varDec->expr->location = varDec->location;
        }
    }
    if (varDec->expr) {
        visitExpr(varDec->expr);
        if (varDec->type) {
            if (!validateExprType(varDec->expr, varDec->type)) return;
            if (varDec->expr->type != varDec->type) {
                const auto castExpr = varDec->expr->castTo(varDec->type);
                if (varDec->expr != castExpr) {
                    delete varDec->expr;
                    varDec->expr = castExpr;
                }
            }
        } else {
            varDec->type = varDec->expr->type;
        }
    }
    addLocalSymbol(LgsSymbol(varDec));
}

void SemaAnalyser::visitAssignment(LgsAssignment* assignment) {
    const auto lValue = assignment->lValue;
    const auto rValue = assignment->rValue;
    visitExpr(lValue);
    visitExpr(rValue);
    if (!lValue->isMutable) return errHandler.addError(E10051, &lValue->location, {lValue->prettyName()});
    const auto lType = lValue->type;
    const auto rType = rValue->type;
    if (!lType || !rType) return;
    if (!lType->equals(rType)) {
        errHandler.addError(E10001, &assignment->location, {lType->prettyName(), rType->prettyName()});
    }
}

void SemaAnalyser::visitIfStmt(LgsIfStmt* ifStmt) {
    stack.enterScope(ifStmt, ifStmt->ifBlock);
    visitExpr(ifStmt->ifCond);
    visitStmtsBlock(ifStmt->ifBlock);
    stack.exitScope();
    for (const auto& [expr, block] : ifStmt->elseIfs) {
        stack.enterScope(ifStmt, block);
        visitExpr(expr);
        visitStmtsBlock(block);
        stack.exitScope();
    }
    if (ifStmt->elseBlock) {
        stack.enterScope(ifStmt, ifStmt->elseBlock);
        visitStmtsBlock(ifStmt->elseBlock);
        stack.exitScope();
    }
}

void SemaAnalyser::visitPatternMatching(LgsIfStmt* pm) {
    if (!pm->ifCond) {
        return visitBoolPatternMatching(pm);
    }
    const auto baseExpr = pm->ifCond;
    stack.enterScope(pm, nullptr);
    visitExpr(baseExpr);
    const auto baseExprType = baseExpr->type;
    // Allows local enum fields to not have a qualifier inside the block
    if (baseExprType->asEnum()) {
        for (const auto& [name, field] : baseExprType->fields) {
            addLocalSymbol(LgsSymbol(field));
        }
    }
    for (const auto [expr, block] : pm->elseIfs) {
        stack.enterScope(pm, block);
        visitExpr(expr);
        visitStmtsBlock(block);
        if (expr->type->isUnknown) continue;
        if (!expr->type->equals(baseExprType)) {
            return errHandler.addError(E10014, &expr->location, {expr->type->prettyName(), baseExprType->prettyName()});
        }
        stack.exitScope();
    }
    if (pm->elseBlock) {
        stack.enterScope(pm, pm->elseBlock);
        visitStmtsBlock(pm->elseBlock);
        stack.exitScope();
    }
    stack.exitScope();
}

void SemaAnalyser::visitBoolPatternMatching(LgsIfStmt* pm) {
    for (const auto [expr, block] : pm->elseIfs) {
        stack.enterScope(pm, block);
        visitExpr(expr);
        if (!expr->type->asBool()) {
            return errHandler.addError(E10057, &expr->location, {expr->prettyName()});
        }
        visitStmtsBlock(block);
        stack.exitScope();
    }
    if (pm->elseBlock) {
        stack.enterScope(pm, pm->elseBlock);
        visitStmtsBlock(pm->elseBlock);
        stack.exitScope();
    }
}

void SemaAnalyser::visitWhileLoop(LgsWhileLoop* whileLoop) {
    visitExpr(whileLoop->condExpr);
    const auto condType = whileLoop->condExpr->type;
    if (!condType->asBool()) {
        return errHandler.addError(E10066, &whileLoop->location, {whileLoop->condExpr->prettyName(), condType->prettyName()});
    }
    visitStmtsBlock(whileLoop->stmtsBlock);
}

void SemaAnalyser::visitLoopStmt(LgsForLoop* loopStmt) {
    stack.enterScope(loopStmt, loopStmt->stmtsBlock);
    if (loopStmt->isFirst) addLocalSymbol(LgsSymbol(loopStmt->isFirst));
    if (loopStmt->isLast) addLocalSymbol(LgsSymbol(loopStmt->isLast));
    if (const auto rangeLoop = dynamic_cast<LgsRangeLoop*>(loopStmt)) {
        visitRangeLoop(rangeLoop);
    } else if (const auto foreachLoop = dynamic_cast<LgsForeachLoop*>(loopStmt)) {
        visitForeachLoop(foreachLoop);
    } else if (const auto infiniteLoop = dynamic_cast<LgsInfiniteLoop*>(loopStmt)) {
        visitInfiniteLoop(infiniteLoop);
    } else if (const auto whileLoop = dynamic_cast<LgsWhileLoop*>(loopStmt)) {
        visitWhileLoop(whileLoop);
    } else {
        assert(0);
    }
    stack.exitScope();
}

void SemaAnalyser::visitRangeLoop(const LgsRangeLoop* rangeLoop) {
    const auto startRange = rangeLoop->startRange;
    const auto endRange = rangeLoop->endRange;
    visitExpr(startRange);
    visitExpr(endRange);
    if (startRange && startRange->type && !startRange->type->isNumber) {
        errHandler.addError(E10002, &startRange->location, {startRange->prettyName(), startRange->type->prettyName()});
    }
    if (endRange && endRange->type && !endRange->type->isNumber) {
        errHandler.addError(E10002, &endRange->location, {endRange->prettyName(), endRange->type->prettyName()});
    }
    addLocalSymbol(LgsSymbol(rangeLoop->loopVars.front()));
    visitStmtsBlock(rangeLoop->stmtsBlock);
}

void SemaAnalyser::visitForeachLoop(LgsForeachLoop* foreachLoop) {
    const auto iterExpr = foreachLoop->iterExpr;
    visitUnaryExpr(iterExpr);
    const auto iterable = iterExpr->type->asIterable();
    if (!iterable) {
        if (iterExpr->type) errHandler.addError(E10002, &iterExpr->location, {iterExpr->prettyName(), iterExpr->type->prettyName()});
        return;
    }
    if (setLoopVars(foreachLoop, iterExpr, iterable)) return;
    for (const auto varDec : foreachLoop->loopVars) {
        addLocalSymbol(LgsSymbol(varDec));
    }
    visitStmtsBlock(foreachLoop->stmtsBlock);
}

void SemaAnalyser::visitInfiniteLoop(const LgsInfiniteLoop* infiniteLoop) {
    if (!infiniteLoop->loopVars.empty()) {
        addLocalSymbol(LgsSymbol(infiniteLoop->loopVars.front()));
    }
    visitStmtsBlock(infiniteLoop->stmtsBlock);
}

void SemaAnalyser::visitCoroutine(const LgsCoroutine* coroutine) {
    if (coroutine->funcCall) {
        visitFuncCall(coroutine->funcCall);
    } else if (coroutine->selection) {
        visitSelection(coroutine->selection);
    } else {
        assert(0);
    }
}

void SemaAnalyser::visitDeferStmt(const LgsDeferStmt* deferStmt) {
    if (deferStmt->funcCall) visitFuncCall(deferStmt->funcCall);
    else visitSelection(deferStmt->selection);
    stack.currentFunc()->hasDefers = true;
}

void SemaAnalyser::visitReturnStmt(LgsReturn* returnStmt) {
    const auto funcType = stack.currentFunc()->funcType;
    const auto retExpr = returnStmt->expr;
    if (retExpr) {
        stack.currentFunc()->returnStmts.push_back(returnStmt);
        visitExpr(retExpr);
    }
    const auto rt = funcType->rt;
    if (rt->isVoid && retExpr && retExpr->type && !retExpr->type->isVoid) {
        errHandler.addError(E10027, &returnStmt->location, {retExpr->type->prettyName()});
    } else if (!rt->isVoid && !retExpr) {
        errHandler.addError(E10026, &returnStmt->location, {funcType->name, rt->prettyName()});
    } else if (retExpr && retExpr->type && !rt->equals(retExpr->type)) {
        errHandler.addError(E10004, &returnStmt->location, {funcType->name, rt->prettyName(), retExpr->type->prettyName()});
    }
}

void SemaAnalyser::visitExpr(LgsExpr* expr) {
    if (!expr) return;
    if (const auto castExpr = dynamic_cast<LgsCast*>(expr)) {
        visitCast(castExpr);
    } else if (const auto unaryExpr = dynamic_cast<LgsUnaryExpr*>(expr)) {
        visitUnaryExpr(unaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
    }
    if (expr->isHeapAlloc) {
        stack.addHeapAllocExpr(expr);
    }
}

void SemaAnalyser::visitCast(LgsCast* castExpr) {
    const auto fromValue = castExpr->fromValue;
    if (const auto unaryExpr = dynamic_cast<LgsUnaryExpr*>(fromValue)) {
        visitUnaryExpr(unaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(fromValue)) {
        visitBinaryExpr(binaryExpr);
    }
    castExpr->toType = resolveType(castExpr->toType);
    castExpr->toValue = fromValue->castTo(castExpr->toType);
    if (!castExpr->toValue) {
        errHandler.addError(E10018, &castExpr->location, {fromValue->type->prettyName(), castExpr->toType->prettyName()});
    }
}

void SemaAnalyser::visitUnaryExpr(LgsUnaryExpr* unaryExpr) {
    if (const auto instance = unaryExpr->asInstance()) visitInstance(instance);
    else if (const auto funcCall = unaryExpr->asFuncCall()) visitFuncCall(funcCall);
    else if (const auto strConst = unaryExpr->asStrConst()) visitStrConst(strConst);
    else if (const auto func = unaryExpr->asFunc()) visitFunc(func);
    else if (const auto selection = unaryExpr->asSelection()) visitSelection(selection);
    else if (const auto arrayExpr = unaryExpr->asArrayExpr()) visitArrayExpr(arrayExpr);
    else if (const auto hashMap = unaryExpr->asHashMap()) visitHashMap(hashMap);
    else if (const auto iterIndex = unaryExpr->asIterIndex()) visitIterIndex(iterIndex);
    else if (const auto variable = unaryExpr->asVariable()) visitVariable(variable);
    else if (const auto postfixExpr = unaryExpr->asPostfixExpr()) visitPostfixExpr(postfixExpr);
    else if (const auto prefixExpr = unaryExpr->asPrefixExpr()) visitPrefixExpr(prefixExpr);
}

void SemaAnalyser::visitBinaryExpr(LgsBinaryExpr* binaryExpr) {
    visitExpr(binaryExpr->left);
    visitExpr(binaryExpr->right);
    LgsType* type = nullptr;
    switch (binaryExpr->op) {
    case ADD:
    case SUB:
    case MUL:
    case DIV:
    case MOD:
    case BIT_AND:
    case BIT_OR:
    case BIT_XOR:
    case LSHIFT:
    case RSHIFT: {
        const auto lType = binaryExpr->left->type;
        const auto rType = binaryExpr->right->type;
        if (!lType || !rType) return;
        type = lType;
        break;
    }
    case AND:
    case OR:
    case NE:
    case EQ:
    case LT:
    case GT:
    case GE:
    case LE: {
        type = &LGS_BOOL;
        break;
    }
    case NOOP:
        break;
    }
    binaryExpr->setType(type);
}

void SemaAnalyser::visitArrayExpr(LgsArrayExpr* array) {
    for (const auto element : array->initialElements) {
        visitExpr(element);
    }
    if (array->type->asSArray()) {
        visitStaticArray(array);
    } else if (array->type->asDArray()) {
        visitDynamicArray(array);
    } else {
        assert(0);
    }
}

void inferBaseType(const LgsArrayExpr* array) {
    LgsType* baseType = nullptr;
    const auto first = array->initialElements.front();
    if (const auto innerArr = first->asArrayExpr()) {
        baseType = innerArr->type;
    } else {
        baseType = first->type;
    }
    array->type->asIterable()->baseType = baseType;
}

void SemaAnalyser::visitDynamicArray(LgsArrayExpr* array) {
    const auto dArr = array->type->asDArray();
    if (!dArr->sizeExpr) {
        dArr->sizeExpr = new LgsLongConst(array->initialElements.size());
    }
    if (array->initialElements.empty()) {
        if (!dArr->baseType) {
            errHandler.addError(E10049, &array->location);
        }
        return;
    }
    inferBaseType(array);
}

void SemaAnalyser::visitStaticArray(LgsArrayExpr* arrayExpr) {
    const auto& initialElements = arrayExpr->initialElements;
    const auto arr = arrayExpr->type->asSArray();
    if (initialElements.empty() && !arr->baseType) {
        return errHandler.addError(E10049, &arrayExpr->location);
    }
    for (const auto element : initialElements) {
        visitExpr(element);
    }
    if (!arr->baseType) {
        arr->baseType = initialElements.front()->type;
    }
}

void SemaAnalyser::visitHashMap(LgsHashMap* hashMap) {
    const auto typePair = hashMap->type->asMap()->typePair;
    if (typePair->key && typePair->value) return;
    if (hashMap->initialElements.empty()) {
        return errHandler.addError(E10049, &hashMap->location);
    }
    for (const auto element : hashMap->initialElements) {
        visitExpr(element->key);
        visitExpr(element->value);
    }
    const auto firstElement = hashMap->initialElements.front();
    typePair->key = firstElement->key->type;
    typePair->value = firstElement->value->type;
}

void SemaAnalyser::visitVariable(LgsVariable* variable) {
    const auto symbol = getSymbol(variable->name, &variable->location);
    if (!symbol) return;
    variable->ref.symbolType = symbol->symbolType;
    switch (symbol->symbolType) {
    case VAR_DEC:
        variable->ref.varDec = symbol->varDec;
        variable->isMutable = symbol->varDec->isMutable;
        variable->setType(symbol->varDec->type);
        break;
    case ENUM_FIELD:
        variable->ref.field = symbol->field;
        variable->isMutable = symbol->field->isMutable;
        variable->setType(symbol->field->type);
        break;
    case PARAM:
        variable->ref.param = symbol->param;
        variable->setType(symbol->param->type);
        if (variable->ref.param->isSelf) {
            stack.currentFunc()->funcType->isStatic = false;
        }
        break;
    case ENUM:
        variable->ref.lgsEnum = symbol->lgsEnum;
        variable->setType(symbol->lgsEnum);
        break;
    case FUNC:
        variable->ref.func = symbol->func;
        variable->setType(symbol->func->funcType);
        break;
    case OBJECT:
        variable->ref.object = symbol->object;
        variable->setType(symbol->object);
        break;
    default:
        assert(false);
    }
    assert(variable->ref.symbolType != UNKNOWN);
}

void SemaAnalyser::visitSelection(LgsSelection* selection) {
    const auto exprs = selection->exprs;
    const auto firstExpr = exprs.front();
    visitFirstSelection(firstExpr);
    if (!firstExpr->type || firstExpr->type->isUnknown) return;
    visitInnerSelections(selection);
    selection->setType(selection->lastExpr()->type);
    selection->isMutable = selection->lastExpr()->isMutable;
}

void SemaAnalyser::visitFirstSelection(LgsExpr* firstExpr) {
    if (const auto variable = firstExpr->asVariable()) {
        visitVariable(variable);
    } else if (const auto funcCall = firstExpr->asFuncCall()) {
        visitFuncCall(funcCall);
    } else if (const auto iterIndex = firstExpr->asIterIndex()) {
        visitIterIndex(iterIndex);
    }
}

void SemaAnalyser::visitInnerSelections(const LgsSelection* selection) {
    const auto exprs = selection->exprs;
    for (int i = 0; i < exprs.size() - 1; ++i) {
        const auto parentExpr = exprs[i];
        const auto childExpr = exprs[i + 1];
        if (const auto var = childExpr->asVariable()) {
            visitFieldSelection(var, parentExpr->type);
        } else if (const auto methodCall = childExpr->asFuncCall()) {
            visitMethodCall(methodCall, parentExpr->type);
        }
        if (!childExpr->type || childExpr->type->isUnknown) return;
    }
}

void SemaAnalyser::visitFieldSelection(LgsVariable* childField, LgsType* parentType) {
    if (!parentType) return;
    const auto field = parentType->getField(childField->name);
    if (!field) {
        return errHandler.addError(E10005, &childField->location, {childField->name, parentType->prettyName()});
    }
    childField->setType(field->type);
    childField->isMutable = field->isMutable;
    childField->ref = LgsSymbol(field);
    validateFieldVisibility(field, parentType->asObject());
}

void SemaAnalyser::visitMethodCall(LgsFuncCall* methodCall, LgsType* parentType) {
    for (int i = 1; i < methodCall->args.size(); ++i) {
        const auto arg = methodCall->args[i];
        visitExpr(arg);
    }
    if (!resolveMethodCall(methodCall, parentType)) return;
    if (!validateMethodVisibility(methodCall, parentType->asObject())) return;
    if (methodCall->isSpread) {
        const auto lastArg = methodCall->args[methodCall->args.size() - 1];
        if (!lastArg->type->asIterable()) {
            return errHandler.addError(E10052, &methodCall->location, {lastArg->prettyName(), lastArg->type->prettyName()});
        }
    }
}

void SemaAnalyser::visitFuncCall(LgsFuncCall* funcCall) {
    for (const auto arg : funcCall->args) {
        visitExpr(arg);
    }
    resolveFuncCall(funcCall);
}

void SemaAnalyser::visitInstance(LgsInstance* instance) {
    const auto objName = instance->name;
    const auto symbol = getSymbol(objName, &instance->location);
    if (!symbol) return;
    if (symbol->symbolType != OBJECT && symbol->symbolType != INTERFACE) {
        return errHandler.addError(E10022, &instance->location, {objName});
    }

    if (symbol->symbolType == INTERFACE) {
        return visitInterfaceInstance(instance, symbol->interface);
    }

    const auto obj = symbol->object;
    if (obj->singleton) {
        return errHandler.addError(E10032, &instance->location, {objName});
    }

    instance->setObject(obj->clone());
    // Args
    for (const auto& [_, arg] : instance->args) {
        const auto field = instance->obj->getField(arg->name);
        if (!field) {
            errHandler.addError(E10005, &arg->location, {arg->name, objName});
            continue;
        }
        if (!validateFieldVisibility(field, instance->obj)) continue;
        visitExpr(arg->expr);
        validateExprType(arg->expr, field->type);
        field->expr = arg->expr;
    }

    // Missing required fields
    for (const auto& [name, field] : instance->obj->fields) {
        if (!field->isMutable && instance->args.find(name) == instance->args.end()) {
            errHandler.addError(E10029, &field->location, {field->name});
        }
    }
}

void SemaAnalyser::visitInterfaceInstance(LgsInstance* instance, LgsInterface* interface) {
    instance->setObject(new LgsObject(interface->name));
    instance->obj->location = instance->location;
    instance->obj->interfaces.push_back(interface);
    auto isValid = true;
    for (const auto& [name, arg] : instance->args) {
        visitExpr(arg->expr);
        const auto field = interface->getField(name);
        if (field) {
            const auto newField = new LgsField(*field);
            newField->expr = arg->expr;
            instance->obj->addField(newField);
            continue;
        }
        const auto method = interface->getMethod(name);
        if (method) {
            const auto newMethod = arg->expr->asFunc();
            newMethod->funcType->name = method->funcType->name;
            newMethod->funcType->params.insert(newMethod->funcType->params.begin(), LgsParam(interface, LGS_SELF));
            instance->obj->addMethod(newMethod);
            continue;
        }
        errHandler.addError(E10005, &arg->location, {arg->name, interface->name});
        isValid = false;
    }
    if (isValid) {
        visitObject(instance->obj);
    }
}

void SemaAnalyser::visitPostfixExpr(LgsPostfixExpr* postfixExpr) {
    const auto baseExpr = postfixExpr->expr;
    visitUnaryExpr(baseExpr);
    const auto type = baseExpr->type;
    if (!type->asInt()) {
        return errHandler.addError(E10050, &postfixExpr->location, {type->prettyName()});
    }
    postfixExpr->setType(type);
}

void SemaAnalyser::visitStrConst(const LgsStrConst* strConst) {
    if (strConst->templateParts.empty()) return;
    for (const auto templatePart : strConst->templateParts) {
        visitExpr(templatePart);
    }
}

void SemaAnalyser::visitPrefixExpr(LgsPrefixExpr* prefixExpr) {
    const auto baseExpr = prefixExpr->expr;
    visitExpr(baseExpr);
    const auto type = baseExpr->type;
    prefixExpr->setType(type);
}

void SemaAnalyser::visitIterIndex(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto exprFrom = iterIndex->index->from;
    const auto exprTo = iterIndex->index->to;
    visitUnaryExpr(baseExpr);
    iterIndex->isMutable = baseExpr->isMutable;
    visitExpr(exprFrom);
    visitExpr(exprTo);
    if (baseExpr->type->isUnknown) return;
    const auto iterable = baseExpr->type->asIterable();
    if (!iterable) {
        return errHandler.addError(E10002, &iterIndex->location, {baseExpr->prettyName(), baseExpr->type->prettyName()});
    }
    if (exprTo) {
        visitSlice(iterIndex);
        iterIndex->setType(iterable);
    } else {
        validateIndex(iterIndex);
        if (const auto map = iterable->asMap()) {
            iterIndex->setType(map->typePair->value);
        } else {
            iterIndex->setType(iterable->baseType);
        }
    }
}

void SemaAnalyser::visitSlice(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto exprFrom = iterIndex->index->from;
    const auto exprTo = iterIndex->index->to;
    const auto iterable = baseExpr->type->asIterable();
    if (!baseExpr->type->canSlice) {
        return errHandler.addError(E10042, &iterIndex->location, {iterIndex->prettyName(), baseExpr->type->prettyName()});
    }
    if (!iterable->getIndexType()->equals(exprFrom->type)) {
        return errHandler.addError(E10036, &iterIndex->location, {iterIndex->prettyName(), exprFrom->type->prettyName()});
    }
    if (!iterable->getIndexType()->equals(exprTo->type)) {
        return errHandler.addError(E10036, &iterIndex->location, {iterIndex->prettyName(), exprFrom->type->prettyName()});
    }
    validateSliceBounds(iterIndex);
}

void SemaAnalyser::visitGroup(LgsGroup* group) {
    for (const auto targetSymbol : group->targetSymbols) {
        for (const auto type : group->types) {
            const auto method = type->getMethod(targetSymbol->name);
            if (!method) continue;
            method->funcType->isVirtual = true;
            group->addMethod(method);
        }
    }
}

bool SemaAnalyser::setSelectionFieldType(const LgsUnaryExpr* parent, LgsVariable* fieldVariable) {
    const auto type = parent->type;
    if (!type) {
        errHandler.addError(E10005, &fieldVariable->location, {fieldVariable->prettyName(), LgsUnknownType::genricName});
        return false;
    }
    const auto field = type->getField(fieldVariable->name);
    if (!field) {
        errHandler.addError(E10005, &fieldVariable->location, {fieldVariable->prettyName(), type->prettyName()});
        return false;
    }
    fieldVariable->setType(field->type);
    return true;
}

bool SemaAnalyser::setLoopVars(LgsForeachLoop* foreachLoop, LgsUnaryExpr* iterExpr, const LgsIterable* iterable) {
    const auto varDecSize = foreachLoop->loopVars.size();
    foreachLoop->withIndex = iterable->unpackLength + 1 == varDecSize;
    const bool withIndex = foreachLoop->withIndex;
    if (withIndex) {
        foreachLoop->loopVars[0]->type = &LGS_INT;
        foreachLoop->loopVars[0]->expr = LGS_INT.getZeroValue();
    } else if (iterable->unpackLength != varDecSize) {
        errHandler.addError(E10041, &iterExpr->location, {iterExpr->prettyName(), std::to_string(iterable->unpackLength), std::to_string(iterable->unpackLength + 1), std::to_string(varDecSize)});
        return true;
    }

    if (const auto pair = iterable->baseType->asPair()) {
        foreachLoop->loopVars[0 + withIndex]->type = pair->key;
        foreachLoop->loopVars[1 + withIndex]->type = pair->value;
    } else {
        foreachLoop->loopVars[0 + withIndex]->type = iterable->baseType;
    }
    return false;
}

void SemaAnalyser::validateObjImplements(LgsObject* obj, const std::vector<LgsType*>& interfaces) {
    std::unordered_set<std::string> interfacesNames;
    for (const auto implementsInterface : interfaces) {
        const auto interface = implementsInterface->asInterface();
        if (!interface) {
            errHandler.addError(E10025, &implementsInterface->location, {implementsInterface->prettyName()});
            continue;
        }
        validateObjInterface(obj, interface);
        for (const auto parentInterface: interface->interfaces) {
            validateObjInterface(obj, parentInterface->asInterface());
        }
    }
}

std::string getMissingImplementsStr(const std::vector<LgsField*>& fields, const std::vector<LgsFunc*>& methods) {
    std::stringstream str;
    str << "Missing fields/methods:";
    if (!fields.empty()) {
        str << LGS_ERROR_PADDING << "Fields:";
        for (const auto& field : fields) {
            str << LGS_ERROR_PADDING << "\t- " << field->name << ": " <<  field->type->prettyName();
        }
    }
    if (!methods.empty()) {
        str << LGS_ERROR_PADDING << "Methods:";
        for (const auto& method : methods) {
            str << LGS_ERROR_PADDING << "\t- " << method->funcType->prettyName();
        }
    }
    return str.str();
}

void SemaAnalyser::validateObjInterface(LgsObject* obj, LgsInterface* interface) {
    // Fields
    std::vector<LgsField*> missingFields;
    for (const auto& [name, interfaceField] : interface->fields) {
        const auto objField = obj->fields.find(name);
        if (objField != obj->fields.end() && objField->second->type->equals(interfaceField->type)) {
            objField->second->isVirtual = true;
            continue;
        }
        if (!interfaceField->isOptional) {
            missingFields.emplace_back(interfaceField);
        }
    }

    // Methods
    std::vector<LgsFunc*> missingMethods;
    for (const auto& [name, interfaceMethod] : interface->methods) {
        const auto method = obj->methods.find(name);
        if (method != obj->methods.end()) {
            const auto objMethod = obj->methods.find(name);
            if (objMethod != obj->methods.end() && objMethod->second->funcType->equals(interfaceMethod->funcType)) {
                objMethod->second->funcType->isVirtual = true;
                continue;
            }
        }

        if (!interfaceMethod->stmtsBlock && !interfaceMethod->funcType->isOptional) {
            missingMethods.emplace_back(interfaceMethod);
        }
    }

    if (!missingMethods.empty() || !missingFields.empty()) {
        errHandler.addError(E10016, &obj->location, {obj->prettyName(), interface->name, getMissingImplementsStr(missingFields, missingMethods)});
    }
}

void SemaAnalyser::validateIndex(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto exprFrom = iterIndex->index->from;
    const auto iterable = baseExpr->type->asIterable();
    if (!iterable->getIndexType()->equals(exprFrom->type)) {
        return errHandler.addError(E10036, &iterIndex->location, {iterIndex->prettyName(), exprFrom->type->prettyName()});
    }
    if (const auto sArr = iterable->asSArray()) {
        const auto i = exprFrom->getConstInt();
        const auto bound = sArr->initialLength;
        if (i >= bound) {
            return errHandler.addError(E10003, &iterIndex->location, {iterIndex->prettyName(), std::to_string(bound)});
        }
    }
}

void SemaAnalyser::validateSliceBounds(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto exprFrom = iterIndex->index->from;
    const auto exprTo = iterIndex->index->to;
    const auto iterable = baseExpr->type->asIterable();
    if (const auto sArr = iterable->asSArray()) {
        if (exprFrom->getConstInt() > exprTo->getConstInt()) {
            return errHandler.addError(E10037, &iterIndex->location, {iterIndex->prettyName()});
        }
        const auto i = exprFrom->getConstInt();
        const auto j = exprTo->getConstInt();
        const auto bound = sArr->initialLength;
        if (i >= bound || j >= bound) {
            return errHandler.addError(E10003, &iterIndex->location, {iterIndex->prettyName(), std::to_string(bound)});
        }
    }
}

bool SemaAnalyser::validateFieldVisibility(LgsField* field, const LgsObject* parent) {
    if (parent && parent->singleton) return true;
    if (!field || field->isVirtual) return false;
    if (!field->isPublic && file->absPath != field->location.filePath) {
        errHandler.addError(E10030, &field->location, {field->name, *field->parentName});
        return false;
    }
    return true;
}

bool SemaAnalyser::validateMethodVisibility(LgsFuncCall* methodCall, const LgsObject* parent) {
    if (parent && parent->singleton) return true;
    const auto method = methodCall->func;
    if (!method || method->funcType->isVirtual) return false;
    if (!method->funcType->isPublic) {
        assert(method->location.filePath);
        if (file->absPath != method->location.filePath) {
            errHandler.addError(E10031, &methodCall->location, {method->funcType->name, method->funcType->parentName});
            return false;
        }
    }
    return true;
}

bool SemaAnalyser::validateExprType(LgsExpr* expr, LgsType* type) {
    assert(expr);
    if (expr->isNull) {
        // null must have a type
        if (type->isUnknown) {
            errHandler.addError(E10024, &expr->location);
            return false;
        }
        // type must be nullable
        if (!type->asNullable()) {
            errHandler.addError(E10023, &type->location, {type->prettyName(), type->prettyName()});
            return false;
        }
    }
    if (type->isUnknown || expr->type->isUnknown) return false;
    if (!expr->type->equals(type)) {
        errHandler.addError(E10001, &expr->location, {type->prettyName(), expr->type->prettyName()});
        return false;
    }
    return true;
}

void SemaAnalyser::validateFuncControlFlow(LgsFunc* func) {
    if (func->funcType->rt->isVoid) return;
    if (!validateBlockControlFlow(func->stmtsBlock, func)) {
        errHandler.addError(E10055, &func->location, {func->funcType->name});
    }
}

bool SemaAnalyser::validateBlockControlFlow(const LgsStmtsBlock* stmtBlock, const LgsFunc* func) {
    if (!stmtBlock) return true;
    if (stmtBlock->returnExpr) return true;
    auto isValid = false;
    for (const auto stmt : stmtBlock->stmts) {
        if (const auto ifStmt = stmt->asIfStmt()) {
            isValid = validateBlockControlFlow(ifStmt->ifBlock, func);
            for (const auto [_, elseIfStmt] : ifStmt->elseIfs) {
                isValid = isValid && validateBlockControlFlow(elseIfStmt, func);
            }
            isValid = isValid && validateBlockControlFlow(ifStmt->elseBlock, func);
        } else if (const auto loop = stmt->asLoop()) {
            isValid = isValid && validateBlockControlFlow(loop->stmtsBlock, func);
        } else if (const auto patternMatch = stmt->asIfStmt()) {
            for (const auto [_, patternsStmtBlock] : patternMatch->elseIfs) {
                isValid = isValid && validateBlockControlFlow(patternsStmtBlock, func);
            }
            isValid = isValid && validateBlockControlFlow(patternMatch->elseBlock, func);
        }
    }
    return isValid;
}

LgsSymbol* SemaAnalyser::getSymbol(const std::string& name, LgsLocation* location) {
    if (const auto globalSymbol = globals.getSymbol(name)) {
        return globalSymbol;
    }
    if (const auto fileSymbol = file->symbolTable.getSymbol(name)) {
        return fileSymbol;
    }
    if (const auto symbol = stack.getSymbolTable().getSymbol(name)) {
        return symbol;
    }
    errHandler.addError(E10006, location, {name});
    return nullptr;
}

void SemaAnalyser::addLocalSymbol(const LgsSymbol& newSymbol) {
    auto symbolName = *newSymbol.name;
    auto symbol = globals.getSymbol(symbolName);
    if (symbol && symbol->isBuiltin) {
        return errHandler.addError(E10053, newSymbol.location, {symbolName});
    }
    if ((symbol = file->symbolTable.getSymbol(symbolName))) {
        return errHandler.addError(E10011, newSymbol.location, {symbolName, getFullPath(*symbol->location)});
    }
    stack.getSymbolTable().addSymbol(newSymbol, &errHandler);
}

void SemaAnalyser::resolveFuncCall(LgsFuncCall* funcCall) {
    const auto symbol = getSymbol(funcCall->name, &funcCall->location);
    if (!symbol) return;
    if (symbol->symbolType == FUNC) {
        const auto func = symbol->func;
        if (funcCall->equals(func->funcType)) {
            funcCall->func = func;
            funcCall->setType(func->funcType->rt);
        } else {
            errHandler.addError(E10015, &funcCall->location, {funcCall->name, funcCall->prettyName(), func->prettyName()});
        }
    } else {
        LgsType* symbolType = nullptr;
        if (symbol->symbolType == VAR_DEC) {
            funcCall->callback = new LgsSymbol(symbol->varDec);
            symbolType = symbol->varDec->type;
        } else if (symbol->symbolType == PARAM) {
            funcCall->callback = new LgsSymbol(symbol->param);
            symbolType = symbol->param->type;
        } else {
            assert(0);
        }

        if (!symbolType->asFuncType()) {
            errHandler.addError(E10046, &funcCall->location, {funcCall->name});
        }
    }
}

bool SemaAnalyser::resolveMethodCall(LgsFuncCall* methodCall, LgsType* parentType) {
    auto name = methodCall->name;
    const auto method = parentType->getMethod(name);
    if (!method) {
        errHandler.addError(E10005, &methodCall->location, {name, parentType->prettyName()});
        return false;
    }
    if (methodCall->equals(method->funcType)) {
        methodCall->func = method;
        methodCall->setType(method->funcType->rt);
    } else {
        errHandler.addError(E10034, &methodCall->location, {parentType->prettyName(), name, methodCall->prettyName(), method->prettyName()});
        return false;
    }
    return true;
}

LgsType* SemaAnalyser::resolveType(LgsType* type) {
    if (const auto nullable = type->asNullable()) {
        nullable->baseType = resolveType(nullable->baseType);
    }
    if (const auto iter = type->asIterable()) {
        resolveIterable(iter);
    }
    if (const auto pair = type->asPair()) {
        pair->key = resolveType(pair->key);
        pair->value = resolveType(pair->value);
    }
    if (const auto funcType = type->asFuncType()) {
        resolveFuncTypes(funcType);
    }

    if (type->isUnknown) {
        auto typeName = type->getName();
        auto symbol = globals.getSymbol(typeName);
        if (!symbol) {
            symbol = file->symbolTable.getSymbol(typeName);
        }
        if (!symbol) {
            errHandler.addError(E10006, &type->location, {typeName});
            return nullptr;
        }
        LgsType* newType = nullptr;
        switch (symbol->symbolType) {
        case FUNC:
            newType = symbol->func->funcType;
            break;
        case OBJECT:
            newType = symbol->object;
            break;
        case INTERFACE:
            newType = symbol->interface;
            break;
        case GROUP:
            newType = symbol->group;
            break;
        case ENUM:
            newType = symbol->lgsEnum;
            break;
        default:
            break;
        }
        assert(newType);
        freeType(type);
        type = newType;
    }
    return type;
}

void SemaAnalyser::resolveIterable(LgsIterable* iterable) {
    iterable->baseType = resolveType(iterable->baseType);
    visitExpr(iterable->sizeExpr);
    if (const auto staticArr = iterable->asSArray()) {
        const auto exprConstNumber = iterable->sizeExpr->getConstInt();
        if (exprConstNumber <= 0) {
            return errHandler.addError(E10048, &iterable->location, {iterable->prettyName()});
        }
        staticArr->initialLength = exprConstNumber;
    }
}

void SemaAnalyser::resolveObjTypes(LgsObject* obj) {
    for (const auto& [_, field] : obj->fields) {
        if (obj->name == field->type->getName()) {
            field->type = obj;
        } else {
            field->type = resolveType(field->type);
        }
        field->parentName = &obj->name;
    }
    for (const auto& [_, method] : obj->methods) {
        resolveFuncTypes(method->funcType);
    }
    for (auto& interface : obj->interfaces) {
        interface = resolveType(interface);
    }
}

void SemaAnalyser::resolveInterfaceTypes(LgsInterface* interface) {
    for (const auto& [_, field] : interface->fields) {
        field->type = resolveType(field->type);
        field->parentName = &interface->name;
    }
    for (const auto& [_, method] : interface->methods) {
        resolveFuncTypes(method->funcType);
    }
    for (auto& i : interface->interfaces) {
        i = resolveType(i);
    }
}

void SemaAnalyser::resolveFuncTypes(LgsFuncType* funcType) {
    for (auto & param : funcType->params) {
        param.type = resolveType(param.type);
    }
    funcType->rt = resolveType(funcType->rt);
}

void SemaAnalyser::resolveGroupTypes(LgsGroup* group) {
    for (auto & type : group->types) {
        type = resolveType(type);
    }
}
