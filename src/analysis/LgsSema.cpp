#include "analysis/LgsSema.h"

#include "builtins/LgsTest.h"
#include "funcs/LgsCoroutine.h"
#include "data/LgsErrors.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsObjectFile.h"
#include "stmts/LgsField.h"
#include "stmts/LgsReturn.h"
#include "exprs/LgsArrayExpr.h"
#include "exprs/LgsIterIndex.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsInstance.h"
#include "exprs/LgsSelection.h"
#include "exprs/LgsVariable.h"
#include "exprs/LgsBinaryExpr.h"
#include "exprs/LgsCast.h"
#include "types/LgsEnum.h"
#include "exprs/LgsHashMap.h"
#include "exprs/LgsJson.h"
#include "exprs/LgsPostfixExpr.h"
#include "exprs/LgsPrefixExpr.h"
#include "exprs/LgsTypeExpr.h"
#include "exprs/LgsVectorExpr.h"
#include "exprs/constants/LgsStrConst.h"
#include "files/LgsMainFile.h"
#include "files/LgsTestFile.h"
#include "funcs/LgsMainFunc.h"
#include "utils/LgsErrHandler.h"
#include "loops/LgsInfiniteLoop.h"
#include "loops/LgsWhileLoop.h"
#include "stmts/LgsBreak.h"
#include "stmts/LgsContinue.h"
#include "stmts/LgsDeferStmt.h"
#include "stmts/LgsVarDec.h"
#include "types/iterables/LgsDArray.h"
#include "types/LgsGroup.h"
#include "types/LgsInterface.h"
#include "types/LgsNullable.h"
#include "loops/LgsForeachLoop.h"
#include "loops/LgsForLoop.h"
#include "loops/LgsLoopMetaVar.h"
#include "loops/LgsRangeLoop.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsIOStmt.h"
#include "stmts/LgsIfStmt.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsUInt.h"

void LgsSema::analyse() {
    if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
        visitMainFile(mainFile);
    } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
        visitObject(objFile->obj);
    } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
        visitInterface(interfaceFile->interface);
    } else if (const auto testFile = dynamic_cast<LgsTestFile*>(file)) {
        visitTestFile(testFile);
    } else {
        assert(0);
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
    for (const auto& field : obj->fields) {
        visitField(field);
    }
    for (const auto& [_, method] : obj->methods) {
        visitFunc(method);
    }
    for (const auto& ioPair : obj->ioPairs) {
        visitIOPair(ioPair, obj);
    }
    validateObjImplements(obj, obj->interfaces);
    validateTypeDuplicates(obj);
}

