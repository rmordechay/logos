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
#include "exprs/LgsNull.h"
#include "exprs/LgsPostfixExpr.h"
#include "exprs/LgsPrefixExpr.h"
#include "exprs/LgsTernaryExpr.h"
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
#include "types/LgsInterface.h"
#include "types/LgsNullable.h"
#include "loops/LgsForeachLoop.h"
#include "loops/LgsForLoop.h"
#include "loops/LgsLoopMetaVar.h"
#include "loops/LgsRangeLoop.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsIOPair.h"
#include "stmts/LgsIOStmt.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsSwitch.h"
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
    for (const auto interface : mainFile->interfaces) {
        visitInterface(interface);
    }
    for (const auto obj : mainFile->objects) {
        visitObject(obj);
    }
    for (const auto& [funcName, func] : mainFile->funcs) {
        if (funcName == LGS_MAIN_FUNC) {
            visitMainFunc(dynamic_cast<LgsMainFunc*>(func));
        }
        visitFunc(func);
    }
    if (mainFile->funcs.find(LGS_MAIN_FUNC) == mainFile->funcs.end()) {
        errHandler.addError(E10000, &file->location, file->absPath, {});
    }
}

void LgsSema::visitObject(LgsObject* obj) {
    for (const auto generic : obj->generics) {
        visitGeneric(generic);
    }
    for (const auto field : obj->fields) {
        visitField(field);
    }
    for (const auto& [_, method] : obj->methods) {
        visitFunc(method);
    }
    for (const auto ioPair : obj->ioPairs) {
        visitIOPair(ioPair, obj);
    }
    validateObjImplements(obj, obj->implements);
    validateObjDuplicates(obj);
}

void LgsSema::visitInterface(LgsInterface* interface) {
    for (const auto& [_, method] : interface->methods) {
        visitFunc(method);
    }
}

void LgsSema::visitTestFile(const LgsTestFile* testFile) {
    for (const auto& func : testFile->funcs) {
        visitFunc(func);
    }
    for (const auto& test : testFile->tests) {
        visitFunc(test);
    }
}

void LgsSema::visitGeneric(LgsGeneric* generic) {
}

void LgsSema::visitField(LgsField* field) {
    if (field->expr) {
        visitExpr(field->expr);
        validateExprType(field->expr, field->type);
    }
    if (field->expr && field->expr->asFunc()) {
        errHandler.addError(E10013, &field->location, file->absPath, {field->name});
    }
    if (!field->type->isHeapAlloc && field->isOwner) {
        field->isOwner = false;
    }
}

void LgsSema::visitFunc(LgsFunc* func) {
    stack.enterScope(func);
    auto defaultParamsStarted = false;
    for (auto& param : func->funcType->params) {
        visitParam(&param);
        if (defaultParamsStarted && !param.expr) {
            errHandler.addError(E10028, &param.location, file->absPath, {});
            break;
        }
        defaultParamsStarted = !!param.expr;
    }
    visitStmtsBlock(func->stmtsBlock);
    if (func->funcType->isVariadic && func->funcType->hasDefaults()) {
        errHandler.addError(E10043, &func->location, file->absPath, {});
    }
    if (!validateBlockControlFlow(func->stmtsBlock, func)) {
        errHandler.addError(E10055, &func->location, file->absPath, {func->asText()});
    }
    // for (const auto& orphan : func->orphans) {
    //     errHandler.addError(E10077, &orphan->location, file->absPath, {orphan->pname()});
    // }
    stack.exitScope();
}

void LgsSema::visitMainFunc(const LgsMainFunc* mainFunc) {
    const auto ft = mainFunc->funcType;
    const auto paramSize = ft->params.size();
    if (paramSize == 0) return;
    if (paramSize != 1) {
        return errHandler.addError(E10039, &mainFunc->location, file->absPath, {});
    }
    const auto firstParam = ft->params.front();
    const auto iterable = firstParam.type->asIterable();
    if (!iterable || !iterable->baseType->asStr()) {
        return errHandler.addError(E10039, &mainFunc->location, file->absPath, {});
    }
    freeType(ft->params.front().type);
    const auto sArray = new LgsSArray(new LgsStr(), LGS_INT.getZeroValue());
    ft->params.front().type = sArray;
    ft->params.front().expr = new LgsArrayExpr(sArray);
}

void LgsSema::visitLambda(LgsFunc* lambda) {
    const auto stmtsBlock = lambda->stmtsBlock;
    // Wraps in return if it's the last statement
    if (!lambda->funcType->rt->isVoid()) {
        const auto expr = stmtsBlock->stmts.back()->asExpr();
        if (expr) {
            const auto returnStmt = new LgsReturn(expr);
            returnStmt->location = expr->location;
            stmtsBlock->stmts[0] = returnStmt;
        }
    }
    visitFunc(lambda);
}

