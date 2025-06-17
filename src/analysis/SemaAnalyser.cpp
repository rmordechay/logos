#include "analysis/SemaAnalyser.h"
#include "data/LgsErrors.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsObjectFile.h"
#include "logos/LgsApp.h"
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
#include "exprs/unary/LgsEnumField.h"
#include "exprs/unary/constants/LgsTypeConst.h"
#include "stmts/LgsBreakStmt.h"
#include "types/LgsEnum.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsPostfixExpr.h"
#include "exprs/unary/LgsPrefixExpr.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "files/LgsMainFile.h"
#include "logos/LgsConfig.h"
#include "logos/LgsErrHandler.h"
#include "loops/LgsInfiniteLoop.h"
#include "stmts/LgsContinueStmt.h"
#include "stmts/LgsPatternMatch.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsArray.h"
#include "types/LgsGroup.h"
#include "types/LgsInterface.h"
#include "utils/LgsUtils.h"
#include <loops/LgsForeachLoop.h>
#include <loops/LgsForLoop.h>
#include <loops/LgsRangeLoop.h>
#include <stmts/LgsAssignment.h>
#include <stmts/LgsIfStmt.h>

void SemaAnalyser::start() {
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
    for (const auto lgsEnum : mainFile->enums) {
        visitEnum(lgsEnum);
    }
    for (const auto group : mainFile->groups) {
        visitGroup(group);
    }
    for (const auto [_, func] : mainFile->funcs) {
        visitFunc(func);
    }
}

void SemaAnalyser::visitObject(LgsObject* obj) {
    for (const auto& [_, field] : obj->fields) {
        visitField(field);
    }
    for (const auto& [_, method] : obj->methods) {
        visitFunc(method);
        method->funcType->isStaticMethod = obj->isSingleton;
    }
    visitObjectImplements(obj);
}

void SemaAnalyser::visitInterface(LgsInterface* interface) const {}

void SemaAnalyser::visitFunc(LgsFunc* func) {
    stack.enterFunc(func);
    for (auto& param : func->funcType->params) {
        visitParam(&param);
    }
    visitStmtBlock(func->stmtBlock);
    validateFuncControlFlow(func);
    stack.exitFunc();
}

void SemaAnalyser::visitParam(LgsParam* param) {
    if (param->expr) {
        visitExpr(param->expr);
        validateExprType(param->expr, param->type);
    } else if (param->isVariadic) {
        assert(0);
    }
    addLocalSymbol(param->name, LgsSymbol(param));
}

void SemaAnalyser::visitField(LgsField* field) {
    if (field->expr) {
        visitExpr(field->expr);
        validateExprType(field->expr, field->type);
    }
}

void SemaAnalyser::visitStmt(LgsStmt* stmt) {
    if (const auto varDec = stmt->asVarDec()) {
        visitVarDec(varDec);
    } else if (const auto ifStmt = stmt->asIfStmt()) {
        visitIfStmt(ifStmt);
    } else if (const auto patternMatch = stmt->asPatternMatch()) {
        visitPatternMatch(patternMatch);
    } else if (const auto loopStmt = stmt->asLoop()) {
        visitLoopStmt(loopStmt);
    } else if (const auto assignment = stmt->asAssignment()) {
        visitAssignment(assignment);
    } else if (const auto funcCall = stmt->asFuncCall()) {
        visitFuncCall(funcCall);
    } else if (const auto postfixExpr = stmt->asPostfixExpr()) {
        visitPostfixExpr(postfixExpr);
    } else if (const auto selection = stmt->asSelection()) {
        visitSelection(selection);
    } else if (const auto returnStmt = stmt->asReturn()) {
        visitReturnStmt(returnStmt);
    } else if (const auto breakStmt = stmt->asBreakStmt()) {
        visitBreakStmt(breakStmt);
    } else if (const auto continueStmt = stmt->asContinue()) {
        visitContinueStmt(continueStmt);
    }
}

void SemaAnalyser::visitStmtBlock(LgsStmtBlock* stmtBlock) {
    if (!stmtBlock) return;
    for (const auto& stmt : stmtBlock->stmts) {
        visitStmt(stmt);
    }
    const auto lastStmt = stmtBlock->lastStmt();
    if (lastStmt->asReturn()) {
        stmtBlock->hasReturn = true;
    }
}