void LgsSema::visitInterface(LgsInterface* interface) {
    for (const auto& field : interface->fields) {
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

void LgsSema::visitTestFile(const LgsTestFile* testFile) {
    const auto parentPath = testFile->path.parent_path();
    if (!is_directory(parentPath) || parentPath.filename() != "tests") {
        return errHandler.addError(E10079, &file->location, {file->name});
    }
    for (const auto& func : testFile->funcs) {
        visitFunc(func);
    }
    for (const auto& test : testFile->tests) {
        visitFunc(test);
    }
}

void LgsSema::visitField(LgsField* field) {
    if (field->expr) {
        visitExpr(field->expr);
        validateExprType(field->expr, field->type);
    }
    if (field->expr && field->expr->asFunc()) {
        errHandler.addError(E10013, &field->location, {field->name});
    }
    if (!field->type->isHeapAlloc && field->isOwner) {
        errHandler.addWarning(W10001, &field->location, {field->type->getName()});
        field->isOwner = false;
    }
}

void LgsSema::visitFunc(LgsFunc* func) {
    stack.enterScope(func);
    auto defaultParamsStarted = false;
    for (auto& param : func->funcType->params) {
        visitParam(&param);
        if (defaultParamsStarted && !param.expr) {
            errHandler.addError(E10028, &param.location);
            break;
        }
        defaultParamsStarted = !!param.expr;
    }
    visitStmtsBlock(func->stmtsBlock);
    if (func->funcType->isVariadic && func->funcType->hasDefaults()) {
        errHandler.addError(E10043, &func->location);
    }
    if (!validateBlockControlFlow(func->stmtsBlock, func)) {
        errHandler.addError(E10055, &func->location, {func->getName()});
    }
    // for (const auto& orphan : func->orphans) {
    //     errHandler.addError(E10077, &orphan->location, {orphan->pname()});
    // }
    stack.exitScope();
}

void LgsSema::visitLambda(LgsFunc* lambda) {
    if (lambda->stmtsBlock->stmts.size() == 1) {
        const auto expr = lambda->stmtsBlock->stmts.front()->asExpr();
        if (expr) {
            lambda->stmtsBlock->stmts[0] = new LgsReturn(expr);
        }
    }
    visitFunc(lambda);
}

void LgsSema::visitParam(LgsParam* param) {
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
    assert(param->type);
}

void LgsSema::visitIOPair(LgsIOPair* ioPair, LgsObject* obj) {
    ioPair->openFunc = obj->getMethod(ioPair->openFuncName);
    ioPair->closeFunc = obj->getMethod(ioPair->closeFuncName);
    if (!ioPair->openFunc) {
        errHandler.addError(E10005, &ioPair->openFunc->location, {ioPair->openFuncName, obj->pname()});
    }
    if (!ioPair->closeFunc) {
        errHandler.addError(E10005, &ioPair->closeFunc->location, {ioPair->closeFuncName, obj->pname()});
    }
}

void LgsSema::visitStmt(LgsStmt* stmt) {
    if (const auto pattern = stmt->asPattern()) visitPatternMatching(pattern);
    else if (const auto ifStmt = stmt->asIfStmt()) visitIfStmt(ifStmt);
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
    else if (const auto ioStmt = stmt->asIOStmt()) visitIOStmt(ioStmt);
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
    if (const auto iter = varDec->type->asIterable()) {
        visitExpr(iter->sizeExpr);
    }
    if (varDec->expr && varDec->type) {
        if (varDec->isOwner) {
            varDec->expr->owner = varDec;
        }
        varDec->type = typeResolver.resolveType(varDec->type, file);
        varDec->expr->completeType(varDec->type);
        visitExpr(varDec->expr);
        validateExprType(varDec->expr, varDec->type);
        freeType(varDec->expr->type);
        varDec->expr->type = varDec->type;
    } else if (varDec->expr) {
        visitExpr(varDec->expr);
        if (varDec->isOwner) {
            varDec->expr->owner = varDec;
        }
        varDec->type = varDec->expr->type;
        validateExprType(varDec->expr, varDec->type);
    } else {
        varDec->type = typeResolver.resolveType(varDec->type, file);
        if (!varDec->type) return;
        varDec->expr = varDec->type->getZeroValue();
        varDec->expr->location = varDec->location;
        visitExpr(varDec->expr);
        if (varDec->isOwner) {
            varDec->expr->owner = varDec;
        }
    }
    if (varDec->type && !varDec->type->isHeapAlloc && varDec->isOwner) {
        errHandler.addWarning(W10001, &varDec->location, {varDec->type->getName()});
        varDec->isOwner = false;
    }
    addLocalSymbol(LgsSymbol(varDec));
    addHeapExpr(varDec->expr);
}

bool LgsSema::canAssignTo(LgsExpr* lValue, LgsExpr* rValue) {
    if (lValue->asIterIndex()) {
        return true;
    }
    if (const auto selection = lValue->asSelection()) {
        const auto lastExprParent = selection->lastExprParent();
        if (const auto obj = lastExprParent->type->asObject()) {
            if (!obj->singleton && lastExprParent->asTypeExpr()) {
                errHandler.addError(E10089, &selection->location, {lastExprParent->getName(), selection->lastExpr()->getName()});
                return false;
            }
        }
    }
    if (lValue->asVariable()) {
        return true;
    }
    return false;
}

void LgsSema::visitAssignment(const LgsAssignment* assignment) {
    const auto lValue = assignment->lValue;
    const auto rValue = assignment->rValue;
    visitExpr(lValue);
    visitExpr(rValue);
    const auto lType = lValue->type;
    const auto rType = rValue->type;
    if (!lType || !rType) return;
    if (!lValue->isMutable) {
        return errHandler.addError(E10051, &lValue->location, {lValue->getName()});
    }
    if (!canAssignTo(lValue, rValue)) return;
    if (!lType->canCastTo(rType)) {
        return errHandler.addError(E10012, &lValue->location, {lValue->getName(), lType->pname(), assignment->getAssignTypeStr(), rValue->getName()});
    }
}

void LgsSema::visitIfStmt(LgsIfStmt* ifStmt) {
    stack.enterScope(ifStmt);
    visitExpr(ifStmt->ifCond);
    visitStmtsBlock(ifStmt->ifBlock);
    stack.exitScope();
    for (const auto& [expr, block] : ifStmt->elseIfs) {
        stack.enterScope(ifStmt);
        visitExpr(expr);
        visitStmtsBlock(block);
        stack.exitScope();
    }
    if (ifStmt->elseBlock) {
        stack.enterScope(ifStmt);
        visitStmtsBlock(ifStmt->elseBlock);
        stack.exitScope();
    }
}

void LgsSema::visitPatternMatching(LgsIfStmt* pm) {
    if (!pm->ifCond) {
        return visitBoolPatternMatching(pm);
    }
    const auto baseExpr = pm->ifCond;
    stack.enterScope(pm);
    visitExpr(baseExpr);
    const auto baseExprType = baseExpr->type;
    // Allows local enum fields to not have a qualifier inside the block
    if (baseExprType->asEnum()) {
        for (const auto& field : baseExprType->fields) {
            addLocalSymbol(LgsSymbol(field));
        }
    }
    for (const auto [expr, block] : pm->elseIfs) {
        stack.enterScope(pm);
        visitExpr(expr);
        visitStmtsBlock(block);
        if (expr->type->isUnknown()) continue;
        if (!baseExprType->canCastTo(expr->type)) {
            return errHandler.addError(E10014, &expr->location, {expr->type->pname(), baseExprType->pname()});
        }
        stack.exitScope();
    }
    if (pm->elseBlock) {
        stack.enterScope(pm);
        visitStmtsBlock(pm->elseBlock);
        stack.exitScope();
    }
    stack.exitScope();
}

void LgsSema::visitBoolPatternMatching(LgsIfStmt* pm) {
    for (const auto [expr, block] : pm->elseIfs) {
        stack.enterScope(pm);
        visitExpr(expr);
        if (!expr->type->asBool()) {
            return errHandler.addError(E10057, &expr->location, {expr->getName()});
        }
        visitStmtsBlock(block);
        stack.exitScope();
    }
    if (pm->elseBlock) {
        stack.enterScope(pm);
        visitStmtsBlock(pm->elseBlock);
        stack.exitScope();
    }
}

void LgsSema::visitWhileLoop(const LgsWhileLoop* whileLoop) {
    visitExpr(whileLoop->condExpr);
    const auto condType = whileLoop->condExpr->type;
    if (!condType->asBool()) {
        return errHandler.addError(E10066, &whileLoop->location, {whileLoop->condExpr->getName(), condType->pname()});
    }
    visitStmtsBlock(whileLoop->stmtsBlock);
}

void LgsSema::visitLoopStmt(LgsForLoop* loopStmt) {
    stack.enterScope(loopStmt);
    if (const auto rangeLoop = loopStmt->asRangeLoop()) {
        visitRangeLoop(rangeLoop);
    } else if (const auto foreachLoop = loopStmt->asForeachLoop()) {
        visitForeachLoop(foreachLoop);
    } else if (const auto infiniteLoop = loopStmt->asInfiniteLoop()) {
        visitInfiniteLoop(infiniteLoop);
    } else if (const auto whileLoop = loopStmt->asWhileLoop()) {
        visitWhileLoop(whileLoop);
    } else {
        assert(0);
    }
    stack.exitScope();
}

void LgsSema::visitRangeLoop(LgsRangeLoop* rangeLoop) {
    const auto startRange = rangeLoop->startRange;
    const auto endRange = rangeLoop->endRange;
    assert(endRange);
    visitExpr(startRange);
    visitExpr(endRange);
    if (endRange->type && !endRange->type->isNumber()) {
        errHandler.addError(E10082, &endRange->location, {endRange->getName(), endRange->type->pname()});
    }

    if (startRange) {
        if (startRange->type && !startRange->type->isNumber()) {
            errHandler.addError(E10082, &startRange->location, {startRange->getName(), startRange->type->pname()});
        }
        if (!startRange->type->equals(endRange->type)) {
            errHandler.addError(E10081, &startRange->location, {startRange->getName(), endRange->getName()});
        }
    } else {
        rangeLoop->startRange = endRange->type->getZeroValue();
    }

    // Range loop can have only one var
    if (!rangeLoop->loopVars.empty()) {
        rangeLoop->loopVars.front()->type = endRange->type;
        addLocalSymbol(LgsSymbol(rangeLoop->loopVars.front()));
    }
    visitStmtsBlock(rangeLoop->stmtsBlock);
}

void LgsSema::visitForeachLoop(LgsForeachLoop* foreachLoop) {
    const auto iterExpr = foreachLoop->iterExpr;
    visitExpr(iterExpr);
    const auto iterable = iterExpr->type->asIterable();
    if (!iterable) {
        if (iterExpr->type) {
            errHandler.addError(E10002, &iterExpr->location, {iterExpr->getName(), iterExpr->type->pname()});
        }
        return;
    }

    const bool unpacked = iterable->unpackLoopVars(foreachLoop);
    if (!unpacked) {
        errHandler.addError(E10041, &foreachLoop->iterExpr->location, {foreachLoop->iterExpr->getName(), foreachLoop->iterExpr->type->pname(), std::to_string(foreachLoop->loopVars.size())});
        return;
    }

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
    } else if (retExpr && retExpr->type && !rt->canCastTo(retExpr->type)) {
        errHandler.addError(E10004, &returnStmt->location, {funcType->name, rt->pname(), retExpr->type->pname()});
    }
}

void LgsSema::visitIOStmt(const LgsIOStmt* ioStmt) {
    visitVarDec(ioStmt->varDec);
    const auto expr = ioStmt->varDec->expr;
    const auto funcCall = expr->asFuncCall() ? expr->asFuncCall() : expr->asSelection()->asMethodCall();
    if (!funcCall->func->funcType->isInIOPair) {
        errHandler.addError(E10084, &funcCall->location, {funcCall->getName()});
    }
    visitStmtsBlock(ioStmt->stmtsBlock);
}

void LgsSema::visitContinueStmt(const LgsContinue* continueStmt) {
    if (!stack.currentLoop()) {
        errHandler.addError(E10038, &continueStmt->location);
    }
}

void LgsSema::visitBreakStmt(const LgsBreak* breakStmt) {
    if (breakStmt->isBreakIf) {
        if (!stack.currentIfStmt()) errHandler.addError(E10071, &breakStmt->location);
    } else if (!stack.currentLoop() && breakStmt->tag == "") {
        errHandler.addError(E10017, &breakStmt->location);
    }
}

void LgsSema::visitDeferStmt(const LgsDeferStmt* deferStmt) {
    if (deferStmt->funcCall) visitFuncCall(deferStmt->funcCall);
    else visitSelection(deferStmt->selection);
    const auto deferType = deferStmt->funcCall ? deferStmt->funcCall->type : deferStmt->selection->type;
    assert(deferType);
    stack.currentFunc()->hasDefers = true;
}

void LgsSema::visitExpr(LgsExpr* expr) {
    if (!expr) return;
    if (const auto iter = expr->type->asIterable()) {
        visitExpr(iter->sizeExpr);
    }
    if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
    } else {
        if (const auto lambda = expr->asFunc()) visitLambda(lambda);
        else if (const auto instance = expr->asInstance()) visitInstance(instance);
        else if (const auto funcCall = expr->asFuncCall()) visitFuncCall(funcCall);
        else if (const auto strConst = expr->asStrConst()) visitStrConst(strConst);
        else if (const auto selection = expr->asSelection()) visitSelection(selection);
        else if (const auto arrayExpr = expr->asArrayExpr()) visitArrayExpr(arrayExpr);
        else if (const auto hashMap = expr->asHashMap()) visitHashMap(hashMap);
        else if (const auto iterIndex = expr->asIterIndex()) visitIterIndex(iterIndex);
        else if (const auto variable = expr->asVariable()) visitVariable(variable);
        else if (const auto postfixExpr = expr->asPostfixExpr()) visitPostfixExpr(postfixExpr);
        else if (const auto prefixExpr = expr->asPrefixExpr()) visitPrefixExpr(prefixExpr);
        else if (const auto forVar = expr->asLoopMetaVar()) visitLoopMetaVar(forVar);
        else if (const auto vecExpr = expr->asVectorExpr()) visitVectorExpr(vecExpr);
        else if (const auto castExpr = expr->asCast()) visitCast(castExpr);
        else if (const auto json = expr->asJson()) visitJson(json);
    }
}