void LgsSema::visitParam(LgsParam* param) {
    if (param->expr) {
        param->expr->completeType(param->type);
        visitExpr(param->expr);
        validateExprType(param->expr, param->type);
    } else if (param->isVariadic) {
        if (param->expr) {
            errHandler.addError(E10045, &param->location, file->absPath, {});
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
        errHandler.addError(E10005, &ioPair->openFunc->location, file->absPath, {ioPair->openFuncName, obj->pname()});
    }
    if (!ioPair->closeFunc) {
        errHandler.addError(E10005, &ioPair->closeFunc->location, file->absPath, {ioPair->closeFuncName, obj->pname()});
    }
}

void LgsSema::visitStmt(LgsStmt* stmt) {
    if (const auto pattern = stmt->asSwitch()) visitSwitch(pattern);
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
    else if (auto expr = stmt->asExpr()) visitExpr(expr);
    else assert(0);
}

void LgsSema::visitStmtsBlock(LgsStmtsBlock* stmtsBlock) {
    if (!stmtsBlock || stmtsBlock->stmts.empty()) return;
    for (const auto& stmt : stmtsBlock->stmts) {
        visitStmt(stmt);
    }
    const auto lastStmt = stmtsBlock->lastStmt();
    stmtsBlock->returnExpr = lastStmt->asReturn();
    for (size_t i = 0; i < stmtsBlock->stmts.size() - 1; ++i) {
        if (stmtsBlock->stmts[i]->isTerminator()) {
            return errHandler.addError(E10059, &lastStmt->location, file->absPath, {});
        }
    }
}

void LgsSema::visitVarDec(LgsVarDec* varDec) {
    if (const auto iter = varDec->type->asIterable()) visitExpr(iter->size);
    if (varDec->expr && varDec->type) {
        if (varDec->isOwner) {
            varDec->expr->owner = varDec;
        }
        varDec->type = typeResolver.resolveType(varDec->type, file);
        varDec->expr->completeType(varDec->type);
        visitExpr(varDec->expr);
        validateExprType(varDec->expr, varDec->type);
        if (varDec->type != varDec->expr->type) {
            freeType(varDec->expr->type);
        }
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
        varDec->isOwner = false;
    }
    addLocalSymbol(LgsSymbol(varDec));
    addHeapExpr(varDec->expr);
}

void LgsSema::visitAssignment(LgsAssignment* assignment) {
    visitExpr(assignment->lValue);
    assignment->rValue->completeType(assignment->lValue->type);
    visitExpr(assignment->rValue);
    if (!validateExprType(assignment->rValue, assignment->lValue->type)) return;
    if (!assignment->lValue->type || !assignment->rValue->type) return;
    if (!assignment->lValue->isMutable) {
        return errHandler.addError(E10051, &assignment->lValue->location, file->absPath, {assignment->lValue->asText()});
    }
    auto canAssign = false;
    if (assignment->lValue->asIterIndex() || assignment->lValue->asVariable() || assignment->lValue->asNull()) {
        canAssign = true;
    } else if (const auto selection = assignment->lValue->asSelection()) {
        const auto firstExpr = selection->exprs.front();
        const auto obj = firstExpr->type->asObject();
        if (obj && !obj->singleton && firstExpr->asTypeExpr()) {
            errHandler.addError(E10089, &selection->location, file->absPath, {firstExpr->asText(), selection->lastExpr()->asText()});
            return;
        }
        canAssign = true;
    }
    if (!canAssign) {
        return errHandler.addError(E10012, &assignment->lValue->location, file->absPath, {assignment->lValue->asText(), assignment->getAssignTypeStr(), assignment->rValue->type->pname()});
    }
}

void LgsSema::visitIfStmt(LgsIfStmt* ifStmt) {
    stack.enterScope(ifStmt);
    visitExpr(ifStmt->ifCond);
    visitStmtsBlock(ifStmt->ifBlock);
    stack.exitScope();
    for (auto& [expr, block] : ifStmt->elseIfs) {
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

void LgsSema::visitSwitch(LgsSwitch* switchStmt) {
    visitExpr(switchStmt->cond);
    stack.enterScope(switchStmt);
    const auto condType = switchStmt->cond->type;
    // Allows local enum fields to not have a qualifier inside the block
    if (condType && condType->asEnum()) {
        for (const auto& field : condType->fields) {
            addLocalSymbol(LgsSymbol(field));
        }
    }
    for (auto [expr, block] : switchStmt->patterns) {
        if (!condType || expr->type->isUnknown()) continue;
        stack.enterScope(switchStmt);
        visitExpr(expr);
        visitStmtsBlock(block);
        if (expr->type && !expr->type->canCastTo(condType)) {
            errHandler.addError(E10014, &expr->location, file->absPath, {expr->type->pname(), condType->pname()});
        }
        stack.exitScope();
    }
    if (switchStmt->elseBlock) {
        stack.enterScope(switchStmt);
        visitStmtsBlock(switchStmt->elseBlock);
        stack.exitScope();
    }
    stack.exitScope();
}

void LgsSema::visitWhileLoop(LgsWhileLoop* whileLoop) {
    visitExpr(whileLoop->condExpr);
    const auto condType = whileLoop->condExpr->type;
    if (!condType->asBool()) {
        return errHandler.addError(E10066, &whileLoop->location, file->absPath, {whileLoop->condExpr->asText(), condType->pname()});
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
    auto startRange = rangeLoop->startRange;
    auto endRange = rangeLoop->endRange;
    assert(endRange);
    visitExpr(endRange);
    visitExpr(startRange);
    if (endRange->type && !endRange->type->isNumber()) {
        errHandler.addError(E10082, &endRange->location, file->absPath, {endRange->asText(), endRange->type->pname()});
    }

    if (startRange) {
        if (startRange->type && !startRange->type->isNumber()) {
            errHandler.addError(E10082, &startRange->location, file->absPath, {startRange->asText(), startRange->type->pname()});
        }
        if (!startRange->type->equals(endRange->type)) {
            errHandler.addError(E10081, &startRange->location, file->absPath, {startRange->asText(), endRange->asText()});
        }
    } else {
        rangeLoop->startRange = LGS_SIZE.getZeroValue();
    }

    // Range loop can have only one var
    if (!rangeLoop->loopVars.empty()) {
        rangeLoop->loopVars.front()->type = endRange->type;
        addLocalSymbol(LgsSymbol(rangeLoop->loopVars.front()));
    }
    visitStmtsBlock(rangeLoop->stmtsBlock);
}

void LgsSema::visitForeachLoop(LgsForeachLoop* foreachLoop) {
    auto iterExpr = foreachLoop->iterExpr;
    visitExpr(iterExpr);
    const auto iterable = iterExpr->type->asIterable();
    if (!iterable) {
        if (iterExpr->type) {
            errHandler.addError(E10002, &iterExpr->location, file->absPath, {iterExpr->asText(), iterExpr->type->pname()});
        }
        return;
    }

    const bool unpacked = iterable->unpackLoopVarsTypes(foreachLoop);
    if (!unpacked) {
        errHandler.addError(E10041, &foreachLoop->iterExpr->location, file->absPath, {foreachLoop->iterExpr->asText(), foreachLoop->iterExpr->type->pname(), std::to_string(foreachLoop->loopVars.size())});
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

void LgsSema::visitReturnStmt(LgsReturn* returnStmt) {
    const auto funcType = stack.currentFunc()->funcType;
    auto retExpr = returnStmt->expr;
    if (retExpr) {
        stack.currentFunc()->returnStmts.push_back(returnStmt);
        visitExpr(retExpr);
    }
    const auto rt = funcType->rt;
    if (rt->isVoid() && retExpr && retExpr->type && !retExpr->type->isVoid()) {
        errHandler.addError(E10027, &returnStmt->location, file->absPath, {retExpr->type->pname()});
    } else if (!rt->isVoid() && !retExpr) {
        errHandler.addError(E10026, &returnStmt->location, file->absPath, {funcType->name, rt->pname()});
    } else if (retExpr && retExpr->type && !rt->canCastTo(retExpr->type)) {
        errHandler.addError(E10004, &returnStmt->location, file->absPath, {funcType->name, rt->pname(), retExpr->type->pname()});
    }
}

void LgsSema::visitContinueStmt(const LgsContinue* continueStmt) {
    if (!stack.currentLoop()) {
        errHandler.addError(E10038, &continueStmt->location, file->absPath, {});
    }
}

void LgsSema::visitBreakStmt(const LgsBreak* breakStmt) {
    if (breakStmt->isBreakIf) {
        if (!stack.currentIfStmt()) errHandler.addError(E10071, &breakStmt->location, file->absPath, {});
    } else if (!stack.currentLoop() && breakStmt->tag == "") {
        errHandler.addError(E10017, &breakStmt->location, file->absPath, {});
    }
}

void LgsSema::visitCoroutine(const LgsCoroutine* coroutine) {
    if (coroutine->funcCall) visitFuncCall(coroutine->funcCall);
    else if (coroutine->selection) visitSelection(coroutine->selection);
    else assert(0);
}

void LgsSema::visitDeferStmt(const LgsDeferStmt* deferStmt) {
    if (deferStmt->funcCall) visitFuncCall(deferStmt->funcCall);
    else if (deferStmt->selection) visitSelection(deferStmt->selection);
    else assert(0);
    stack.currentFunc()->hasDefers = true;
}

void LgsSema::visitIOStmt(const LgsIOStmt* ioStmt) {
    visitVarDec(ioStmt->varDec);
    const auto expr = ioStmt->varDec->expr;
    const auto funcCall = expr->asFuncCall() ? expr->asFuncCall() : expr->asSelection()->asMethodCall();
    if (!funcCall->func->funcType->isInIOPair) {
        errHandler.addError(E10084, &funcCall->location, file->absPath, {funcCall->asText()});
    }
    visitStmtsBlock(ioStmt->stmtsBlock);
}

void LgsSema::visitExpr(LgsExpr*& expr) {
    if (!expr) return;
    if (const auto iter = expr->type->asIterable()) {
        visitExpr(iter->size);
    }
    if (const auto ternaryExpr = dynamic_cast<LgsTernaryExpr*>(expr)) {
        visitTernaryExpr(ternaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
    } else {
        if (const auto variable = expr->asVariable()) visitVariable(variable);
        else if (const auto lambda = expr->asFunc()) visitLambda(lambda);
        else if (const auto instance = expr->asInstance()) visitInstance(instance);
        else if (const auto funcCall = expr->asFuncCall()) visitFuncCall(funcCall);
        else if (const auto strConst = expr->asStrConst()) visitStrConst(strConst);
        else if (const auto selection = expr->asSelection()) visitSelection(selection);
        else if (const auto arrayExpr = expr->asArrayExpr()) visitArrayExpr(arrayExpr);
        else if (const auto hashMap = expr->asHashMap()) visitHashMap(hashMap);
        else if (const auto iterIndex = expr->asIterIndex()) visitIterIndex(iterIndex);
        else if (const auto postfixExpr = expr->asPostfixExpr()) visitPostfixExpr(postfixExpr);
        else if (const auto prefixExpr = expr->asPrefixExpr()) visitPrefixExpr(prefixExpr);
        else if (const auto forVar = expr->asLoopMetaVar()) visitLoopMetaVar(forVar);
        else if (const auto vecExpr = expr->asVectorExpr()) visitVectorExpr(vecExpr);
        else if (const auto castExpr = expr->asCast()) visitCast(castExpr);
        else if (const auto json = expr->asJson()) visitJson(json);
        if (expr->isNullable) {
            expr->type = new LgsNullable(expr->type);
        }
    }
}

void LgsSema::visitBinaryExpr(LgsBinaryExpr* binaryExpr) {
    auto l = binaryExpr->left;
    auto r = binaryExpr->right;
    visitExpr(l);
    visitExpr(r);
    const auto ltype = l->type;
    const auto rtype = r->type;
    if (!ltype || !rtype) return;
    const auto type = ltype->applyBinOp(binaryExpr->op.opType, rtype);
    if (!type) {
        return errHandler.addError(E10076, &l->location, file->absPath, {binaryExpr->op.name, ltype->pname(), rtype->pname()});
    }
    binaryExpr->setType(type);
}

void LgsSema::visitTernaryExpr(LgsTernaryExpr* ternary) {
    auto condExpr = ternary->condExpr;
    auto thenExpr = ternary->thenExpr;
    auto elseExpr = ternary->elseExpr;
    visitExpr(condExpr);
    visitExpr(thenExpr);
    visitExpr(elseExpr);
    if (!condExpr->type->asBool()) {
        errHandler.addError(E10092, &ternary->location, file->absPath, {condExpr->asText(), condExpr->type->pname()});
    }
    if (!thenExpr->type->canCastTo(elseExpr->type)) {
        errHandler.addError(E10021, &ternary->location, file->absPath, {thenExpr->asText(), elseExpr->asText(), thenExpr->type->pname(), elseExpr->type->pname()});
    }
    ternary->type = thenExpr->type;
}

void LgsSema::visitCast(LgsCast* cast) {
    visitExpr(cast->fromValue);
    if (!cast->fromValue->type) return;
    cast->toType = typeResolver.resolveType(cast->toType, file);
    cast->value = cast->fromValue->castTo(cast->toType, true);
    if (!cast->value) {
        errHandler.addError(E10018, &cast->location, file->absPath, {cast->fromValue->asText(), cast->toType->pname()});
        return;
    }
    cast->type = cast->value->type;
}

void LgsSema::visitArrayExpr(LgsArrayExpr* arrayExpr) {
    if (arrayExpr->elements.empty() && !arrayExpr->type) {
        return errHandler.addError(E10049, &arrayExpr->location, file->absPath, {arrayExpr->asText()});
    }
    const auto iter = arrayExpr->type->asIterable();
    for (auto element : arrayExpr->elements) {
        visitExpr(element);
        if (iter->baseType && !element->type->canCastTo(iter->baseType)) {
            return errHandler.addError(E10001, &element->location, file->absPath, {iter->pname(), element->type->pname()});
        }
    }
    if (arrayExpr->type->asDArray() || arrayExpr->type->asSet()) {
        visitDynamicArray(arrayExpr);
    } else if (arrayExpr->type->asSArray()) {
        visitStaticArray(arrayExpr);
    } else {
        assert(0);
    }
}

void LgsSema::visitStaticArray(const LgsArrayExpr* arrayExpr) {
    const auto& initialElements = arrayExpr->elements;
    const auto arr = arrayExpr->type->asSArray();
    for (auto element : initialElements) {
        visitExpr(element);
    }
    if (!arr->baseType) {
        arr->baseType = initialElements.front()->type;
    }
}

void LgsSema::visitDynamicArray(LgsArrayExpr* arrayExpr) {
    const auto dArr = arrayExpr->type->asIterable();
    if (!dArr->baseType && arrayExpr->elements.empty()) {
        return errHandler.addError(E10049, &arrayExpr->location, file->absPath, {arrayExpr->asText()});
    }

    LgsType* baseType = nullptr;
    if (dArr->baseType) {
        baseType = dArr->baseType;
    } else if (const auto innerArr = arrayExpr->elements.front()->asArrayExpr()) {
        baseType = innerArr->type;
    } else {
        baseType = arrayExpr->elements.front()->type;
    }
    dArr->baseType = baseType;
}

void LgsSema::visitHashMap(LgsHashMap* hashMap) {
    for (auto [key, value] : hashMap->pairs) {
        visitExpr(key);
        visitExpr(value);
    }
    if (hashMap->type) return;
    if (hashMap->pairs.empty()) {
        return errHandler.addError(E10049, &hashMap->location, file->absPath, {LgsMap::name});
    }
    const auto [key, value] = hashMap->pairs.front();
    hashMap->type = new LgsMap(key->type, value->type);
}

void LgsSema::visitVectorExpr(const LgsVectorExpr* vectorExpr) {
    auto sumDim = 0;
    for (auto arg : vectorExpr->args) {
        visitExpr(arg);
        if (arg->type->isNumber()) {
            sumDim++;
        } else if (const auto otherVec = arg->type->asVec()) {
            sumDim += otherVec->vectorDim;
        } else {
            errHandler.addError(E10073, &vectorExpr->location, file->absPath, {arg->type->pname()});
            break;
        }
    }
    if (sumDim > vectorExpr->vecType->vectorDim) {
        errHandler.addError(E10074, &vectorExpr->location, file->absPath, {std::to_string(vectorExpr->vecType->vectorDim), std::to_string(sumDim)});
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

    if (const auto var = firstExpr->asVariable()) {
        if (var->ref.symbolType == OBJECT) {
            const auto typeExpr = new LgsTypeExpr(var->ref.object);
            freeExpr(firstExpr);
            selection->exprs[0] = typeExpr;
        }
    }
    visitInnerSelections(selection);

    const auto lastExpr = selection->lastExpr();
    if (selection->hasNullables && !lastExpr->type->asNullable()) {
        lastExpr->type = new LgsNullable(lastExpr->type);
    }

    selection->type = lastExpr->type;
    selection->isMutable = lastExpr->isMutable;
    selection->owner = lastExpr->owner;
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

void LgsSema::visitInnerSelections(LgsSelection* selection) {
    const auto exprs = selection->exprs;
    selection->hasNullables = exprs.front()->type->asNullable();
    for (size_t i = 0; i < exprs.size() - 1; ++i) {
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
        selection->hasNullables = selection->hasNullables || childExpr->type->asNullable();
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
        validateFieldVisibility(field, parentType);
    } else if (const auto method = parentType->getMethod(childName)) {
        child->setType(method->type);
        child->isMutable = false;
        child->ref = LgsSymbol(method);
        validateMethodVisibility(method, parentType, method->location);
    } else {
        errHandler.addError(E10005, &child->location, file->absPath, {childName, parentType->pname()});
    }
}

void LgsSema::visitIterIndexSelection(LgsIterIndex* iterIndex, LgsType* parentType) {
    if (const auto innerIterIndex = iterIndex->baseExpr->asIterIndex()) {
        visitIterIndexSelection(innerIterIndex, parentType);
    } else {
        const auto baseExpr = iterIndex->baseExpr->asVariable();
        const auto field = parentType->getField(baseExpr->name);
        if (!field) {
            return errHandler.addError(E10005, &iterIndex->location, file->absPath, {baseExpr->name, parentType->pname()});
        }
        baseExpr->type = field->type;
        baseExpr->ref = LgsSymbol(field);
    }
    visitIndex(iterIndex);
}

void LgsSema::visitMethodCall(LgsFuncCall* methodCall, LgsExpr* parent) {
    auto name = methodCall->name;
    const auto method = parent->type->getMethod(name);
    if (!method) {
        return errHandler.addError(E10005, &methodCall->location, file->absPath, {name, parent->type->pname()});
    }
    if (parent->asTypeExpr() && method->funcType->isMethod) {
        return errHandler.addError(E10083, &methodCall->location, file->absPath, {method->funcType->pname()});
    }
    methodCall->selfPtr = parent;
    if (method->funcType->isMethod) {
        methodCall->args.insert(methodCall->args.begin(), parent);
    }
    for (size_t i = method->funcType->isMethod; i < method->funcType->params.size(); ++i) {
        if (i >= methodCall->args.size()) continue;
        auto arg = methodCall->args[i];
        const auto& param = method->funcType->params[i];
        arg->completeType(param.type);
        visitExpr(arg);
    }
    if (methodCall->equals(method->funcType)) {
        methodCall->func = method;
        methodCall->setType(method->funcType->rt);
    } else {
        errHandler.addError(E10034, &methodCall->location, file->absPath, {parent->type->pname(), name, methodCall->asText(), method->asText()});
        return;
    }

    if (!validateMethodVisibility(method, parent->type, methodCall->location)) return;
    if (stack.currentFunc()->isTest && parent->type->pname() == LgsTest::name && methodCall->name == "mock") {
        const auto pair = std::make_pair(methodCall->args[0], methodCall->args[1]);
        stack.currentFunc()->mocks.push_back(pair);
    }
}

void LgsSema::visitFuncCall(LgsFuncCall* funcCall) {
    const auto symbol = getSymbol(funcCall->name, &funcCall->location);
    if (!symbol) return;
    const auto ft = symbol->getType()->asFuncType();
    if (!ft) {
        return errHandler.addError(E10046, &funcCall->location, file->absPath, {funcCall->name});
    }
    for (size_t i = ft->isMethod; i < ft->params.size(); ++i) {
        if (i >= funcCall->args.size()) break;
        auto& arg = funcCall->args[i];
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
        for (const auto arg : funcCall->args) if (!arg->type) return;
        errHandler.addError(E10015, &funcCall->location, file->absPath, {funcCall->name, funcCall->asText(), ft->pname()});
    }
}

void LgsSema::visitPrefixExpr(LgsPrefixExpr* prefixExpr) {
    auto baseExpr = prefixExpr->expr;
    visitExpr(baseExpr);
    switch (prefixExpr->op) {
    case MINUS_PREFIX: {
        if (!baseExpr->type->isNumber()) {
            errHandler.addError(E10090, &prefixExpr->location, file->absPath, {"-", baseExpr->type->pname()});
            return;
        }
        prefixExpr->setType(baseExpr->type);
        break;
    }
    case NOT_PREFIX: {
        if (!baseExpr->type->asBool()) {
            errHandler.addError(E10091, &prefixExpr->location, file->absPath, {baseExpr->type->pname()});
            return;
        }
        prefixExpr->setType(baseExpr->type);
        break;
    }
    case SQRT_PREFIX: {
        if (!baseExpr->type->isNumber()) {
            errHandler.addError(E10090, &prefixExpr->location, file->absPath, {"_/", baseExpr->type->pname()});
            return;
        }
        prefixExpr->setType(&LGS_DOUBLE);
        break;
    }
    }
}

void LgsSema::visitPostfixExpr(LgsPostfixExpr* postfixExpr) {
    auto baseExpr = postfixExpr->baseExpr;
    visitExpr(baseExpr);
    const auto type = baseExpr->type;
    if (!type->isNumber()) {
        return errHandler.addError(E10050, &postfixExpr->location, file->absPath, {type->pname()});
    }
    postfixExpr->setType(type);
}

void LgsSema::visitStrConst(const LgsStrConst* strConst) {
    if (strConst->parts.empty()) return;
    for (auto templatePart : strConst->parts) {
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
        return errHandler.addError(E10022, &instance->location, file->absPath, {objName});
    }
    if (symbol->symbolType == INTERFACE) {
        return visitInterfaceInstance(instance, symbol->interface);
    }

    const auto obj = symbol->object;
    if (obj->singleton) {
        return errHandler.addError(E10032, &instance->location, file->absPath, {objName});
    }
    instance->setObject(obj->clone());

    // Args
    std::unordered_set<std::string> visited;
    for (auto& [argName, arg] : instance->args) {
        if (visited.count(argName)) {
            errHandler.addError(E10054, &arg->location, file->absPath, {argName});
        }
        visited.insert(argName);
        const auto field = instance->obj->getField(argName);
        if (!field) {
            errHandler.addError(E10005, &arg->location, file->absPath, {argName, objName});
            continue;
        }
        if (!validateFieldVisibility(field, instance->obj)) continue;
        visitExpr(arg);
        validateExprType(arg, field->type);
        if (field->isOwner && field->type->isHeapAlloc) {
            field->expr->owner = field;
        }
    }

    // Missing required fields
    for (const auto& field : instance->obj->fields) {
        if (field->isConst && instance->args.find(field->name) == instance->args.end()) {
            errHandler.addError(E10029, &field->location, file->absPath, {field->name});
        }
    }
}

void LgsSema::visitInterfaceInstance(LgsInstance* instance, LgsInterface* interface) {
    instance->setObject(new LgsObject(interface->name));
    instance->obj->location = instance->location;
    instance->obj->implements.push_back(interface);
    auto isValid = true;
    for (auto& [name, arg] : instance->args) {
        visitExpr(arg);
        const auto field = interface->getField(name);
        if (field) {
            const auto newField = new LgsField(*field);
            newField->expr = arg;
            instance->obj->addField(newField);
            continue;
        }
        const auto method = interface->getMethod(name);
        if (method) {
            const auto newMethod = arg->asFunc();
            newMethod->funcType->name = method->funcType->name;
            newMethod->funcType->params.insert(newMethod->funcType->params.begin(), LgsParam(interface, LGS_SELF));
            instance->obj->addMethod(newMethod);
            continue;
        }
        errHandler.addError(E10005, &arg->location, file->absPath, {name, interface->name});
        isValid = false;
    }
    if (isValid) {
        visitObject(instance->obj);
    }
}

void LgsSema::visitIterIndex(LgsIterIndex* iterIndex) {
    auto baseExpr = iterIndex->baseExpr;
    visitExpr(baseExpr);
    iterIndex->isMutable = baseExpr->isMutable;
    if (!baseExpr->type) return;
    const auto iterable = baseExpr->type->asIterable();
    if (!iterable) {
        const auto typeName = baseExpr->type ? baseExpr->type->pname() : LGS_UNKNOWN_TYPE;
        return errHandler.addError(E10002, &iterIndex->location, file->absPath, {baseExpr->asText(), typeName});
    }
    visitIndex(iterIndex);
}

void LgsSema::visitIndex(LgsIterIndex* iterIndex) {
    const auto iterable = iterIndex->baseExpr->type->asIterable();
    auto exprFrom = iterIndex->index.from;
    visitExpr(exprFrom);
    auto exprTo = iterIndex->index.to;
    if (exprTo) {
        visitExpr(exprTo);
        visitSlice(iterIndex);
        iterIndex->setType(iterable->clone());
    } else {
        if (!exprFrom->type->canCastTo(iterable->getIndexType())) {
            return errHandler.addError(E10036, &iterIndex->location, file->absPath, {iterIndex->asText(), exprFrom->type->pname()});
        }
        if (iterable->isStatic) {
            const auto index = exprFrom->getConstInt();
            const auto bounds = iterable->size->getConstInt();
            if (index && bounds && *index >= *bounds) {
                errHandler.addError(E10048, &iterIndex->location, file->absPath, {iterIndex->asText(), std::to_string(*bounds)});
            }
        }
        iterIndex->setType(iterable->getValueType());
    }
}

void LgsSema::visitSlice(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto exprFrom = iterIndex->index.from;
    const auto exprTo = iterIndex->index.to;
    const auto iterable = baseExpr->type->asIterable();
    if (!baseExpr->type->isSliceable()) {
        return errHandler.addError(E10042, &iterIndex->location, file->absPath, {iterIndex->asText(), baseExpr->type->pname()});
    }
    if (!exprFrom->type->canCastTo(iterable->getIndexType())) {
        return errHandler.addError(E10036, &iterIndex->location, file->absPath, {iterIndex->asText(), exprFrom->type->pname()});
    }
    if (!iterable->getIndexType()->canCastTo(exprTo->type)) {
        return errHandler.addError(E10036, &iterIndex->location, file->absPath, {iterIndex->asText(), exprTo->type->pname()});
    }
    if (iterable->isStatic) {
        const auto sizeFrom = exprFrom->getConstInt();
        const auto sizeTo = exprTo->getConstInt();
        if (!sizeFrom || !sizeTo) return;
        if (*sizeFrom > *sizeTo) {
            return errHandler.addError(E10037, &iterIndex->location, file->absPath, {});
        }
        const auto bounds = iterable->size->getConstInt();
        if (!bounds) return;
        if (*sizeFrom >= *bounds) {
            return errHandler.addError(E10048, &exprFrom->location, file->absPath, {std::to_string(*sizeFrom), std::to_string(*bounds - 1)});
        }
        if (*sizeTo >= *bounds) {
            return errHandler.addError(E10048, &exprTo->location, file->absPath, {std::to_string(*sizeTo), std::to_string(*bounds - 1)});
        }
    }
}

void LgsSema::visitLoopMetaVar(LgsLoopMetaVar* metaVar) {
    const auto loop = stack.currentLoop();
    if (!loop) {
        return errHandler.addError(E10060, &metaVar->location, file->absPath, {});
    }

    metaVar->forLoop = loop;
    const auto name = metaVar->asText();
    if (loop->asWhileLoop() || loop->asWhileLoop()) {
        return errHandler.addError(E10061, &metaVar->location, file->absPath, {name});
    }

    if (loop->metaVars.find(metaVar->varType) == loop->metaVars.end()) {
        loop->metaVars[metaVar->varType] = metaVar;
    }
}

bool LgsSema::validateExprType(LgsExpr* expr, LgsType* type) {
    if (expr->asNull()) {
        const auto nullable = type->asNullable();
        // null must have a type
        if (nullable && !nullable->baseType) {
            errHandler.addError(E10024, &expr->location, file->absPath, {});
            return false;
        }
        // type must be nullable
        if (!nullable) {
            errHandler.addError(E10023, &expr->location, file->absPath, {type->pname()});
            return false;
        }
    }
    if (!type || !expr->type || type->isUnknown() || expr->type->isUnknown()) return false;
    if (!expr->type->canCastTo(type)) {
        errHandler.addError(E10001, &expr->location, file->absPath, {type->pname(), expr->type->pname()});
        return false;
    }
    return true;
}

std::string getMissingImplementsStr(const std::vector<LgsField*>& fields, const std::vector<LgsFunc*>& methods) {
    std::stringstream str;
    str << "Missing fields/methods:";
    if (!fields.empty()) {
        for (const auto& field : fields) {
            str << "\n - " << field->name << ": " << field->type->pname();
        }
    }
    if (!methods.empty()) {
        for (const auto& func : methods) {
            str << "\n - " << func->asText();
        }
    }
    return str.str();
}

void LgsSema::validateObjImplements(LgsObject* obj, const std::vector<LgsType*>& interfaces) {
    std::unordered_set<std::string> interfacesNames;
    for (const auto implementsInterface : interfaces) {
        const auto interface = implementsInterface->asInterface();
        if (!interface) {
            errHandler.addError(E10025, &implementsInterface->location, file->absPath, {implementsInterface->pname()});
            continue;
        }

        // Fields
        std::vector<LgsField*> missingFields;
        for (const auto& interfaceField : interface->fields) {
            const auto objField = obj->getField(interfaceField->name);
            if (objField && objField->type->equals(interfaceField->type)) {
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
            const auto objMethod = obj->methods.find(name);
            if (objMethod != obj->methods.end() && objMethod->second->type->equals(interfaceMethod->type)) {
                objMethod->second->funcType->isVirtual = true;
                continue;
            }
            if (interfaceMethod->stmtsBlock) {
                interfaceMethod->funcType->isVirtual = true;
                continue;
            }
            missingMethods.emplace_back(interfaceMethod);
        }

        if (!missingMethods.empty() || !missingFields.empty()) {
            errHandler.addError(E10016, &obj->location, file->absPath, {obj->pname(), interface->name, getMissingImplementsStr(missingFields, missingMethods)});
        }
    }
}

void LgsSema::validateIndex(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto exprFrom = iterIndex->index.from;
    const auto iterable = baseExpr->type->asIterable();
    if (!exprFrom->type->canCastTo(iterable->getIndexType())) {
        return errHandler.addError(E10036, &iterIndex->location, file->absPath, {iterIndex->asText(), exprFrom->type->pname()});
    }
    if (const auto sArr = iterable->asSArray()) {
        const auto i = exprFrom->getConstInt();
        const auto bounds = sArr->size->getConstInt();
        if (!i || !bounds) return;
        if (*i >= *bounds) {
            return errHandler.addError(E10048, &iterIndex->location, file->absPath, {iterIndex->asText(), std::to_string(*bounds)});
        }
    }
}

bool LgsSema::validateFieldVisibility(LgsField* field, LgsType* parent) {
    if (parent && parent->asObject() && parent->asObject()->singleton) return true;
    if (!field || field->isVirtual) return false;
    if (!field->isPublic && file->id != field->location.fileID && !stack.currentFunc()->isTest) {
        if (parent) errHandler.addError(E10030, &field->location, file->absPath, {field->name, parent->pname()});
        return false;
    }
    return true;
}

bool LgsSema::validateMethodVisibility(const LgsFunc* method, LgsType* parent, const LgsLocation& location) {
    if (parent && parent->asObject() && parent->asObject()->singleton) return true;
    if (!method || method->funcType->isVirtual) return false;
    if (!method->funcType->isPublic && file->id != method->location.fileID && !stack.currentFunc()->isTest) {
        errHandler.addError(E10031, &location, file->absPath, {method->funcType->name, method->funcType->parentName});
        return false;
    }
    return true;
}

bool LgsSema::validateVecElements(const LgsVariable* fieldVar, LgsVec* vec) {
    const auto fieldName = fieldVar->name;
    const auto dim = vec->vectorDim;
    if (fieldName.empty() || fieldName.size() > 4) {
        errHandler.addError(E10069, &fieldVar->location, file->absPath, {vec->pname()});
        return false;
    }

    const auto expectedSet = LgsVec::getSwizzleSet(fieldName[0]);
    if (expectedSet < 0) {
        errHandler.addError(E10070, &fieldVar->location, file->absPath, {fieldName, vec->pname()});
        return false;
    }

    for (const char c : fieldName) {
        if (LgsVec::getSwizzleSet(c) != expectedSet) {
            errHandler.addError(E10070, &fieldVar->location, file->absPath, {fieldName, vec->pname()});
            return false;
        }
        const auto componentIndex = LgsVec::getComponentIndex(c);
        if (componentIndex >= dim) {
            errHandler.addError(E10070, &fieldVar->location, file->absPath, {fieldName, vec->pname()});
            return false;
        }
    }
    return true;
}

void LgsSema::validateObjDuplicates(LgsType* type){
    std::unordered_set<std::string> names;
    for (const auto* f : type->fields) {
        if (!f) continue;
        const auto& name = f->name;
        if (names.count(name)) {
            errHandler.addError(E10056, &type->location, file->absPath, {type->pname(), name});
            break;
        }
        names.insert(name);
    }
    for (const auto& [name, func] : type->methods) {
        if (names.count(name)) {
            errHandler.addError(E10056, &type->location, file->absPath, {type->pname(), name});
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
        } else if (const auto switch_ = stmt->asIfStmt()) {
            for (const auto [_, patternsStmtBlock] : switch_->elseIfs) {
                isValid = isValid && validateBlockControlFlow(patternsStmtBlock, func);
            }
            isValid = isValid && validateBlockControlFlow(switch_->elseBlock, func);
        }
    }
    return isValid;
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
    errHandler.addError(E10006, location, file->absPath, {name});
    return nullptr;
}

void LgsSema::addLocalSymbol(const LgsSymbol& newSymbol) {
    auto symbolName = *newSymbol.name;
    const auto symbol = globals.getSymbol(symbolName);
    if (symbol && symbol->isBuiltin) {
        return errHandler.addError(E10053, newSymbol.location, file->absPath, {symbolName});
    }
    if (file->symbolTable.getSymbol(symbolName)) {
        return errHandler.addError(E10011, newSymbol.location, file->absPath, {symbolName});
    }
    stack.getSymbolTable().addSymbol(newSymbol, &errHandler);
}