void SemaAnalyser::visitVarDec(LgsVarDec* varDec) {
    if (varDec->type && varDec->expr) {
        varDec->type = resolveType(varDec->type);
        visitExpr(varDec->expr);
        validateExprType(varDec->expr, varDec->type);
    } else if (varDec->type) {
        varDec->type = resolveType(varDec->type);
        varDec->expr = varDec->type->getZeroValue();
        visitExpr(varDec->expr);
    } else if (varDec->expr) {
        visitExpr(varDec->expr);
        varDec->type = varDec->expr->type;
    } else {
        assert(0);
    }
    addLocalSymbol(varDec->name, LgsSymbol(varDec));
}

void SemaAnalyser::visitAssignment(LgsAssignment* assignment) {
    const auto lValue = assignment->lValue;
    const auto rValue = assignment->rValue;
    visitExpr(lValue);
    visitExpr(rValue);
    const auto lType = lValue->type;
    const auto rType = rValue->type;
    if (lValue->isImmutable) return errHandler.handleError(E10051, &lValue->location, {lValue->prettyName()});
    if (lType && rType && lType->equals(rType)) return;
    return errHandler.handleError(E10001, &assignment->location, {lType->prettyName(), rType->prettyName()});
}

void SemaAnalyser::visitIfStmt(LgsIfStmt* ifStmt) {
    stack.enterScope(IF_SCOPE, ifStmt);
    visitExpr(ifStmt->ifCond);
    visitStmtBlock(ifStmt->ifStmtBlock);
    for (const auto& elseIfCond : ifStmt->elseIfConds) {
        visitExpr(elseIfCond);
    }
    for (const auto& elseIfStmtBlock : ifStmt->elseIfStmtBlocks) {
        visitStmtBlock(elseIfStmtBlock);
    }
    if (ifStmt->elseStmtBlock) {
        visitStmtBlock(ifStmt->elseStmtBlock);
    }
    stack.exitScope(IF_SCOPE);
}

void SemaAnalyser::visitPatternMatch(const LgsPatternMatch* patternMatching) {
    const auto baseExpr = patternMatching->expr;
    if (!baseExpr) {
        return visitBoolPatternMatching(patternMatching);
    }
    visitExpr(baseExpr);
    const auto baseExprType = baseExpr->type;
    for (const auto patternExpr : patternMatching->patterns) {
        visitExpr(patternExpr);
        if (!patternExpr->type) continue;
        if (!patternExpr->type->equals(baseExprType)) {
            return errHandler.handleError(E10014, &patternExpr->location, {patternExpr->type->prettyName(), baseExprType->prettyName()});
        }
    }
    for (const auto& patternsStmtBlock : patternMatching->patternsStmtBlocks) {
        visitStmtBlock(patternsStmtBlock);
    }
    visitStmtBlock(patternMatching->elseStmtBlock);
}

void SemaAnalyser::visitBoolPatternMatching(const LgsPatternMatch* patternMatching) const {}

void SemaAnalyser::visitLoopStmt(LgsForLoop* loopStmt) {
    stack.enterScope(LOOP_SCOPE, loopStmt);
    if (const auto rangeLoop = dynamic_cast<LgsRangeLoop*>(loopStmt)) {
        visitRangeLoop(rangeLoop);
    } else if (const auto foreachLoop = dynamic_cast<LgsForeachLoop*>(loopStmt)) {
        visitForeachLoop(foreachLoop);
    } else if (const auto infiniteLoop = dynamic_cast<LgsInfiniteLoop*>(loopStmt)) {
        visitInfiniteLoop(infiniteLoop);
    } else {
        assert(0);
    }
    stack.exitScope(LOOP_SCOPE);
}

void SemaAnalyser::visitRangeLoop(const LgsRangeLoop* rangeLoop) {
    const auto loopVar = rangeLoop->loopVars[0];
    addLocalSymbol(loopVar->name, LgsSymbol(loopVar));
    visitStmtBlock(rangeLoop->stmtBlock);
}

void SemaAnalyser::visitForeachLoop(LgsForeachLoop* foreachLoop) {
    const auto iterExpr = foreachLoop->iterExpr;
    visitUnaryExpr(iterExpr);
    const auto iterable = iterExpr->type->asIterable();
    if (!iterable) {
        // If type is not defined an error was already thrown
        if (iterExpr->type) errHandler.handleError(E10002, &iterExpr->location, {iterExpr->prettyName()});
        return;
    }
    if (setLoopVars(foreachLoop, iterExpr, iterable)) return;
    for (const auto varDec : foreachLoop->loopVars) {
        addLocalSymbol(varDec->name, LgsSymbol(varDec));
    }
    visitStmtBlock(foreachLoop->stmtBlock);
}