void LgsSema::visitBinaryExpr(LgsBinaryExpr* binaryExpr) {
    const auto l = binaryExpr->left;
    const auto r = binaryExpr->right;
    visitExpr(l);
    visitExpr(r);
    const auto ltype = l->type;
    const auto rtype = r->type;
    LgsType* type = nullptr;
    if (binaryExpr->op == IN) {
        type = rtype->applyOp(ltype, binaryExpr->op);
    } else {
        type = ltype->applyOp(rtype, binaryExpr->op);
    }
    if (!type) {
        return errHandler.addError(E10076, &l->location, {getOpAsText(binaryExpr->op), ltype->pname(), rtype->pname()});
    }
    binaryExpr->setType(type);
}

void LgsSema::visitCast(LgsCast* lgsCast) {
    const auto fromValue = lgsCast->fromValue;
    if (const auto unaryExpr = dynamic_cast<LgsExpr*>(fromValue)) {
        visitExpr(unaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(fromValue)) {
        visitBinaryExpr(binaryExpr);
    }
    lgsCast->toType = typeResolver.resolveType(lgsCast->toType, file);
}

void LgsSema::visitArrayExpr(LgsArrayExpr* array) {
    for (const auto element : array->initialElements) {
        visitExpr(element);
    }
    if (array->type->asDArray() || array->type->asSet()) {
        visitDynamicArray(array);
    } else {
        visitStaticArray(array);
    }
}

void LgsSema::visitStaticArray(LgsArrayExpr* arrayExpr) {
    const auto& initialElements = arrayExpr->initialElements;
    const auto arr = arrayExpr->type->asSArray();
    if (initialElements.empty() && !arr->baseType) {
        return errHandler.addError(E10049, &arrayExpr->location, {arrayExpr->getName()});
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
        return errHandler.addError(E10049, &array->location, {array->getName()});
    }

    LgsType* baseType = nullptr;
    if (dArr->baseType) {
        baseType = dArr->baseType;
    } else if (const auto innerArr = array->initialElements.front()->asArrayExpr()) {
        baseType = innerArr->type;
    } else {
        baseType = array->initialElements.front()->type;
    }
    dArr->baseType = baseType;
}

void LgsSema::visitHashMap(LgsHashMap* hashMap) {
    for (const auto element : hashMap->initialElements) {
        visitExpr(element->key);
        visitExpr(element->value);
    }
    if (hashMap->type) return;
    if (hashMap->initialElements.empty()) {
        return errHandler.addError(E10049, &hashMap->location, {LgsMap::name});
    }
    const auto firstElement = hashMap->initialElements.front();
    hashMap->type = new LgsMap(firstElement->key->type, firstElement->value->type);
}

void LgsSema::visitVectorExpr(const LgsVectorExpr* vectorExpr) {
    auto sumDim = 0;
    for (const auto arg : vectorExpr->args) {
        visitExpr(arg);
        if (arg->type->isNumber()) {
            sumDim++;
        } else if (const auto otherVec = arg->type->asVec()) {
            sumDim += otherVec->dim;
        } else {
            errHandler.addError(E10073, &vectorExpr->location, {arg->type->pname()});
            break;
        }
    }
    if (sumDim > vectorExpr->vecType->dim) {
        errHandler.addError(E10074, &vectorExpr->location, {std::to_string(vectorExpr->vecType->dim), std::to_string(sumDim)});
    }
}

void LgsSema::visitVariable(LgsVariable* variable) {
    const auto symbol = getSymbol(variable->name, &variable->location);
    if (!symbol) return;
    variable->ref.symbolType = symbol->symbolType;
    switch (symbol->symbolType) {
    case VAR_DEC: {
        variable->ref.varDec = symbol->varDec;
        variable->isMutable = !symbol->varDec->isConst;
        variable->setType(symbol->varDec->type);
        if (symbol->varDec->isOwner) {
            variable->owner = symbol->varDec;
        }
        break;
    }
    case PARAM: {
        variable->ref.param = symbol->param;
        variable->setType(symbol->param->type);
        break;
    }
    case ENUM: {
        variable->ref.enum_ = symbol->enum_;
        variable->setType(symbol->enum_);
        break;
    }
    case FUNC: {
        variable->ref.func = symbol->func;
        variable->setType(symbol->func->funcType);
        break;
    }
    case OBJECT: {
        variable->ref.object = symbol->object;
        variable->setType(symbol->object);
        break;
    }
    case FIELD: {
        variable->ref.field = symbol->field;
        variable->setType(symbol->field->type);
        variable->isMutable = !symbol->field->isConst;
        if (symbol->field->isOwner) {
            variable->owner = symbol->field;
        }
        break;
    }
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
    selection->owner = selection->lastExpr()->owner;
}

void LgsSema::visitFirstSelection(LgsExpr* firstExpr) {
    if (const auto variable = firstExpr->asVariable()) {
        visitVariable(variable);
    } else if (const auto funcCall = firstExpr->asFuncCall()) {
        visitFuncCall(funcCall);
    } else if (const auto iterIndex = firstExpr->asIterIndex()) {
        visitIterIndex(iterIndex);
    } else if (const auto typeExpr = firstExpr->asTypeExpr()) {
        visitTypeExpr(typeExpr);
    } else {
        assert(0);
    }
}

void LgsSema::visitInnerSelections(const LgsSelection* selection) {
    const auto exprs = selection->exprs;
    for (int i = 0; i < exprs.size() - 1; ++i) {
        const auto parentExpr = exprs[i];
        const auto childExpr = exprs[i + 1];
        if (const auto var = childExpr->asVariable()) {
            visitFieldSelection(var, parentExpr->type);
        } else if (const auto methodCall = childExpr->asFuncCall()) {
            visitMethodCall(methodCall, parentExpr);
        } else if (const auto iterIndex = childExpr->asIterIndex()) {
            visitIterIndexSelection(iterIndex, parentExpr->type);
        } else {
            assert(0);
        }
        if (!childExpr->type || childExpr->type->isUnknown()) {
            return;
        }
    }
}

void LgsSema::visitFieldSelection(LgsVariable* child, LgsType* parentType) {
    if (!parentType) return;
    if (parentType->asVec() && !validateVecElements(child, parentType->asVec())) return;
    auto childName = child->name;
    if (const auto field = parentType->getField(childName)) {
        child->setType(field->type);
        child->isMutable = !field->isConst;
        child->ref = LgsSymbol(field);
        if (field->isOwner && field->type->isHeapAlloc) {
            child->owner = field;
        }
        if (const auto parentAsObj = parentType->asObject()) {
            validateFieldVisibility(field, parentAsObj);
        }
    } else if (const auto method = parentType->getMethod(childName)) {
        child->setType(method->type);
        child->isMutable = false;
        child->ref = LgsSymbol(method);
        if (const auto parentAsObj = parentType->asObject()) {
            validateMethodVisibility(method, parentAsObj, method->location);
        }
    } else {
        errHandler.addError(E10005, &child->location, {childName, parentType->pname()});
    }
}

void LgsSema::visitIterIndexSelection(LgsIterIndex* child, LgsType* parentType) {
    const auto baseExpr = child->baseExpr->asVariable();
    const auto field = parentType->getField(baseExpr->name);
    if (!field) {
        return errHandler.addError(E10005, &child->location, {baseExpr->name, parentType->pname()});
    }
    if (!field->type->asIterable()) {
        return errHandler.addError(E10002, &child->location, {baseExpr->name});
    }
    child->type = field->type->asIterable()->baseType;
    child->baseExpr->type = field->type;
    baseExpr->ref = LgsSymbol(field);
    visitIndex(child);
}

void LgsSema::visitMethodCall(LgsFuncCall* methodCall, LgsExpr* parent) {
    auto name = methodCall->name;
    const auto method = parent->type->getMethod(name);
    if (!method) {
        errHandler.addError(E10005, &methodCall->location, {name, parent->type->pname()});
        return;
    }
    if (parent->asTypeExpr() && method->funcType->isMethod) {
        errHandler.addError(E10083, &methodCall->location, {method->funcType->pname()});
    } else if (method->funcType->isMethod) {
        methodCall->args.insert(methodCall->args.begin(), parent);
    }

    for (size_t i = method->funcType->isMethod; i < method->funcType->params.size(); ++i) {
        const auto arg = methodCall->args[i];
        const auto& param = method->funcType->params[i];
        arg->completeType(param.type);
        visitExpr(arg);
    }
    if (methodCall->equals(method->funcType)) {
        methodCall->func = method;
        methodCall->setType(method->funcType->rt);
    } else {
        errHandler.addError(E10034, &methodCall->location, {parent->type->pname(), name, methodCall->getName(), method->getName()});
        return;
    }

    if (!validateMethodVisibility(method, parent->type->asObject(), methodCall->location)) return;
    if (stack.currentFunc()->isTest && parent->type->getName() == LgsTest::name && methodCall->name == "mock") {
        const auto pair = std::make_pair(methodCall->args[0], methodCall->args[1]);
        stack.currentFunc()->mocks.push_back(pair);
    }
}

void LgsSema::visitFuncCall(LgsFuncCall* funcCall) {
    const auto symbol = getSymbol(funcCall->name, &funcCall->location);
    if (!symbol) return;
    const auto ft = symbol->getType()->asFuncType();
    if (!ft) {
        return errHandler.addError(E10046, &funcCall->location, {funcCall->name});
    }
    for (size_t i = ft->isMethod; i < ft->params.size(); ++i) {
        const auto arg = funcCall->args[i];
        const auto& param = ft->params[i];
        arg->completeType(param.type);
        visitExpr(arg);
    }
    if (funcCall->equals(ft)) {
        if (symbol->symbolType == FUNC) {
            const auto func = symbol->func;
            funcCall->func = func;
            funcCall->setType(func->funcType->rt);
        } else {
            funcCall->ref = *symbol;
            funcCall->setType(ft->rt);
        }
    } else {
        errHandler.addError(E10015, &funcCall->location, {funcCall->name, funcCall->getName(), ft->pname()});
    }
}

void LgsSema::visitPrefixExpr(LgsPrefixExpr* prefixExpr) {
    const auto baseExpr = prefixExpr->expr;
    visitExpr(baseExpr);
    switch (prefixExpr->op) {
    case MINUS_PREFIX: {
        if (!baseExpr->type->isNumber()) {
            errHandler.addError(E10090, &prefixExpr->location, {"-", baseExpr->type->pname()});
            return;
        }
        prefixExpr->setType(baseExpr->type);
        break;
    }
    case NOT_PREFIX: {
        if (!baseExpr->type->asBool()) {
            errHandler.addError(E10091, &prefixExpr->location, {baseExpr->type->pname()});
            return;
        }
        prefixExpr->setType(baseExpr->type);
        break;
    }
    case SQRT_PREFIX: {
        if (!baseExpr->type->isNumber()) {
            errHandler.addError(E10090, &prefixExpr->location, {"_/", baseExpr->type->pname()});
            return;
        }
        prefixExpr->setType(&LGS_DOUBLE);
        break;
    }
    }
}

void LgsSema::visitPostfixExpr(LgsPostfixExpr* postfixExpr) {
    const auto baseExpr = postfixExpr->expr;
    visitExpr(baseExpr);
    const auto type = baseExpr->type;
    if (!type->isNumber()) {
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

void LgsSema::visitTypeExpr(LgsTypeExpr* typeExpr) {
    typeExpr->type = typeResolver.resolveType(typeExpr->type, file);
}

void LgsSema::visitJson(const LgsJson* json) {
    if (const auto arr = json->arr) {
        visitArrayExpr(arr);
    } else if (const auto strConst = json->strConst) {
        visitStrConst(strConst);
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
    std::unordered_set<std::string> visited;
    for (const auto& [argName, arg] : instance->args) {
        visited.insert(argName);
        const auto field = instance->obj->getField(arg->name);
        if (!field) {
            errHandler.addError(E10005, &arg->location, {arg->name, objName});
            continue;
        }
        if (!validateFieldVisibility(field, instance->obj)) continue;
        visitExpr(arg->expr);
        validateExprType(arg->expr, field->type);
        if (field->isOwner && field->type->isHeapAlloc) {
            field->expr->owner = field;
        }
    }

    // Missing required fields
    for (const auto& field : instance->obj->fields) {
        if (field->isConst && instance->args.find(field->name) == instance->args.end()) {
            errHandler.addError(E10029, &field->location, {field->name});
        }
    }
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

void LgsSema::visitIterIndex(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    visitExpr(baseExpr);
    iterIndex->isMutable = baseExpr->isMutable;
    if (!baseExpr->type) return;
    const auto iterable = baseExpr->type->asIterable();
    if (!iterable) {
        const auto typeName = baseExpr->type ? baseExpr->type->pname() : LGS_UNKNOWN_TYPE;
        return errHandler.addError(E10002, &iterIndex->location, {baseExpr->getName(), typeName});
    }
    visitIndex(iterIndex);
}

void LgsSema::visitIndex(LgsIterIndex* iterIndex) {
    const auto iterable = iterIndex->baseExpr->type->asIterable();
    visitExpr(iterIndex->index.from);
    const auto exprTo = iterIndex->index.to;
    if (exprTo) {
        visitExpr(exprTo);
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
    const auto exprFrom = iterIndex->index.from;
    const auto exprTo = iterIndex->index.to;
    const auto iterable = baseExpr->type->asIterable();
    if (!baseExpr->type->isSliceable()) {
        return errHandler.addError(E10042, &iterIndex->location, {iterIndex->getName(), baseExpr->type->pname()});
    }
    if (!iterable->getIndexType()->canCastTo(exprFrom->type)) {
        return errHandler.addError(E10036, &iterIndex->location, {iterIndex->getName(), exprFrom->type->pname()});
    }
    if (!iterable->getIndexType()->canCastTo(exprTo->type)) {
        return errHandler.addError(E10036, &iterIndex->location, {iterIndex->getName(), exprTo->type->pname()});
    }
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

void LgsSema::visitLoopMetaVar(LgsLoopMetaVar* metaVar) {
    const auto loop = stack.currentLoop();
    if (!loop) {
        return errHandler.addError(E10060, &metaVar->location);
    }
    metaVar->forLoop = loop;
    const auto name = metaVar->getName();
    if (loop->asWhileLoop()) {
        return errHandler.addError(E10061, &metaVar->location, {name});
    }
    if (loop->asInfiniteLoop()) {
        return errHandler.addError(E10061, &metaVar->location, {name});
    }

    if (metaVar->varType == FOR_PREV || metaVar->varType == FOR_NEXT) {
        if (loop->asRangeLoop()) {
            metaVar->setType(&LGS_UINT);
        } else if (const auto foreachLoop = loop->asForeachLoop()) {
            const auto iterable = foreachLoop->iterExpr->type->asIterable();
            if (!iterable) return;
            metaVar->setType(iterable->baseType);
        }
    }

    if (loop->metaVars.find(metaVar->varType) == loop->metaVars.end()) {
        loop->metaVars[metaVar->varType] = metaVar;
    }
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

void LgsSema::addHeapExpr(LgsExpr* expr) {
    if (!expr->type) return;
    if (!expr->type->isHeapAlloc) return;
    const auto currentFunc = stack.currentFunc();
    if (expr->owner) {
        currentFunc->owners.push_back(expr);
    } else {
        currentFunc->orphans.push_back(expr);
    }
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

void LgsSema::validateExprType(const LgsExpr* expr, LgsType* type) {
    if (expr->isNull) {
        // null must have a type
        if (!type || type->isUnknown()) {
            return errHandler.addError(E10024, &expr->location);
        }
        // type must be nullable
        if (!type->asNullable()) {
            errHandler.addError(E10023, &type->location, {type->pname(), type->pname()});
        }
        return;
    }
    if (!type || !expr->type || type->isUnknown() || expr->type->isUnknown()) return;
    if (!type->canCastTo(expr->type)) {
        errHandler.addError(E10001, &expr->location, {type->pname(), expr->type->pname()});
    }
}

void LgsSema::validateObjInterface(LgsObject* obj, LgsInterface* interface) {
    // Fields
    std::vector<LgsField*> missingFields;
    for (const auto& interfaceField : interface->fields) {
        const auto objField = obj->getField(interfaceField->name);
        if (objField && objField->type->canCastTo(interfaceField->type)) {
            objField->isVirtual = true;
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
            if (objMethod != obj->methods.end() && objMethod->second->funcType->canCastTo(interfaceMethod->funcType)) {
                objMethod->second->funcType->isVirtual = true;
                continue;
            }
        }

        if (!interfaceMethod->stmtsBlock && !interfaceMethod->funcType->isOptional) {
            missingMethods.emplace_back(interfaceMethod);
        }
    }

    if (!missingMethods.empty() || !missingFields.empty()) {
        errHandler.addError(E10016, &obj->location, {obj->pname(), interface->name, getMissingImplementsStr(missingFields, missingMethods)});
    }
}

void LgsSema::validateIndex(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto exprFrom = iterIndex->index.from;
    const auto iterable = baseExpr->type->asIterable();
    if (!iterable->getIndexType()->canCastTo(exprFrom->type)) {
        return errHandler.addError(E10036, &iterIndex->location, {iterIndex->getName(), exprFrom->type->pname()});
    }
}

bool LgsSema::validateFieldVisibility(LgsField* field, const LgsObject* parent) {
    if (parent && parent->singleton) return true;
    if (!field || field->isVirtual) return false;
    if (!field->isPublic && file->id != field->location.fileID && !stack.currentFunc()->isTest) {
        if (parent) errHandler.addError(E10030, &field->location, {field->name, parent->name});
        return false;
    }
    return true;
}

bool LgsSema::validateMethodVisibility(const LgsFunc* methodCall, const LgsObject* parent, const LgsLocation& location) {
    if (parent && parent->singleton) return true;
    const auto method = methodCall;
    if (!method || method->funcType->isVirtual) return false;
    if (!method->funcType->isPublic && file->id != method->location.fileID && !stack.currentFunc()->isTest) {
        errHandler.addError(E10031, &location, {method->funcType->name, method->funcType->parentName});
        return false;
    }
    return true;
}

bool LgsSema::validateVecElements(const LgsVariable* fieldVar, LgsVec* vec) {
    const auto fieldName = fieldVar->name;
    const auto dim = vec->dim;
    if (fieldName.empty() || fieldName.size() > 4) {
        errHandler.addError(E10069, &fieldVar->location, {vec->pname()});
        return false;
    }

    const auto expectedSet = LgsVec::getSwizzleSet(fieldName[0]);
    if (expectedSet < 0) {
        errHandler.addError(E10070, &fieldVar->location, {fieldName, vec->pname()});
        return false;
    }

    for (const char c : fieldName) {
        if (LgsVec::getSwizzleSet(c) != expectedSet) {
            errHandler.addError(E10070, &fieldVar->location, {fieldName, vec->pname()});
            return false;
        }
        const auto componentIndex = LgsVec::getComponentIndex(c);
        if (componentIndex >= dim) {
            errHandler.addError(E10070, &fieldVar->location, {fieldName, vec->pname()});
            return false;
        }
    }
    return true;
}

void LgsSema::validateTypeDuplicates(LgsType* type){
    std::unordered_set<std::string> names;
    for (const auto* f : type->fields) {
        if (!f) continue;
        const auto& name = f->name;
        if (names.count(name)) {
            errHandler.addError(E10056, &type->location, {type->getName(), name});
            break;
        }
        names.insert(name);
    }
    for (const auto& [name, func] : type->methods) {
        if (names.count(name)) {
            errHandler.addError(E10056, &type->location, {type->getName(), name});
            break;
        }
        names.insert(name);
    }
}

bool LgsSema::validateBlockControlFlow(const LgsStmtsBlock* stmtBlock, const LgsFunc* func) {
    assert(func->funcType->rt);
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

LgsSymbol* LgsSema::getSymbol(const std::string& name, const LgsLocation* location) {
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
