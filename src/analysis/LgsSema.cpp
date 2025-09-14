#include "analysis/LgsSema.h"
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
#include "exprs/LgsPostfixExpr.h"
#include "exprs/LgsPrefixExpr.h"
#include "exprs/LgsTypeExpr.h"
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
#include "test/LgsTest.h"
#include "types/LgsPtr.h"
#include "types/primitives/LgsDouble.h"

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
        visitTest(test);
    }
}

void LgsSema::visitField(LgsField* field) {
    if (field->expr) {
        visitExpr(field->expr);
        matchExprToType(field->expr, field->type);
    }
    if (field->expr && field->expr->asFunc()) {
        errHandler.addError(E10013, &field->location, {field->name});
    }
    field->isOwner = field->type->isHeapAlloc;
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
    if (func->funcType->isVariadic && func->funcType->hasDefaults) {
        errHandler.addError(E10043, &func->location);
    }
    if (!validateBlockControlFlow(func->stmtsBlock, func)) {
        errHandler.addError(E10055, &func->location, {func->pname()});
    }
    for (const auto& orphan : func->orphans) {
        // errHandler.addError(E10077, &orphan->location, {orphan->pname()});
    }
    stack.exitScope();
}

void LgsSema::visitLambda(LgsFunc* lambda) {
    if (lambda->stmtsBlock->stmts.size() == 1) {
        const auto expr = lambda->stmtsBlock->stmts[0]->asExpr();
        assert(expr);
        lambda->stmtsBlock->stmts[0] = new LgsReturn(expr);
    }
    visitFunc(lambda);
    if (!lambda->funcType->isTypeComplete()) {
        return errHandler.addError(E10049, &lambda->location, {lambda->pname()});
    }
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

void LgsSema::visitTest(const LgsTest* test) {
    visitFunc(test->func);
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
    if (varDec->expr && varDec->type) {
        varDec->type = typeResolver.resolveType(varDec->type, file);
        varDec->expr->completeType(varDec->type);
        visitExpr(varDec->expr);
        matchExprToType(varDec->expr, varDec->type);
    } else if (varDec->expr) {
        visitExpr(varDec->expr);
        varDec->type = varDec->expr->type;
        matchExprToType(varDec->expr, varDec->type);
    } else {
        if (const auto iter = varDec->type->asIterable()) visitExpr(iter->sizeExpr);
        varDec->type = typeResolver.resolveType(varDec->type, file);
        varDec->expr = varDec->type->getZeroValue();
        varDec->expr->location = varDec->location;
    }
    if (varDec->isOwner && varDec->expr) {
        if (varDec->expr->owner) {
            // errHandler.addError(E10075, &varDec->expr->location, {varDec->expr->pname()});
        }
        varDec->expr->owner = varDec;
    }
    addLocalSymbol(LgsSymbol(varDec));
    addHeapExpr(varDec->expr);
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
        return errHandler.addError(E10051, &lValue->location, {lValue->pname()});
    }
    if (!lValue->canAssignTo(rType, assignment->assignmentType)) {
        return errHandler.addError(E10012, &lValue->location, {lValue->pname(), lType->pname(), assignment->getAssignTypeStr(), rValue->pname()});
    }
    if (assignment->lValue->owner && assignment->rValue->owner) {
        // errHandler.addError(E10075, &lValue->location, {rValue->pname()});
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
        if (expr->type->isUnknown) continue;
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
            return errHandler.addError(E10057, &expr->location, {expr->pname()});
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
        return errHandler.addError(E10066, &whileLoop->location, {whileLoop->condExpr->pname(), condType->pname()});
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
    if (endRange->type && !endRange->type->isNumber) {
        errHandler.addError(E10082, &endRange->location, {endRange->pname(), endRange->type->pname()});
    }

    if (startRange) {
        if (startRange->type && !startRange->type->isNumber) {
            errHandler.addError(E10082, &startRange->location, {startRange->pname(), startRange->type->pname()});
        }
        if (!startRange->type->equals(endRange->type)) {
            errHandler.addError(E10081, &startRange->location, {startRange->pname(), endRange->pname()});
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

void LgsSema::visitForeachLoop(const LgsForeachLoop* foreachLoop) {
    const auto iterExpr = foreachLoop->iterExpr;
    visitExpr(iterExpr);
    const auto iterable = iterExpr->type->asIterable();
    if (!iterable) {
        if (iterExpr->type) {
            errHandler.addError(E10002, &iterExpr->location, {iterExpr->pname(), iterExpr->type->pname()});
        }
        return;
    }
    if (!resolveForeachVars(foreachLoop, iterExpr, iterable)) return;
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
    const auto funcCall = expr->asFuncCall() ? expr->asFuncCall() : expr->asSelection()->lastExpr()->asFuncCall();
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
    }
}

void LgsSema::visitBinaryExpr(LgsBinaryExpr* binaryExpr) {
    const auto l = binaryExpr->left;
    const auto r = binaryExpr->right;
    visitExpr(l);
    visitExpr(r);
    const auto ltype = l->type;
    const auto rtype = r->type;
    const auto binaryType = ltype->applyOp(rtype, binaryExpr->op);
    if (!binaryType) {
        return errHandler.addError(E10076, &l->location, {getOpAsText(binaryExpr->op), ltype->pname(), rtype->pname()});
    }
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
        type = binaryType;
        break;
    }
    case AND:
    case OR:
    case NE:
    case EQ:
    case LT:
    case GT:
    case GE:
    case LE:
    case IN: {
        type = &LGS_BOOL;
        break;
    }
    case NOOP:
        break;
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
    if (array->type->asDArray()) {
        visitDynamicArray(array);
    } else {
        visitStaticArray(array);
    }
}

void LgsSema::visitStaticArray(LgsArrayExpr* arrayExpr) {
    const auto& initialElements = arrayExpr->initialElements;
    const auto arr = arrayExpr->type->asSArray();
    if (initialElements.empty() && !arr->baseType) {
        return errHandler.addError(E10049, &arrayExpr->location, {arrayExpr->pname()});
    }
    for (const auto element : initialElements) {
        visitExpr(element);
    }
    if (!arr->baseType) {
        arr->baseType = initialElements.front()->type;
    }
}

void LgsSema::visitDynamicArray(LgsArrayExpr* array) {
    const auto dArr = array->type->asDArray();
    if (!dArr->sizeExpr) {
        dArr->sizeExpr = new LgsIntConst(&LGS_LONG, array->initialElements.size());
    }
    if (!dArr->baseType && array->initialElements.empty()) {
        errHandler.addError(E10049, &array->location, {array->pname()});
    } else {
        LgsType* baseType = nullptr;
        const auto first = array->initialElements.front();
        if (const auto innerArr = first->asArrayExpr()) {
            baseType = innerArr->type;
        } else {
            baseType = first->type;
        }
        array->type->asIterable()->baseType = baseType;
        const auto mapFT = dArr->mapFunc->funcType->params[1].type->asFuncType();
        mapFT->params[0].type = baseType;
        mapFT->rt = baseType;
    }
}

void LgsSema::visitHashMap(LgsHashMap* hashMap) {
    const auto typePair = hashMap->type->asMap()->typePair;
    if (typePair->key && typePair->value) return;
    if (hashMap->initialElements.empty()) {
        return errHandler.addError(E10049, &hashMap->location, {hashMap->pname()});
    }
    for (const auto element : hashMap->initialElements) {
        visitExpr(element->key);
        visitExpr(element->value);
    }
    const auto firstElement = hashMap->initialElements.front();
    typePair->key = firstElement->key->type;
    typePair->value = firstElement->value->type;
}

void LgsSema::visitVectorExpr(const LgsVectorExpr* vectorExpr) {
    auto sumDim = 0;
    for (const auto arg : vectorExpr->args) {
        visitExpr(arg);
        if (arg->type->isNumber) {
            sumDim++;
        } else if (const auto otherVec = arg->type->asVec()) {
            sumDim += otherVec->dim;
        } else {
            errHandler.addError(E10073, &vectorExpr->location, {arg->type->pname()});
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
        break;
    }
    case FIELD: {
        variable->ref.field = symbol->field;
        variable->isMutable = !symbol->field->isConst;
        variable->setType(symbol->field->type);
        break;
    }
    case PARAM: {
        variable->ref.param = symbol->param;
        variable->setType(symbol->param->type);
        if (symbol->param->isOwner) {
            variable->owner = symbol->param;
        }
        break;
    }
    case ENUM: {
        variable->ref.lgsEnum = symbol->lgsEnum;
        variable->setType(symbol->lgsEnum);
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
    default:
        assert(false);
    }
    assert(variable->ref.symbolType != UNKNOWN);
}

void LgsSema::visitSelection(LgsSelection* selection) {
    const auto exprs = selection->exprs;
    const auto firstExpr = exprs.front();
    visitFirstSelection(firstExpr);
    if (!firstExpr->type || firstExpr->type->isUnknown) return;
    visitInnerSelections(selection);
    selection->setType(selection->lastExpr()->type);
    selection->isMutable = selection->lastExpr()->isMutable;
    selection->owner = selection->lastExpr()->owner;
    validateMock(selection);
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
            visitVarSelection(var, parentExpr->type);
        } else if (const auto methodCall = childExpr->asFuncCall()) {
            visitMethodCall(methodCall, parentExpr);
        } else if (const auto iterIndex = childExpr->asIterIndex()) {
            visitIterIndexSelection(iterIndex, parentExpr->type);
        } else {
            assert(0);
        }
        if (!childExpr->type || childExpr->type->isUnknown) {
            return;
        }
    }
}

void LgsSema::visitVarSelection(LgsVariable* child, LgsType* parentType) {
    if (!parentType) return;
    if (parentType->asVec() && !validateVecElements(child, parentType->asVec())) return;
    auto childName = child->name;
    const auto field = parentType->getField(childName);
    if (!field) {
        errHandler.addError(E10005, &child->location, {childName, parentType->pname()});
        return;
    }
    child->setType(field->type);
    child->isMutable = !field->isConst;
    child->ref = LgsSymbol(field);
    if (field->isOwner) {
        child->owner = field;
    }
    if (const auto parentAsObj = parentType->asObject()) {
        validateFieldVisibility(field, parentAsObj);
    }
}

void LgsSema::visitIterIndexSelection(LgsIterIndex* child, LgsType* parentType) {
    const auto baseExpr = child->baseExpr->asVariable();
    const auto field = parentType->getField(baseExpr->name);
    if (!field) {
        return errHandler.addError(E10005, &child->location, {baseExpr->name, parentType->pname()});
    }
    const auto iterable = field->type->asIterable();
    if (!iterable) {
        return errHandler.addError(E10002, &child->location, {baseExpr->name});
    }
    child->type = iterable->baseType;
    child->baseExpr->type = iterable;
    baseExpr->ref = LgsSymbol(field);
    visitIndex(child);
}

void LgsSema::visitMethodCall(LgsFuncCall* methodCall, LgsExpr* parent) {
    if (!resolveMethodCall(methodCall, parent->type)) return;
    if (methodCall->func->funcType->isMethod) {
        if (parent->asTypeExpr()) {
            errHandler.addError(E10083, &methodCall->location, {methodCall->func->funcType->pname()});
        } else {
            methodCall->args.insert(methodCall->args.begin(), parent);
        }
    }
    validateMethodVisibility(methodCall, parent->type->asObject());
}

void LgsSema::visitFuncCall(LgsFuncCall* funcCall) {
    for (const auto arg : funcCall->args) {
        visitExpr(arg);
    }
    resolveFuncCall(funcCall);
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
    visitExpr(baseExpr);
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

void LgsSema::visitTypeExpr(LgsTypeExpr* typeExpr) {
    typeExpr->type = typeResolver.resolveType(typeExpr->type, file);
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
        matchExprToType(arg->expr, field->type);
        field->expr = arg->expr;
        if (field->isOwner) {
            field->expr->owner = field;
        }
    }

    // Zero values
    for (const auto field : instance->obj->fields) {
        if (visited.count(field->name)) continue;
        if (!field->expr) {
            field->expr = field->type->getZeroValue();
        }
        if (field->isOwner) {
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
    if (baseExpr->type->isUnknown) return;
    const auto iterable = baseExpr->type->asIterable();
    if (!iterable) {
        const auto typeName = baseExpr->type ? baseExpr->type->pname() : LGS_UNKNOWN_TYPE;
        return errHandler.addError(E10002, &iterIndex->location, {baseExpr->pname(), typeName});
    }
    visitIndex(iterIndex);
}

void LgsSema::visitIndex(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto iterable = baseExpr->type->asIterable();
    const auto exprFrom = iterIndex->index->from;
    const auto exprTo = iterIndex->index->to;
    visitExpr(exprFrom);
    visitExpr(exprTo);
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
    if (!iterable->getIndexType()->canCastTo(exprFrom->type)) {
        return errHandler.addError(E10036, &iterIndex->location, {iterIndex->pname(), exprFrom->type->pname()});
    }
    if (!iterable->getIndexType()->canCastTo(exprTo->type)) {
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

void LgsSema::visitLoopMetaVar(LgsLoopMetaVar* metaVar) {
    const auto loop = stack.currentLoop();
    if (!loop) {
        return errHandler.addError(E10060, &metaVar->location);
    }

    const auto name = metaVar->pname();
    if (loop->asWhileLoop()) {
        errHandler.addError(E10065, &metaVar->location, {name});
    } else if (loop->asInfiniteLoop()) {
        errHandler.addError(E10061, &metaVar->location, {name});
    }

    if (metaVar->varType == FOR_I) {
        if (const auto rangeLoop = loop->asRangeLoop()) {
            metaVar->setType(rangeLoop->endRange->type);
        } else {
            metaVar->setType(&LGS_INT);
        }
    }

    if (loop->metaVars.find(metaVar->varType) == loop->metaVars.end()) {
        loop->metaVars[metaVar->varType] = metaVar;
    }
}

bool LgsSema::resolveForeachVars(const LgsForeachLoop* foreachLoop, LgsExpr* iterExpr, const LgsIterable* iterable) {
    const auto varDecSize = foreachLoop->loopVars.size();
    const auto unpackCount = iterable->getUnpackCount();
    if (unpackCount != varDecSize) {
        errHandler.addError(E10041, &iterExpr->location, {iterExpr->pname(), std::to_string(unpackCount), std::to_string(unpackCount + 1), std::to_string(varDecSize)});
        return false;
    }
    if (const auto pair = iterable->baseType->asPair()) {
        foreachLoop->loopVars[0]->type = pair->key;
        foreachLoop->loopVars[1]->type = pair->value;
    } else {
        foreachLoop->loopVars[0]->type = new LgsPtr(iterable->baseType);
    }
    return true;
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

void LgsSema::matchExprToType(const LgsExpr* expr, LgsType* type) {
    if (expr->isNull) {
        // null must have a type
        if (!type || type->isUnknown) {
            return errHandler.addError(E10024, &expr->location);
        }
        // type must be nullable
        if (!type->asNullable()) {
            errHandler.addError(E10023, &type->location, {type->pname(), type->pname()});
        }
        return;
    }
    if (expr->type == type) return;
    if (!type || !expr->type) return;
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
    const auto exprFrom = iterIndex->index->from;
    const auto iterable = baseExpr->type->asIterable();
    if (!iterable->getIndexType()->canCastTo(exprFrom->type)) {
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
    if (!field->isPublic && file->id != field->location.fileID && !stack.currentFunc()->isTest) {
        if (parent) errHandler.addError(E10030, &field->location, {field->name, parent->name});
        return false;
    }
    return true;
}

bool LgsSema::validateMethodVisibility(const LgsFuncCall* methodCall, const LgsObject* parent) {
    if (parent && parent->singleton) return true;
    const auto method = methodCall->func;
    if (!method || method->funcType->isVirtual) return false;
    if (!method->funcType->isPublic && file->id != method->location.fileID && !stack.currentFunc()->isTest) {
        errHandler.addError(E10031, &methodCall->location, {method->funcType->name, method->funcType->parentName});
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
        LgsType* type = nullptr;
        if (symbol->symbolType == VAR_DEC) {
            type = symbol->varDec->type;
            if (const auto func = symbol->varDec->expr->asFunc()) {
                if (funcCall->equals(func->funcType)) {
                    funcCall->func = func;
                    funcCall->setType(func->funcType->rt);
                } else {
                    errHandler.addError(E10015, &funcCall->location, {funcCall->name, funcCall->pname(), func->pname()});
                }
            }
        } else if (symbol->symbolType == PARAM) {
            type = symbol->param->type;
            if (funcCall->equals(type->asFuncType())) {
                funcCall->ref.symbolType = PARAM;
                funcCall->ref.param = symbol->param;
            } else {
                errHandler.addError(E10015, &funcCall->location, {funcCall->name, funcCall->pname(), type->pname()});
            }
        }
        if (!type->asFuncType()) {
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
    for (size_t i = method->funcType->isMethod; i < method->funcType->params.size(); ++i) {
        const auto param = method->funcType->params[i];
        const auto paramType = param.type;
        const auto arg = methodCall->args[i - method->funcType->isMethod];
        arg->completeType(paramType);
        visitExpr(arg);
    }
    if (methodCall->equals(method->funcType)) {
        methodCall->func = method;
        methodCall->setType(method->funcType->rt);
    } else {
        errHandler.addError(E10034, &methodCall->location, {parentType->pname(), name, methodCall->pname(), method->pname()});
        return false;
    }
    return true;
}

void LgsSema::validateMock(const LgsSelection* selection) {
    const auto currentFunc = stack.currentFunc();
    if (selection->exprs.size() != 2) {
        return;
    }
    const auto funcCall1 = selection->exprs[0]->asFuncCall();
    const auto funcCall2 = selection->exprs[1]->asFuncCall();
    if (funcCall1 && funcCall2 && funcCall1->name == "when" && funcCall2->name == "ret") {
        auto mock = LgsMock(funcCall1->args.front(), funcCall2->args.front());
        assert(0);
    }
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