void SemaAnalyser::visitInfiniteLoop(const LgsInfiniteLoop* infiniteLoop) {
    visitStmtBlock(infiniteLoop->stmtBlock);
}

void SemaAnalyser::visitReturnStmt(const LgsReturn* returnStmt) {
    const auto currentFunc = stack.currentFunc;
    const auto funcType = currentFunc->funcType;
    const auto retExpr = returnStmt->expr;
    if (retExpr) {
        retExpr->isReturnExpr = true;
        currentFunc->returnExprs.push_back(retExpr);
        visitExpr(retExpr);
    }
    const auto rt = funcType->rt;
    if (rt->isVoid && retExpr) {
        errHandler.handleError(E10027, &returnStmt->location, {retExpr->type->prettyName()});
    } else if (!rt->isVoid && !retExpr) {
        errHandler.handleError(E10026, &returnStmt->location, {funcType->name, rt->prettyName()});
    } else if (retExpr && retExpr->type && !rt->equals(retExpr->type)) {
        errHandler.handleError(E10004, &returnStmt->location, {funcType->name, rt->prettyName(), retExpr->type->prettyName()});
    }
}

void SemaAnalyser::visitBreakStmt(const LgsBreakStmt* breakStmt) {
    if (!stack.getLoop()) {
        return errHandler.handleError(E10017, &breakStmt->location);
    }
}

void SemaAnalyser::visitContinueStmt(const LgsContinueStmt* continueStmt) {
    if (!stack.getLoop()) {
        return errHandler.handleError(E10038, &continueStmt->location);
    }
}

void SemaAnalyser::visitEnum(const LgsEnum* lgsEnum) const {}

