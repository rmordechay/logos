#include "analysis/LgsSema.h"
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
#include "funcs/LgsMainFunc.h"
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
#include "loops/LgsForeachLoop.h"
#include "loops/LgsForLoop.h"
#include "loops/LgsRangeLoop.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsIfStmt.h"
#include "types/primitives/LgsDouble.h"

void LgsSema::analyse() {
    if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
        visitMainFile(mainFile);
    } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
        visitObject(objFile->obj);
    } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
        visitInterface(interfaceFile->interface);
    }
}

void LgsSema::visitMainFile(LgsMainFile* mainFile) {
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

void LgsSema::visitObject(LgsObject* obj) {
    for (const auto& [_, field] : obj->fields) {
        visitField(field);
    }
    for (const auto& [_, method] : obj->methods) {
        visitFunc(method);
    }
    validateObjImplements(obj, obj->interfaces);
}

void LgsSema::visitInterface(LgsInterface* interface) {
    for (const auto& [_, field] : interface->fields) {
        visitField(field);
    }
    auto allMethodsImplemented = true;
    for (const auto& [_, method] : interface->methods) {
        visitFunc(method);
        allMethodsImplemented = allMethodsImplemented && method->stmtsBlock;
    }
    if (allMethodsImplemented) {
        errHandler.addError(E10062, &interface->location, {interface->name});
    }
}

void LgsSema::visitField(LgsField* field) {
    if (field->expr) {
        visitExpr(field->expr);
        matchExprToType(field->expr, field->type);
    }
    if (field->type && field->type->asFuncType()) {
        errHandler.addError(E10013, &field->location, {field->name});
    }
}

void LgsSema::visitFunc(LgsFunc* func) {
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
    if (!validateBlockControlFlow(func->stmtsBlock, func)) {
        errHandler.addError(E10055, &func->location, {func->pname()});
    }
    stack.exitScope();
}

void LgsSema::visitParam(LgsParam* param) {
    if (param->expr) {
        visitExpr(param->expr);
        matchExprToType(param->expr, param->type);
    } else if (param->isVariadic) {
        if (param->expr) {
            errHandler.addError(E10045, &param->location);
        }
        assert(0);
    }
    addLocalSymbol(LgsSymbol(param));
}

void LgsSema::visitStmt(LgsStmt* stmt) {
    if (const auto ifStmt = stmt->asIfStmt()) {
        ifStmt->isPatternMatching ? visitPatternMatching(ifStmt) : visitIfStmt(ifStmt);
    }
    else if (const auto varDec = stmt->asVarDec()) visitVarDec(varDec);
    else if (const auto loopStmt = stmt->asLoop()) visitLoopStmt(loopStmt);
    else if (const auto coroutine = stmt->asCoroutine()) visitCoroutine(coroutine);
    else if (const auto deferStmt = stmt->asDefer()) visitDeferStmt(deferStmt);
    else if (const auto assignment = stmt->asAssignment()) visitAssignment(assignment);
    else if (const auto funcCall = stmt->asFuncCall()) visitFuncCall(funcCall);
    else if (const auto postfixExpr = stmt->asPostfixExpr()) visitPostfixExpr(postfixExpr);
    else if (const auto selection = stmt->asSelection()) visitSelection(selection);
    else if (const auto returnStmt = stmt->asReturn()) visitReturnStmt(returnStmt);
    else if (const auto continueStmt = stmt->asContinue()) visitContinueStmt(continueStmt);
    else if (const auto breakStmt = stmt->asBreak()) visitBreakStmt(breakStmt);
}

void LgsSema::visitStmtsBlock(LgsStmtsBlock* stmtsBlock) {
    if (!stmtsBlock || stmtsBlock->stmts.empty()) return;
    for (const auto& stmt : stmtsBlock->stmts) {
        visitStmt(stmt);
    }
    const auto lastStmt = stmtsBlock->lastStmt();
    stmtsBlock->returnExpr = lastStmt->asReturn();
    for (int i = 0; i < stmtsBlock->stmts.size() - 1; ++i) {
        if (stmtsBlock->stmts[i]->isTerminator()) {
            return errHandler.addError(E10059, &lastStmt->location);
        }
    }
}

void LgsSema::visitVarDec(LgsVarDec* varDec) {
    if (varDec->expr && varDec->type) {
        varDec->type = typeResolver.resolveType(varDec->type, file);
        visitExpr(varDec->expr);
        matchExprToType(varDec->expr, varDec->type);
    } else if (varDec->expr) {
        visitExpr(varDec->expr);
        varDec->type = varDec->expr->type;
    } else {
        if (const auto iter = varDec->type->asIterable()) visitExpr(iter->sizeExpr);
        varDec->type = typeResolver.resolveType(varDec->type, file);
        varDec->expr = varDec->type->getZeroValue();
        varDec->expr->location = varDec->location;
    }
    addLocalSymbol(LgsSymbol(varDec));
}

void LgsSema::visitAssignment(LgsAssignment* assignment) {
    const auto lValue = assignment->lValue;
    const auto rValue = assignment->rValue;
    visitExpr(lValue);
    if (lValue->isAssignable) {
        errHandler.addError(E10012, &lValue->location);
    }
    visitExpr(rValue);
    if (!lValue->isMutable) {
        return errHandler.addError(E10051, &lValue->location, {lValue->pname()});
    }
    const auto lType = lValue->type;
    const auto rType = rValue->type;
    if (!lType || !rType) return;
    if (!lType->equals(rType)) {
        errHandler.addError(E10001, &assignment->location, {lType->pname(), rType->pname()});
    }
}

void LgsSema::visitIfStmt(LgsIfStmt* ifStmt) {
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

void LgsSema::visitPatternMatching(LgsIfStmt* pm) {
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
        if (expr->type->isUnknown()) continue;
        if (!baseExprType->equals(expr->type)) {
            return errHandler.addError(E10014, &expr->location, {expr->type->pname(), baseExprType->pname()});
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

void LgsSema::visitBoolPatternMatching(LgsIfStmt* pm) {
    for (const auto [expr, block] : pm->elseIfs) {
        stack.enterScope(pm, block);
        visitExpr(expr);
        if (!expr->type->asBool()) {
            return errHandler.addError(E10057, &expr->location, {expr->pname()});
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

void LgsSema::visitWhileLoop(LgsWhileLoop* whileLoop) {
    visitExpr(whileLoop->condExpr);
    const auto condType = whileLoop->condExpr->type;
    if (!condType->asBool()) {
        return errHandler.addError(E10066, &whileLoop->location, {whileLoop->condExpr->pname(), condType->pname()});
    }
    visitStmtsBlock(whileLoop->stmtsBlock);
}

void LgsSema::visitLoopStmt(LgsForLoop* loopStmt) {
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

void LgsSema::visitRangeLoop(const LgsRangeLoop* rangeLoop) {
    const auto startRange = rangeLoop->startRange;
    const auto endRange = rangeLoop->endRange;
    visitExpr(startRange);
    visitExpr(endRange);
    if (startRange && startRange->type && !startRange->type->isNumber) {
        errHandler.addError(E10002, &startRange->location, {startRange->pname(), startRange->type->pname()});
    }
    if (endRange && endRange->type && !endRange->type->isNumber) {
        errHandler.addError(E10002, &endRange->location, {endRange->pname(), endRange->type->pname()});
    }
    addLocalSymbol(LgsSymbol(rangeLoop->loopVars.front()));
    visitStmtsBlock(rangeLoop->stmtsBlock);
}

void LgsSema::visitForeachLoop(LgsForeachLoop* foreachLoop) {
    const auto iterExpr = foreachLoop->iterExpr;
    visitUnaryExpr(iterExpr);
    const auto iterable = iterExpr->type->asIterable();
    if (!iterable) {
        if (iterExpr->type)
            errHandler.addError(E10002, &iterExpr->location,
                                {iterExpr->pname(), iterExpr->type->pname()});
        return;
    }
    if (resolveLoopVars(foreachLoop, iterExpr, iterable)) return;
    for (const auto varDec : foreachLoop->loopVars) {
        addLocalSymbol(LgsSymbol(varDec));
    }
    visitStmtsBlock(foreachLoop->stmtsBlock);
}

void LgsSema::visitInfiniteLoop(const LgsInfiniteLoop* infiniteLoop) {
    if (!infiniteLoop->loopVars.empty()) {
        addLocalSymbol(LgsSymbol(infiniteLoop->loopVars.front()));
    }
    visitStmtsBlock(infiniteLoop->stmtsBlock);
}

void LgsSema::visitCoroutine(const LgsCoroutine* coroutine) {
    if (coroutine->funcCall) {
        visitFuncCall(coroutine->funcCall);
    } else if (coroutine->selection) {
        visitSelection(coroutine->selection);
    } else {
        assert(0);
    }
}

void LgsSema::visitReturnStmt(LgsReturn* returnStmt) {
    const auto funcType = stack.currentFunc()->funcType;
    const auto retExpr = returnStmt->expr;
    if (retExpr) {
        stack.currentFunc()->returnStmts.push_back(returnStmt);
        visitExpr(retExpr);
    }
    const auto rt = funcType->rt;
    if (rt->isVoid() && retExpr && retExpr->type && !retExpr->type->isVoid()) {
        errHandler.addError(E10027, &returnStmt->location, {retExpr->type->pname()});
    } else if (!rt->isVoid() && !retExpr) {
        errHandler.addError(E10026, &returnStmt->location, {funcType->name, rt->pname()});
    } else if (retExpr && retExpr->type && !rt->equals(retExpr->type)) {
        errHandler.addError(E10004, &returnStmt->location, {funcType->name, rt->pname(), retExpr->type->pname()});
    }
}

void LgsSema::visitContinueStmt(LgsContinue* continueStmt) {
    if (!stack.currentLoop()) {
        errHandler.addError(E10038, &continueStmt->location);
    }
}

void LgsSema::visitBreakStmt(LgsBreak* breakStmt) {
    if (breakStmt->isBreakIf) {
        if (!stack.currentIfStmt()) errHandler.addError(E10071, &breakStmt->location);
    } else if (!stack.currentLoop()) {
        errHandler.addError(E10017, &breakStmt->location);
    }
}

void LgsSema::visitDeferStmt(const LgsDeferStmt* deferStmt) {
    if (deferStmt->funcCall) visitFuncCall(deferStmt->funcCall);
    else visitSelection(deferStmt->selection);
    stack.currentFunc()->hasDefers = true;
}

void LgsSema::visitExpr(LgsExpr* expr) {
    if (!expr) return;
    if (const auto iter = expr->type->asIterable()) {
        visitExpr(iter->sizeExpr);
    }
    if (const auto castExpr = dynamic_cast<LgsCast*>(expr)) {
        visitCast(castExpr);
    } else if (const auto unaryExpr = dynamic_cast<LgsUnaryExpr*>(expr)) {
        visitUnaryExpr(unaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
    }
    if (expr->type && expr->type->isHeapAlloc) {
        stack.addHeapAllocExpr(expr);
    }
}

void LgsSema::visitCast(LgsCast* castExpr) {
    const auto fromValue = castExpr->fromValue;
    if (const auto unaryExpr = dynamic_cast<LgsUnaryExpr*>(fromValue)) {
        visitUnaryExpr(unaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(fromValue)) {
        visitBinaryExpr(binaryExpr);
    }
    castExpr->toType = typeResolver.resolveType(castExpr->toType, file);
    castExprToType(fromValue, castExpr->toType);
}

void LgsSema::visitArrayExpr(LgsArrayExpr* array) {
    for (const auto element : array->initialElements) {
        visitExpr(element);
    }
    if (array->type->isHeapAlloc) {
        visitDynamicArray(array);
    } else {
        visitStaticArray(array);
    }
}

void LgsSema::visitUnaryExpr(LgsUnaryExpr* unaryExpr) {
    if (const auto func = unaryExpr->asFunc()) visitFunc(func);
    else if (const auto instance = unaryExpr->asInstance()) visitInstance(instance);
    else if (const auto funcCall = unaryExpr->asFuncCall()) visitFuncCall(funcCall);
    else if (const auto strConst = unaryExpr->asStrConst()) visitStrConst(strConst);
    else if (const auto selection = unaryExpr->asSelection()) visitSelection(selection);
    else if (const auto arrayExpr = unaryExpr->asArrayExpr()) visitArrayExpr(arrayExpr);
    else if (const auto hashMap = unaryExpr->asHashMap()) visitHashMap(hashMap);
    else if (const auto iterIndex = unaryExpr->asIterIndex()) visitIterIndex(iterIndex);
    else if (const auto variable = unaryExpr->asVariable()) visitVariable(variable);
    else if (const auto postfixExpr = unaryExpr->asPostfixExpr()) visitPostfixExpr(postfixExpr);
    else if (const auto prefixExpr = unaryExpr->asPrefixExpr()) visitPrefixExpr(prefixExpr);
    else if (const auto vecExpr = unaryExpr->asVectorExpr()) visitVector(vecExpr);
}

void LgsSema::visitBinaryExpr(LgsBinaryExpr* binaryExpr) {
    visitExpr(binaryExpr->left);
    visitExpr(binaryExpr->right);
    LgsType* type = nullptr;
    switch (binaryExpr->op) {
    case ADD: case SUB: case MUL: case DIV:
    case MOD: case BIT_AND: case BIT_OR: case BIT_XOR:
    case LSHIFT: case RSHIFT: {
        const auto lType = binaryExpr->left->type;
        const auto rType = binaryExpr->right->type;
        if (!lType || !rType) return;
        type = lType;
        break;
    }
    case AND: case OR: case NE: case EQ:
    case LT: case GT: case GE:case LE: {
        type = &LGS_BOOL;
        break;
    }
    case NOOP: break;
    }
    binaryExpr->setType(type);
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

void LgsSema::visitInterfaceInstance(LgsInstance* instance, LgsInterface* interface) {
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

void LgsSema::visitStaticArray(LgsArrayExpr* arrayExpr) {
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

void LgsSema::visitDynamicArray(LgsArrayExpr* array) {
    const auto dArr = array->type->asIterable();
    if (!dArr->sizeExpr) {
        dArr->sizeExpr = new LgsIntConst(&LGS_LONG, array->initialElements.size());
    }
    if (!dArr->baseType && array->initialElements.empty()) {
        errHandler.addError(E10049, &array->location);
    } else {
        inferBaseType(array);
    }
}

void LgsSema::visitHashMap(LgsHashMap* hashMap) {
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

void LgsSema::visitVector(const LgsVectorExpr* vec) {
    for (const auto arg : vec->args) {
        visitExpr(arg);
    }
}

void LgsSema::visitVariable(LgsVariable* variable) {
    if (variable->name == "for.isFirst") return visitForIsFirst(variable);
    if (variable->name == "for.isLast") return visitForIsLast(variable);
    const auto symbol = getSymbol(variable->name, &variable->location);
    if (!symbol) return;
    variable->ref.symbolType = symbol->symbolType;
    switch (symbol->symbolType) {
    case VAR_DEC: variable->ref.varDec = symbol->varDec;
        variable->isMutable = symbol->varDec->isMutable;
        variable->setType(symbol->varDec->type);
        break;
    case ENUM_FIELD: variable->ref.field = symbol->field;
        variable->isMutable = symbol->field->isMutable;
        variable->setType(symbol->field->type);
        break;
    case PARAM: variable->ref.param = symbol->param;
        variable->setType(symbol->param->type);
        if (variable->ref.param->isSelf) {
            stack.currentFunc()->funcType->isStatic = false;
        }
        break;
    case ENUM: variable->ref.lgsEnum = symbol->lgsEnum;
        variable->setType(symbol->lgsEnum);
        break;
    case FUNC: variable->ref.func = symbol->func;
        variable->setType(symbol->func->funcType);
        break;
    case OBJECT: variable->ref.object = symbol->object;
        variable->setType(symbol->object);
        break;
    default:
        assert(false);
    }
    assert(variable->ref.symbolType != UNKNOWN);
}

void LgsSema::visitSelection(LgsSelection* selection) {
    const auto exprs = selection->exprs;
    const auto firstExpr = exprs.front();
    visitFirstSelection(firstExpr);
    if (!firstExpr->type || firstExpr->type->isUnknown()) return;
    visitInnerSelections(selection);
    selection->setType(selection->lastExpr()->type);
    selection->isMutable = selection->lastExpr()->isMutable;
}

void LgsSema::visitFirstSelection(LgsExpr* firstExpr) {
    if (const auto variable = firstExpr->asVariable()) {
        visitVariable(variable);
    } else if (const auto funcCall = firstExpr->asFuncCall()) {
        visitFuncCall(funcCall);
    } else if (const auto iterIndex = firstExpr->asIterIndex()) {
        visitIterIndex(iterIndex);
    }
}

void LgsSema::visitInnerSelections(LgsSelection* selection) {
    const auto exprs = selection->exprs;
    for (int i = 0; i < exprs.size() - 1; ++i) {
        const auto parentExpr = exprs[i];
        const auto childExpr = exprs[i + 1];
        if (const auto var = childExpr->asVariable()) {
            visitFieldSelection(var, parentExpr->type);
        } else if (const auto methodCall = childExpr->asFuncCall()) {
            visitMethodCall(methodCall, parentExpr->type);
        }
        if (!childExpr->type || childExpr->type->isUnknown()) return;
    }
    selection->isMutable = selection->lastExpr()->isMutable;
}

void LgsSema::visitFieldSelection(LgsVariable* child, LgsType* parentType) {
    if (!parentType) return;
    auto childName = child->name;
    LgsField* field = nullptr;
    if (parentType->isVector()) {
        field = resolveVectorField(child, parentType->asVec());
        if (!field) return;
    } else {
        field = parentType->getField(childName);
    }
    if (!field) {
        errHandler.addError(E10005, &child->location, {childName, parentType->pname()});
        return;
    }
    child->setType(field->type);
    child->isMutable = !field->isConst;
    child->ref = LgsSymbol(field);
    if (const auto parentAsObj = parentType->asObject()) {
        validateFieldVisibility(field, parentAsObj);
    }
}

void LgsSema::visitMethodCall(LgsFuncCall* methodCall, LgsType* parentType) {
    for (int i = 1; i < methodCall->args.size(); ++i) {
        const auto arg = methodCall->args[i];
        visitExpr(arg);
    }
    if (!resolveMethodCall(methodCall, parentType)) return;
    validateMethodVisibility(methodCall, parentType->asObject());
    validateArgs(methodCall);
}

void LgsSema::visitFuncCall(LgsFuncCall* funcCall) {
    for (const auto arg : funcCall->args) {
        visitExpr(arg);
    }
    resolveFuncCall(funcCall);
    if (!funcCall->func) return;
    validateArgs(funcCall);
}

void LgsSema::visitPrefixExpr(LgsPrefixExpr* prefixExpr) {
    const auto baseExpr = prefixExpr->expr;
    visitExpr(baseExpr);
    const auto type = baseExpr->type;
    switch (prefixExpr->op) {
    case NOT_PREFIX: prefixExpr->setType(type);
        break;
    case MINUS_PREFIX: prefixExpr->setType(type);
        break;
    case SQRT_PREFIX: prefixExpr->setType(&LGS_DOUBLE);
        break;
    }
}

void LgsSema::visitPostfixExpr(LgsPostfixExpr* postfixExpr) {
    const auto baseExpr = postfixExpr->expr;
    visitUnaryExpr(baseExpr);
    const auto type = baseExpr->type;
    if (!type->isNumber) {
        return errHandler.addError(E10050, &postfixExpr->location, {type->pname()});
    }
    postfixExpr->setType(type);
}

void LgsSema::visitStrConst(const LgsStrConst* strConst) {
    if (strConst->templateParts.empty()) return;
    for (const auto templatePart : strConst->templateParts) {
        visitExpr(templatePart);
    }
}

void LgsSema::visitInstance(LgsInstance* instance) {
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
        matchExprToType(arg->expr, field->type);
        field->expr = arg->expr;
    }

    // Missing required fields
    for (const auto& [name, field] : instance->obj->fields) {
        if (!field->isMutable && instance->args.find(name) == instance->args.end()) {
            errHandler.addError(E10029, &field->location, {field->name});
        }
    }
}

void LgsSema::visitIterIndex(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto exprFrom = iterIndex->index->from;
    const auto exprTo = iterIndex->index->to;
    visitUnaryExpr(baseExpr);
    iterIndex->isMutable = baseExpr->isMutable;
    visitExpr(exprFrom);
    visitExpr(exprTo);
    if (baseExpr->type->isUnknown()) return;
    const auto iterable = baseExpr->type->asIterable();
    if (!iterable) {
        if (baseExpr->type)
            errHandler.addError(E10002, &iterIndex->location,
                                {baseExpr->pname(), baseExpr->type->pname()});
        return;
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

void LgsSema::visitSlice(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto exprFrom = iterIndex->index->from;
    const auto exprTo = iterIndex->index->to;
    const auto iterable = baseExpr->type->asIterable();
    if (!baseExpr->type->isSliceable) {
        return errHandler.addError(E10042, &iterIndex->location, {iterIndex->pname(), baseExpr->type->pname()});
    }
    if (!iterable->getIndexType()->equals(exprFrom->type)) {
        return errHandler.addError(E10036, &iterIndex->location, {iterIndex->pname(), exprFrom->type->pname()});
    }
    if (!iterable->getIndexType()->equals(exprTo->type)) {
        return errHandler.addError(E10036, &iterIndex->location, {iterIndex->pname(), exprFrom->type->pname()});
    }
    validateSliceBounds(iterIndex);
}

void LgsSema::visitGroup(LgsGroup* group) {
    for (const auto targetSymbol : group->targetSymbols) {
        for (const auto type : group->types) {
            const auto method = type->getMethod(targetSymbol->name);
            if (!method) continue;
            method->funcType->isVirtual = true;
            group->addMethod(method);
        }
    }
}

void LgsSema::visitForIsFirst(LgsVariable* variable) {
    const auto loop = stack.currentLoop();
    if (!loop) {
        return errHandler.addError(E10060, &variable->location);
    }
    if (dynamic_cast<LgsWhileLoop*>(loop)) {
        return errHandler.addError(E10065, &variable->location);
    }
    const auto varDec = new LgsVarDec("for.isLast", new LgsIntConst(&LGS_BOOL, false));
    varDec->isConst = true;
    loop->isFirst = varDec;
}

void LgsSema::visitForIsLast(LgsVariable* variable) {
    const auto loop = stack.currentLoop();
    if (!loop) {
        return errHandler.addError(E10060, &variable->location);
    }
    if (dynamic_cast<LgsInfiniteLoop*>(loop)) {
        return errHandler.addError(E10061, &variable->location);
    }
    if (dynamic_cast<LgsWhileLoop*>(loop)) {
        return errHandler.addError(E10065, &variable->location);
    }
    const auto varDec = new LgsVarDec("for.isLast", new LgsIntConst(&LGS_BOOL, false));
    varDec->isConst = true;
    loop->isLast = varDec;
}

void LgsSema::validateObjImplements(LgsObject* obj, const std::vector<LgsType*>& interfaces) {
    std::unordered_set<std::string> interfacesNames;
    for (const auto implementsInterface : interfaces) {
        const auto interface = implementsInterface->asInterface();
        if (!interface) {
            errHandler.addError(E10025, &implementsInterface->location, {implementsInterface->pname()});
            continue;
        }
        validateObjInterface(obj, interface);
        for (const auto parentInterface : interface->interfaces) {
            validateObjInterface(obj, parentInterface->asInterface());
        }
    }
}

void LgsSema::validateArgs(const LgsFuncCall* funcCall) {
    for (int i = funcCall->func->funcType->isStatic; i < funcCall->args.size(); ++i) {
        const auto arg = funcCall->args[i];
        const auto param = funcCall->func->funcType->params[i];
        castExprToType(arg, param.type);
    }
}

bool LgsSema::resolveLoopVars(LgsForeachLoop* foreachLoop, LgsUnaryExpr* iterExpr, const LgsIterable* iterable) {
    const auto varDecSize = foreachLoop->loopVars.size();
    const auto unpackCount = iterable->getUnpackCount();
    foreachLoop->withIndex = unpackCount + 1 == varDecSize;
    const bool withIndex = foreachLoop->withIndex;
    if (withIndex) {
        foreachLoop->loopVars[0]->type = &LGS_INT;
        foreachLoop->loopVars[0]->expr = LGS_INT.getZeroValue();
    } else if (unpackCount != varDecSize) {
        errHandler.addError(E10041, &iterExpr->location, {iterExpr->pname(), std::to_string(unpackCount),
                                                          std::to_string(unpackCount + 1), std::to_string(varDecSize)});
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

std::string getMissingImplementsStr(const std::vector<LgsField*>& fields, const std::vector<LgsFunc*>& methods) {
    std::stringstream str;
    str << "Missing fields/methods:";
    if (!fields.empty()) {
        str << LGS_ERROR_PADDING << "Fields:";
        for (const auto& field : fields) {
            str << LGS_ERROR_PADDING << "\t- " << field->name << ": " << field->type->pname();
        }
    }
    if (!methods.empty()) {
        str << LGS_ERROR_PADDING << "Methods:";
        for (const auto& method : methods) {
            str << LGS_ERROR_PADDING << "\t- " << method->funcType->pname();
        }
    }
    return str.str();
}

void LgsSema::validateObjInterface(LgsObject* obj, LgsInterface* interface) {
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
        errHandler.addError(E10016, &obj->location,
                            {obj->pname(), interface->name, getMissingImplementsStr(missingFields, missingMethods)});
    }
}

void LgsSema::validateIndex(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto exprFrom = iterIndex->index->from;
    const auto iterable = baseExpr->type->asIterable();
    if (!iterable->getIndexType()->equals(exprFrom->type)) {
        return errHandler.addError(E10036, &iterIndex->location, {iterIndex->pname(), exprFrom->type->pname()});
    }
    if (const auto sArr = iterable->asSArray()) {
        const auto i = exprFrom->getConstInt();
        const auto bound = sArr->sizeExpr->getConstInt();
        if (i >= bound) {
            return errHandler.addError(E10003, &iterIndex->location, {iterIndex->pname(), std::to_string(bound)});
        }
    }
}

void LgsSema::validateSliceBounds(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto exprFrom = iterIndex->index->from;
    const auto exprTo = iterIndex->index->to;
    const auto iterable = baseExpr->type->asIterable();
    if (const auto sArr = iterable->asSArray()) {
        const auto iterSizeFrom = exprFrom->getConstInt();
        const auto iterSizeTo = exprTo->getConstInt();
        if (iterSizeFrom > iterSizeTo) {
            return errHandler.addError(E10037, &iterIndex->location, {iterIndex->pname()});
        }
        const auto i = iterSizeFrom;
        const auto j = iterSizeTo;
        const auto bound = sArr->sizeExpr->getConstInt();
        if (i >= bound || j >= bound) {
            return errHandler.addError(E10003, &iterIndex->location, {iterIndex->pname(), std::to_string(bound)});
        }
    }
}

bool LgsSema::validateFieldVisibility(LgsField* field, const LgsObject* parent) {
    if (parent && parent->singleton) return true;
    if (!field || field->isVirtual) return false;
    if (!field->isPublic && file->id != field->location.fileID) {
        if (parent) errHandler.addError(E10030, &field->location, {field->name, parent->name});
        return false;
    }
    return true;
}

bool LgsSema::validateMethodVisibility(LgsFuncCall* methodCall, const LgsObject* parent) {
    if (parent && parent->singleton) return true;
    const auto method = methodCall->func;
    if (!method || method->funcType->isVirtual) return false;
    if (!method->funcType->isPublic) {
        if (file->id != method->location.fileID) {
            errHandler.addError(E10031, &methodCall->location, {method->funcType->name, method->funcType->parentName});
            return false;
        }
    }
    return true;
}

bool LgsSema::validateBlockControlFlow(const LgsStmtsBlock* stmtBlock, const LgsFunc* func) {
    if (func->funcType->rt->isVoid()) return true;
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

void LgsSema::castExprToType(LgsExpr* expr, LgsType* toType) {
    if (expr->type == toType) return;
    if (!expr->castTo(toType)) {
        errHandler.addError(E10018, &expr->location, {expr->type->pname(), toType->pname()});
    }
}

void LgsSema::matchExprToType(LgsExpr* expr, LgsType* type) {
    if (expr->type == type) return;
    if (expr->isNull) {
        // null must have a type
        if (!type || type->isUnknown()) {
            errHandler.addError(E10024, &expr->location);
            return;
        }
        // type must be nullable
        if (!type->asNullable()) {
            errHandler.addError(E10023, &type->location, {type->pname(), type->pname()});
            return;
        }
        return;
    }
    if (!type || !expr->type) return;
    if (!type->equals(expr->type)) {
        errHandler.addError(E10001, &expr->location, {type->pname(), expr->type->pname()});
        return;
    }
    castExprToType(expr, type);
}

void LgsSema::resolveFuncCall(LgsFuncCall* funcCall) {
    const auto symbol = getSymbol(funcCall->name, &funcCall->location);
    if (!symbol) return;
    if (symbol->symbolType == FUNC) {
        const auto func = symbol->func;
        if (funcCall->equals(func->funcType)) {
            funcCall->func = func;
            funcCall->setType(func->funcType->rt);
        } else {
            errHandler.addError(E10015, &funcCall->location, {funcCall->name, funcCall->pname(), func->pname()});
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

bool LgsSema::resolveMethodCall(LgsFuncCall* methodCall, LgsType* parentType) {
    auto name = methodCall->name;
    const auto method = parentType->getMethod(name);
    if (!method) {
        errHandler.addError(E10005, &methodCall->location, {name, parentType->pname()});
        return false;
    }
    if (methodCall->equals(method->funcType)) {
        methodCall->func = method;
        methodCall->setType(method->funcType->rt);
    } else {
        errHandler.addError(E10034, &methodCall->location,
                            {parentType->pname(), name, methodCall->pname(), method->pname()});
        return false;
    }
    return true;
}

LgsField* LgsSema::resolveVectorField(LgsVariable* fieldVar, LgsVec* vec) {
    const auto scalarPositions = resolveScalars(fieldVar, vec);
    if (scalarPositions.empty()) return nullptr;
    const auto fieldName = fieldVar->name;
    const auto dim = fieldName.size();
    LgsField* field = nullptr;
    if (dim == 1) {
        field = new LgsField(fieldName, vec->baseType);
    } else {
        field = new LgsField(fieldName, new LgsVec(dim));
    }
    vec->addField(field);
    return field;
}

std::vector<uint8_t> LgsSema::resolveScalars(LgsVariable* fieldVar, LgsVec* vec) {
    assert(vec->isVector());
    const auto fieldName = fieldVar->name;
    const auto dim = vec->dim;
    if (fieldName.empty() || fieldName.size() > 4) {
        errHandler.addError(E10069, &fieldVar->location, {vec->pname()});
        return {};
    }

    const auto expectedSet = LgsVec::getSwizzleSet(fieldName[0]);
    if (expectedSet < 0) {
        errHandler.addError(E10070, &fieldVar->location, {fieldName, vec->pname()});
        return {};
    }

    std::vector<uint8_t> indices;
    indices.reserve(fieldName.size());
    for (const char c : fieldName) {
        if (LgsVec::getSwizzleSet(c) != expectedSet) {
            errHandler.addError(E10070, &fieldVar->location, {fieldName, vec->pname()});
            return {};
        }
        const auto componentIndex = LgsVec::getComponentIndex(c);
        if (componentIndex >= dim) {
            errHandler.addError(E10070, &fieldVar->location, {fieldName, vec->pname()});
            return {};
        }
        indices.push_back(componentIndex);
    }
    return indices;
}

LgsSymbol* LgsSema::getSymbol(const std::string& name, LgsLocation* location) {
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

void LgsSema::addLocalSymbol(const LgsSymbol& newSymbol) {
    auto symbolName = *newSymbol.name;
    const auto symbol = globals.getSymbol(symbolName);
    if (symbol && symbol->isBuiltin) {
        return errHandler.addError(E10053, newSymbol.location, {symbolName});
    }
    if (file->symbolTable.getSymbol(symbolName)) {
        return errHandler.addError(E10011, newSymbol.location, {symbolName});
    }
    stack.getSymbolTable().addSymbol(newSymbol, &errHandler);
}