void SemaAnalyser::visitExpr(LgsExpr* expr) {
    if (!expr) return;
    if (const auto castExpr = dynamic_cast<LgsCast*>(expr)) {
        visitCast(castExpr);
    } else if (const auto unaryExpr = dynamic_cast<LgsUnaryExpr*>(expr)) {
        visitUnaryExpr(unaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
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
    castExpr->toValue = fromValue->convertExpr(castExpr->toType);
    if (!castExpr->toValue) {
        errHandler.handleError(E10018, &castExpr->location, {fromValue->type->prettyName(), castExpr->toType->prettyName()});
    }
}

void SemaAnalyser::visitUnaryExpr(LgsUnaryExpr* unaryExpr) {
    if (const auto instance = unaryExpr->asInstance()) visitInstance(instance);
    else if (const auto funcCall = unaryExpr->asFuncCall()) visitFuncCall(funcCall);
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
    setBinaryExprType(binaryExpr);
}

void SemaAnalyser::visitArrayExpr(LgsArrayExpr* array) {
    for (const auto element : array->initialElements) {
        visitExpr(element);
    }
    if (array->type->asArray()->isStatic) {
        visitStaticArray(array);
    } else {
        visitDynamicArray(array);
    }
}

void SemaAnalyser::visitDynamicArray(const LgsArrayExpr* array) {
    const auto& initialElements = array->initialElements;
    const auto arr = array->type->asArray();
    const auto& arrType = arr;
    if (initialElements.empty()) {
        if (!arrType->baseType) return errHandler.handleError(E10049, &array->location);
    } else {
        arr->baseType = initialElements.front()->type;
    }
    if (!arrType->sizeExpr) {
        arr->sizeExpr = new LgsIntConst(initialElements.size());
    }
}

void SemaAnalyser::visitStaticArray(const LgsArrayExpr* arrayExpr) {
    const auto& initialElements = arrayExpr->initialElements;
    const auto arr = arrayExpr->type->asArray();
    if (initialElements.empty() && !arr->baseType) {
        return errHandler.handleError(E10049, &arrayExpr->location);
    }
    for (const auto element : initialElements) {
        element->type->isStatic = true;
        visitExpr(element);
    }
    if (!arr->baseType) {
        arr->baseType = initialElements.front()->type;
    }
}

void SemaAnalyser::visitHashMap(LgsHashMap* hashMap) {
    const auto typePair = hashMap->type->asMap()->typePair;
    if (typePair->key && typePair->value) return;
    if (hashMap->initialElements.empty()) return errHandler.handleError(E10049, &hashMap->location);
    const auto firstElement = hashMap->initialElements.front();
    typePair->key = firstElement->key->type;
    typePair->value = firstElement->value->type;
}

void SemaAnalyser::visitVariable(LgsVariable* variable) {
    const auto symbol = getSymbol(variable->name, &variable->location);
    if (!symbol) return;
    variable->ref.symbolType = symbol->symbolType;
    symbol->refs.push_back(variable);
    switch (symbol->symbolType) {
    case VAR_DEC:
        variable->ref.varDec = symbol->varDec;
        variable->isImmutable = symbol->varDec->isImmutable;
        variable->setType(symbol->varDec->type);
        break;
    case FIELD:
        variable->ref.field = symbol->field;
        variable->isImmutable = symbol->field->isImmutable;
        variable->setType(symbol->field->type);
        break;
    case PARAM:
        variable->ref.param = symbol->param;
        variable->isImmutable = true;
        variable->setType(symbol->param->type);
        break;
    case ENUM_FIELD:
        variable->ref.enumField = symbol->enumField;
        variable->isImmutable = true;
        variable->setType(symbol->enumField->type);
        break;
    case FUNC:
        variable->ref.func = symbol->func;
        variable->isImmutable = true;
        variable->setType(symbol->func->funcType);
        break;
    case OBJECT:
        variable->ref.object = symbol->object;
        variable->isImmutable = true;
        variable->setType(symbol->object);
        break;
    default:
        assert(false);
    }
    assert(variable->ref.symbolType != UNKNOWN);
}

void SemaAnalyser::visitSelection(LgsSelection* selection) {
    const auto exprs = selection->exprs;
    visitFirstSelection(exprs[0]);
    visitInnerSelections(selection);
    selection->setType(selection->lastExpr()->type);
}

void SemaAnalyser::visitFirstSelection(LgsExpr* firstExpr) {
    if (const auto variable = firstExpr->asVariable()) {
        visitVariable(variable);
    } else if (const auto funcCall = firstExpr->asFuncCall()) {
        visitFuncCall(funcCall);
    } else if (const auto iterIndex = firstExpr->asIterIndex()) {
        visitIterIndex(iterIndex);
    } else if (const auto typeConst = firstExpr->asTypeConst()) {
        typeConst->type = resolveType(typeConst->type);
    } else {
        assert(0);
    }
}

void SemaAnalyser::visitInnerSelections(const LgsSelection* selection) {
    const auto exprs = selection->exprs;
    for (int i = 0; i < exprs.size() - 1; ++i) {
        const auto parentExpr = exprs[i];
        const auto childExpr = exprs[i + 1];
        if (const auto var = childExpr->asVariable()) {
            visitFieldSelection(parentExpr, var);
        } else if (const auto methodCall = childExpr->asFuncCall()) {
            visitMethodCall(methodCall, parentExpr->type);
        }
    }
}

void SemaAnalyser::visitFieldSelection(const LgsExpr* parentExpr, LgsVariable* childField) {
    const auto parentType = parentExpr->type;
    const auto field = parentType->getField(childField->name);
    if (!field) {
        return errHandler.handleError(E10005, &childField->location, {childField->getExprName(), parentType->prettyName()});
    }
    childField->setType(field->type);
    childField->ref = LgsSymbol(field);
    if (!field->isPublic && file->absPath != *field->location.filePath) {
        errHandler.handleError(E10030, &childField->location, {childField->getExprName(), *field->parentName});
    }
}

void SemaAnalyser::visitFuncCall(LgsFuncCall* funcCall) {
    for (const auto arg : funcCall->args) {
        visitExpr(arg);
    }
    resolveFuncCall(funcCall);
    if (!funcCall->func) return;
    const auto& funcType = funcCall->func->funcType;
    if (funcType->isVariadic) return;
    for (int i = 0; i < funcType->params.size(); ++i) {
        const auto param = funcType->params[i];
        const auto arg = funcCall->args[i];
        castImplicitly(arg, param.type);
    }
}

void SemaAnalyser::visitInstance(LgsInstance* instance) {
    const auto symbol = getSymbol(instance->name, &instance->location);
    if (!symbol) return;
    if (symbol->symbolType != OBJECT) {
        return errHandler.handleError(E10022, &instance->location, {instance->name});
    }
    if (symbol->object->isSingleton) {
        return errHandler.handleError(E10032, &instance->location, {instance->name});
    }

    if (!instance->obj) {
        instance->obj = symbol->object;
        instance->type = instance->obj;
    }

    for (const auto [_, field] : instance->obj->fields) {
        if (field->isImmutable && !field->expr) {
            errHandler.handleError(E10029, &field->location, {field->name});
            continue;
        }
    }

    unordered_set<string> initializedFields;
    for (const auto& arg : instance->args) {
        visitExpr(arg->expr);
        const auto field = instance->obj->getField(arg->name);
        if (!field) {
            errHandler.handleError(E10005, &arg->location, {arg->name, instance->obj->name});
            continue;
        }
        field->expr = arg->expr;
        initializedFields.insert(field->name);
    }

    for (const auto& [name, field] : instance->obj->fields) {
        if (initializedFields.count(name)) continue;
        if (!field->expr) {
            setZeroField(field);
        }
    }

    assert(instance->obj);
}

void SemaAnalyser::visitPostfixExpr(LgsPostfixExpr* postfixExpr) {
    const auto baseExpr = postfixExpr->expr;
    visitUnaryExpr(baseExpr);
    const auto type = baseExpr->type;
    if (!type->asInt()) {
        return errHandler.handleError(E10050, &postfixExpr->location, {type->prettyName()});
    }
    postfixExpr->setType(type);
}

void SemaAnalyser::visitPrefixExpr(LgsPrefixExpr* prefixExpr) {
    const auto baseExpr = prefixExpr->expr;
    visitExpr(baseExpr);
    const auto type = baseExpr->type;
    prefixExpr->setType(type);
}

void SemaAnalyser::visitMethodCall(LgsFuncCall* methodCall, const LgsType* parentType) {
    if (!parentType) assert(0);
    for (const auto& arg : methodCall->args) {
        visitExpr(arg);
    }
    if (resolveMethodCall(methodCall, parentType)) return;
    validateMethodVisibility(methodCall);
    if (methodCall->isSpread) {
        const auto lastArg = methodCall->args[methodCall->args.size() - 1];
        if (!lastArg->type->asIterable()) {
            return errHandler.handleError(E10052, &methodCall->location, {lastArg->prettyName(), lastArg->type->prettyName()});
        }
    }
}

void SemaAnalyser::visitAnonymousFunc(LgsFuncCall* funcCall, LgsFuncType* funcType) {
    assert(funcType->isAnonymous);
    for (const auto& arg : funcCall->args) {
        visitExpr(arg);
    }
    if (!funcCall->equals(funcType)) {
        errHandler.handleError(E10006, &funcCall->location, {funcCall->name});
        return;
    }
    funcCall->type = funcType->rt;
    funcCall->func = new LgsFunc(funcType);
}

void SemaAnalyser::visitIterIndex(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto exprFrom = iterIndex->index->from;
    const auto exprTo = iterIndex->index->to;
    visitUnaryExpr(baseExpr);
    visitExpr(exprFrom);
    visitExpr(exprTo);
    if (!baseExpr->type) return;
    const auto iterable = baseExpr->type->asIterable();
    if (!iterable && baseExpr->type) {
        return errHandler.handleError(E10002, &iterIndex->location, {iterIndex->baseExpr->prettyName()});
    }
    if (exprTo) {
        visitSlice(iterIndex);
        iterIndex->setType(iterable);
    } else {
        validateIndex(iterIndex);
        iterIndex->setType(iterable->getValueType());
    }
}

void SemaAnalyser::visitSlice(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto exprFrom = iterIndex->index->from;
    const auto exprTo = iterIndex->index->to;
    const auto iterable = baseExpr->type->asIterable();
    if (!baseExpr->type->canSlice) {
        return errHandler.handleError(E10042, &iterIndex->location, {iterIndex->prettyName(), baseExpr->type->prettyName()});
    }
    if (!iterable->getIndexType()->equals(exprFrom->type)) {
        return errHandler.handleError(E10036, &iterIndex->location, {iterIndex->prettyName(), exprFrom->type->prettyName()});
    }
    if (!iterable->getIndexType()->equals(exprTo->type)) {
        return errHandler.handleError(E10036, &iterIndex->location, {iterIndex->prettyName(), exprFrom->type->prettyName()});
    }
    validateSliceBounds(iterIndex);
}

void SemaAnalyser::visitGroup(LgsGroup* group) const {
    for (const auto targetSymbol : group->targetSymbols) {
        for (const auto type : group->types) {
            const auto method = type->getMethod(targetSymbol->name);
            if (!method) continue;
            method->funcType->isVirtual = true;
            group->addMethod(method);
        }
    }
}

void SemaAnalyser::visitObjectImplements(LgsObject* obj) {
    for (int i = 0; i < obj->interfaces.size(); ++i) {
        const auto implement = obj->interfaces[i];
        if (!implement) continue;
        const auto interface = implement->asInterface();
        if (!interface) {
            errHandler.handleError(E10025, &implement->location, {implement->prettyName()});
            continue;
        }

        vector<LgsFunc*> missingFuncs;
        for (const auto& [name, interfaceFunc] : interface->methods) {
            const auto objMethod = obj->getMethod(name);
            if (objMethod && objMethod->funcType->equals(interfaceFunc->funcType)) {
                objMethod->implementsFunc = interfaceFunc;
                continue;
            }
            missingFuncs.emplace_back(interfaceFunc);
        }

        if (!missingFuncs.empty()) {
            errHandler.handleError(E10016, &obj->location, {obj->name, interface->interfaceName, getFuncsAsStr(missingFuncs)});
        }
    }
}

void SemaAnalyser::castImplicitly(LgsExpr* expr, LgsType* type) const {
    if (expr->type == type) return;
    freeType(expr->type);
    expr->type = type;
}

bool SemaAnalyser::setSelectionFieldType(const LgsUnaryExpr* parent, LgsVariable* fieldVariable) {
    const auto type = parent->type;
    const auto field = type ? type->getField(fieldVariable->name) : nullptr;
    if (!type || !field) {
        errHandler.handleError(E10005, &fieldVariable->location, {fieldVariable->prettyName(), type->prettyName()});
        return false;
    }
    fieldVariable->setType(field->type);
    return true;
}

void SemaAnalyser::setZeroField(LgsField* field) const {
    if (const auto fieldObj = field->type->asObject()) {
        for (const auto& [name, field] : fieldObj->fields) {
            setZeroField(field);
        }
    } else {
        field->expr = field->type->getZeroValue();
    }
}

void SemaAnalyser::setBinaryExprType(LgsBinaryExpr* binaryExpr) {
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

bool SemaAnalyser::setLoopVars(LgsForeachLoop* foreachLoop, LgsUnaryExpr* iterExpr, const LgsIterable* iterable) {
    const auto varDecSize = foreachLoop->loopVars.size();
    foreachLoop->withIndex = iterable->unpackLength + 1 == varDecSize;
    const bool withIndex = foreachLoop->withIndex;
    if (withIndex) {
        foreachLoop->loopVars[0]->type = &LGS_INT;
        foreachLoop->loopVars[0]->expr = LGS_INT.getZeroValue();
    } else if (iterable->unpackLength != varDecSize) {
        errHandler.handleError(E10041, &iterExpr->location, {iterExpr->prettyName(), to_string(iterable->unpackLength), to_string(iterable->unpackLength + 1), to_string(varDecSize)});
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

void SemaAnalyser::validateIndex(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto exprFrom = iterIndex->index->from;
    const auto iterable = baseExpr->type->asIterable();
    if (!iterable->getIndexType()->equals(exprFrom->type)) {
        return errHandler.handleError(E10036, &iterIndex->location, {iterIndex->prettyName(), exprFrom->type->prettyName()});
    }
    if (baseExpr->type->isStatic) {
        const auto i = exprFrom->getConstInt();
        const auto bound = iterable->iterLen;
        if (i >= bound) {
            return errHandler.handleError(E10003, &iterIndex->location, {iterIndex->prettyName(), to_string(bound)});
        }
    }
}

void SemaAnalyser::validateSliceBounds(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto exprFrom = iterIndex->index->from;
    const auto exprTo = iterIndex->index->to;
    const auto iterable = baseExpr->type->asIterable();
    if (baseExpr->type->isStatic) {
        if (exprFrom->getConstInt() > exprTo->getConstInt()) {
            return errHandler.handleError(E10037, &iterIndex->location, {iterIndex->prettyName()});
        }
        const auto i = exprFrom->getConstInt();
        const auto j = exprTo->getConstInt();
        const auto bound = iterable->iterLen;
        if (i >= bound || j >= bound) {
            return errHandler.handleError(E10003, &iterIndex->location, {iterIndex->prettyName(), to_string(bound)});
        }
    }
}

void SemaAnalyser::validateMethodVisibility(const LgsFuncCall* methodCall) {
    const auto method = methodCall->func;
    if (!method) return;
    if (!method->funcType->isPublic && file->absPath != *method->location.filePath) {
        errHandler.handleError(E10031, &method->location, {method->funcType->name, method->funcType->parentName});
    }
}

void SemaAnalyser::validateExprType(LgsExpr* expr, LgsType* type) {
    assert(expr);
    if (expr->isNull) {
        // null must have a type
        if (!type) return errHandler.handleError(E10024, &expr->location);
        // type must be nullable
        if (!type->isNullable) return errHandler.handleError(E10023, &type->location, {type->prettyName(), type->prettyName()});
    }
    if (!type || !expr->type) return;
    if (!expr->type->equals(type)) {
        return errHandler.handleError(E10001, &expr->location, {type->prettyName(), expr->type->prettyName()});
    }
    castImplicitly(expr, type);
}

void SemaAnalyser::validateFuncControlFlow(const LgsFunc* func) {
    if (func->funcType->rt->isVoid) return;
    if (!validateBlockControlFlow(func->stmtBlock, func)) {
        errHandler.handleError(E10055, &func->location, {func->funcType->name});
    }
}

bool SemaAnalyser::validateBlockControlFlow(const LgsStmtBlock* stmtBlock, const LgsFunc* func) {
    if (!stmtBlock) return true;
    if (stmtBlock->hasReturn) return true;
    auto isValid = false;
    for (const auto stmt : stmtBlock->stmts) {
        if (const auto ifStmt = stmt->asIfStmt()) {
            isValid = validateBlockControlFlow(ifStmt->ifStmtBlock, func);
            for (const auto elseIfStmtBlock : ifStmt->elseIfStmtBlocks) {
                isValid = isValid && validateBlockControlFlow(elseIfStmtBlock, func);
            }
            isValid = isValid && validateBlockControlFlow(ifStmt->elseStmtBlock, func);
        }
        if (const auto loop = stmt->asLoop()) {
            isValid = isValid && validateBlockControlFlow(loop->stmtBlock, func);
        }
        if (const auto patternMatch = stmt->asPatternMatch()) {
            for (const auto patternsStmtBlock : patternMatch->patternsStmtBlocks) {
                isValid = isValid && validateBlockControlFlow(patternsStmtBlock, func);
            }
            isValid = isValid && validateBlockControlFlow(patternMatch->elseStmtBlock, func);
        }
    }
    return isValid;
}

LgsSymbol* SemaAnalyser::getSymbol(const string& name, const Location* location) {
    if (const auto globalSymbol = globals.getSymbol(name)) {
        return globalSymbol;
    }
    if (const auto fileSymbol = file->symbolTable.getSymbol(name)) {
        return fileSymbol;
    }
    for (const auto externFilePath : file->externFiles) {
        auto externalFile = externalFiles.find(externFilePath->value);
        if (externalFile == externalFiles.end()) continue;
        const auto symbol = externalFile->second->symbolTable.getSymbol(name);
        if (symbol) return symbol;
    }
    if (const auto symbol = stack.top().symbolTable.getSymbol(name)) {
        return symbol;
    }
    if (location) {
        errHandler.handleError(E10006, location, {name});
    }
    return nullptr;
}

void SemaAnalyser::addLocalSymbol(const string&name, const LgsSymbol& newSymbol) {
    if (const auto symbol = getSymbol(name, nullptr)) {
        return errHandler.handleError(E10011, newSymbol.location, {name, symbol->location->lineNumberStr()});
    }
    stack.top().symbolTable.addSymbol(name, newSymbol);
}

void SemaAnalyser::resolveFuncCall(LgsFuncCall* funcCall) {
    const auto symbol = getSymbol(funcCall->name, &funcCall->location);
    if (!symbol) return;
    if (symbol->symbolType == FUNC) {
        const auto func = symbol->func;
        if (funcCall->equals(func->funcType)) {
            funcCall->func = func;
            funcCall->type = func->funcType->rt;
        } else {
            errHandler.handleError(E10015, &funcCall->location, {funcCall->name, funcCall->prettyName(), func->prettyName()});
            return;
        }
        assert(funcCall->func);
        return;
    }

    LgsType* symbolType = nullptr;
    if (symbol->symbolType == VAR_DEC) {
        funcCall->callback = new LgsSymbol(symbol->varDec);
        symbolType = symbol->varDec->type;
    } else if (symbol->symbolType == PARAM) {
        funcCall->callback = new LgsSymbol(symbol->param);
        symbolType = symbol->param->type;
    }

    const auto anonymousFuncType = symbolType->asFuncType();
    if (anonymousFuncType) {
        visitAnonymousFunc(funcCall, anonymousFuncType);
    } else {
        errHandler.handleError(E10046, &funcCall->location, {funcCall->name});
    }
}

bool SemaAnalyser::resolveMethodCall(LgsFuncCall* methodCall, const LgsType* parentType) {
    auto name = methodCall->name;
    const auto method = parentType->getMethod(name);
    if (!method) {
        errHandler.handleError(E10013, &methodCall->location, {name, parentType->prettyName()});
        return true;
    }
    if (methodCall->equals(method->funcType)) {
        methodCall->func = method;
        methodCall->type = method->funcType->rt;
    } else {
        errHandler.handleError(E10034, &methodCall->location, {parentType->prettyName(), name, method->prettyName(), method->funcType->prettyName()});
        return true;
    }
    return false;
}

LgsType* SemaAnalyser::resolveType(LgsType* type) {
    if (const auto iter = type->asIterable()) {
        resolveIterable(iter);
        return iter;
    }
    if (const auto pair = type->asPair()) {
        pair->key = resolveType(pair->key);
        pair->value = resolveType(pair->value);
        return pair;
    }
    if (!type->isUnknown()) return type;
    auto typeName = type->prettyName();
    auto symbol = globals.getSymbol(typeName);
    if (!symbol) {
        symbol = file->symbolTable.getSymbol(typeName);
    }
    if (!symbol) {
        errHandler.handleError(E10006, &type->location, {typeName});
        return nullptr;
    }

    LgsType* newType = nullptr;
    switch (symbol->symbolType) {
    case ENUM_FIELD:
        symbol->enumField->type->isNullable = true;
        newType = symbol->enumField->type;
        break;
    case FUNC:
        newType = symbol->func->funcType;
        break;
    case OBJECT:
        symbol->object->isNullable = true;
        newType = symbol->object;
        break;
    case INTERFACE:
        symbol->interface->isNullable = true;
        newType = symbol->interface;
        break;
    case GROUP:
        symbol->group->isNullable = true;
        newType = symbol->group;
        break;
    case ENUM:
        symbol->lgsEnum->isNullable = true;
        newType = symbol->lgsEnum;
        break;
    case VAR_DEC:
    case PARAM:
    case FIELD:
    case UNKNOWN:
        break;
    }
    assert(newType);
    freeType(type);
    return newType;
}

void SemaAnalyser::resolveIterable(LgsIterable* iterable) {
    iterable->baseType = resolveType(iterable->baseType);
    visitExpr(iterable->sizeExpr);
    if (iterable->isStatic) {
        const auto exprConstNumber = iterable->sizeExpr->getConstInt();
        if (exprConstNumber <= 0) {
            return errHandler.handleError(E10048, &iterable->location, {iterable->prettyName()});
        }
        iterable->iterLen = exprConstNumber;
    }
}

void SemaAnalyser::resolveObjTypes(LgsObject* obj) {
    for (const auto& [_, field] : obj->fields) {
        field->type = resolveType(field->type);
        field->parentName = &obj->name;
    }
    for (const auto& [_, method] : obj->methods) {
        resolveFuncTypes(method->funcType);
    }
    for (int i = 0; i < obj->interfaces.size(); ++i) {
        obj->interfaces[i] = resolveType(obj->interfaces[i]);
    }
}

void SemaAnalyser::resolveFuncTypes(LgsFuncType* funcType) {
    for (int i = 0; i < funcType->params.size(); ++i) {
        funcType->params[i].type = resolveType(funcType->params[i].type);
    }
    funcType->rt = resolveType(funcType->rt);
    if (!funcType->rt->isVoid && funcType->rt->getSizeBytes() > PARAM_SWAP_SIZE_THRESHOLD) {
        funcType->isBigType = true;
    }
}

void SemaAnalyser::resolveGroupTypes(LgsGroup* group) {
    for (int i = 0; i < group->types.size(); ++i) {
        group->types[i] = resolveType(group->types[i]);
    }
}

void SemaAnalyser::reprocessFuncs(const vector<LgsFile*>& files) {
    for (const auto& file : files) {
        SemaAnalyser semaAnalyser(file);
        if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
            for (const auto& obj : mainFile->objects) {
                for (const auto& [_, method] : obj->methods) {
                    method->swapReturnIfNeeded();
                }
            }
            for (const auto [_, func] : mainFile->funcs) {
                func->swapReturnIfNeeded();
            }
        } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
            const auto obj = objFile->obj;
            for (const auto& [_, method] : obj->methods) {
                method->swapReturnIfNeeded();
            }
        } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
            for (const auto& [_, method] : interfaceFile->interface->methods) {
                method->swapReturnIfNeeded();
            }
        }
    }
}

string SemaAnalyser::getFuncsAsStr(const vector<LgsFunc*>& funcs) const {
    stringstream str;
    for (const auto& func : funcs) {
        str << "\n\t     - " << func->funcType->prettyName();
    }
    return str.str();
}
