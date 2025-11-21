#include "analysis/LgsSema.h"
#include "builtins/LgsReflect.h"
#include "builtins/LgsTest.h"
#include "funcs/LgsCoroutine.h"
#include "errors/LgsErrors.h"
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
#include "logos/LgsApp.h"
#include "errors/LgsErrHandler.h"
#include "exprs/LgsMatrixExpr.h"
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
#include "loops/LgsMetaVar.h"
#include "loops/LgsRangeLoop.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsIOPair.h"
#include "stmts/LgsIOStmt.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsSwitch.h"
#include "types/primitives/LgsDouble.h"
#include "types/LgsGenericParam.h"
#include <iostream>
#include <ranges>
#include <unordered_set>

static std::string getMissingImplementsStr(const std::vector<LgsField*>& fields, const std::vector<LgsFunc*>& methods);

void LgsSema::analyse() {
    resolveImports();
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
    mergeRTTypes();
}

void LgsSema::visitMainFile(LgsMainFile* mainFile) {
    for (const auto varDec : mainFile->varDecs) {
        if (!varDec->isConst) {
            addError(E10100, varDec->location, {varDec->name});
        }
        visitExpr(varDec->expr);
    }
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
    if (mainFile->funcs.contains(LGS_MAIN_FUNC)) {
        if (appConfigs.isLibrary) {
            addError(E10087, file->location);
        }
    } else if (!appConfigs.isLibrary) {
        addError(E10000, file->location);
    }
}

void LgsSema::visitObject(LgsObject* obj) {
    validateTypeName(obj->name, &obj->location);
    for (const auto generic : obj->generics) {
        visitGeneric(generic);
    }
    for (const auto enum_ : obj->enums) {
        visitEnum(enum_);
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
    validateTypeName(interface->name, &interface->location);
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

void LgsSema::visitGeneric(LgsGenericParam* generic) {
}

void LgsSema::visitEnum(const LgsEnum* enum_) {
    validateTypeName(enum_->name, &enum_->location);
}

void LgsSema::visitField(LgsField* field) {
    if (field->expr) {
        visitExpr(field->expr);
        validateExprType(field->expr, field->type);
    }
    if (field->expr && field->expr->asFunc()) {
        addError(E10013, field->location, {field->name});
    }
    if (!field->type->isHeapAlloc && field->isOwner) {
        field->isOwner = false;
    }
}

void LgsSema::visitFunc(LgsFunc* func) {
    const auto ft = func->funcType;
    if (!ft->genericParams.empty()) return;
    stack.enterScope(func);
    auto defaultParamsStarted = false;
    for (auto& param : ft->params) {
        visitParam(&param);
        if (defaultParamsStarted && !param.expr) {
            addError(E10028, param.location);
            break;
        }
        defaultParamsStarted = !!param.expr;
    }
    visitStmtsBlock(func->stmtsBlock);
    if (ft->isVariadic && ft->hasDefaults) {
        addError(E10043, func->location);
    }
    if (!validateBlockControlFlow(func->stmtsBlock, func)) {
        addError(E10055, func->location, {func->asText()});
    }
    stack.exitScope();
}

void LgsSema::visitMainFunc(const LgsMainFunc* mainFunc) {
    const auto ft = mainFunc->funcType;
    const auto paramSize = ft->params.size();
    if (paramSize == 0) return;
    if (paramSize != 1) {
        return addError(E10039, mainFunc->location);
    }
    auto& firstParam = ft->params.front();
    const auto iterable = firstParam.type->asIterable();
    if (!iterable || !iterable->baseType->asStr()) {
        return addError(E10039, mainFunc->location);
    }
    // Replaces dyn array to static array
    freeType(firstParam.type);
    const auto sArray = new LgsSArray(new LgsStr(), LGS_INT.getZeroValue());
    firstParam.setType(sArray);
    firstParam.expr = new LgsArrayExpr(sArray);
}

void LgsSema::visitLambda(LgsFunc* lambda) {
    const auto ft = lambda->funcType;
    if (ft->params.empty()) {
        ft->params.emplace_back(&LGS_INT, "it");
    }
    const auto stmtsBlock = lambda->stmtsBlock;
    // Wraps in return if it's the last statement
    if (!stmtsBlock->stmts.empty() && !lambda->funcType->rt->isVoid()) {
        const auto expr = stmtsBlock->stmts.back().stmt->asExpr();
        if (expr) {
            const auto returnStmt = new LgsReturn(expr);
            returnStmt->location = expr->location;
            stmtsBlock->stmts[0].stmt = returnStmt;
        }
    }
    visitFunc(lambda);
}

void LgsSema::visitParam(LgsParam* param) {
    validateLocalName(param->name, &param->location);
    if (param->expr) {
        param->expr->castImplicitly(param->type);
        visitExpr(param->expr);
        validateExprType(param->expr, param->type);
    } else if (param->isVariadic) {
        if (param->expr) addError(E10045, param->location);
    }
    addLocalSymbol(LgsSymbol(param));
    assert(param->type);
}

void LgsSema::visitIOPair(LgsIOPair* ioPair, LgsObject* obj) {
    ioPair->openFunc = obj->getMethod(ioPair->openFuncName);
    ioPair->closeFunc = obj->getMethod(ioPair->closeFuncName);
    if (!ioPair->openFunc) {
        addError(E10005, ioPair->openFunc->location, {ioPair->openFuncName, obj->pname()});
    }
    if (!ioPair->closeFunc) {
        addError(E10005, ioPair->closeFunc->location, {ioPair->closeFuncName, obj->pname()});
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
        switch (stmt.type) {
        case LgsObjOrStmt::Type::Object:
            visitObject(stmt.obj);
            addLocalSymbol(LgsSymbol(stmt.obj));
            break;
        case LgsObjOrStmt::Type::Stmt:
            visitStmt(stmt.stmt);
            break;
        }
    }
    if (stmtsBlock->stmts.empty()) return;
    const auto lastStmt = stmtsBlock->stmts[stmtsBlock->stmts.size() - 1];
    stmtsBlock->returnStmt = lastStmt.stmt->asReturn();
    for (size_t i = 0; i < stmtsBlock->stmts.size() - 1; ++i) {
        if (stmtsBlock->stmts[i].stmt->isTerminator()) {
            return addError(E10059, lastStmt.stmt->location);
        }
    }
}

void LgsSema::visitVarDec(LgsVarDec* varDec) {
    validateLocalName(varDec->name, &varDec->location);
    if (const auto iter = varDec->type->asIterable()) visitExpr(iter->size);
    if (varDec->expr && varDec->type) {
        if (varDec->isOwner) {
            varDec->expr->owner = varDec;
        }
        varDec->setType(typeResolver.resolveType(varDec->type, file));
        varDec->expr->castImplicitly(varDec->type);
        visitExpr(varDec->expr);
        validateExprType(varDec->expr, varDec->type);
        if (varDec->type != varDec->expr->type) {
            freeType(varDec->expr->type);
        }
        varDec->expr->setType(varDec->type);
    } else if (varDec->expr) {
        visitExpr(varDec->expr);
        if (varDec->isOwner) {
            varDec->expr->owner = varDec;
        }
        varDec->setType(varDec->expr->type);
        validateExprType(varDec->expr, varDec->type);
    } else {
        varDec->setType(typeResolver.resolveType(varDec->type, file));
        if (!varDec->type) return;
        varDec->expr = varDec->type->getZeroValue();
        varDec->expr->location = varDec->location;
        visitExpr(varDec->expr);
        if (varDec->isOwner) {
            varDec->expr->owner = varDec;
        }
    }
    if (varDec->expr->type->isVoid()) {
        addError(E10093, varDec->location);
    }
    if (varDec->type && !varDec->type->isHeapAlloc && varDec->isOwner) {
        varDec->isOwner = false;
    }
    addLocalSymbol(LgsSymbol(varDec));
    addHeapExpr(varDec->expr);
}

void LgsSema::visitAssignment(const LgsAssignment* assignment) {
    auto l = assignment->lValue;
    auto r = assignment->rValue;
    visitExpr(l);
    visitExpr(r);
    r->castImplicitly(l->type);
    if (!validateExprType(r, l->type)) return;
    if (!l->type || !r->type) return;

    auto canAssign = false;
    if (l->asIterIndex() || l->asVariable() || l->asNull()) {
        canAssign = true;
    } else if (const auto selection = l->asSelection()) {
        const auto firstExpr = selection->exprs.front();
        const auto obj = firstExpr->type->asObject();
        if (obj && !obj->singleton && firstExpr->asTypeExpr()) {
            addError(E10089, selection->location, {firstExpr->asText(), selection->lastExpr()->asText()});
            return;
        }
        canAssign = true;
    }
    if (!canAssign) {
        return addError(E10012, l->location, {l->asText(), assignment->getAssignTypeStr(), r->type->pname()});
    }
}

void LgsSema::visitIfStmt(LgsIfStmt* ifStmt) {
    if (ifStmt->ifBlock->isMacro) return visitMacroIf(ifStmt);
    stack.enterScope(ifStmt);
    visitExpr(ifStmt->ifCond);
    stack.exitScope();
    for (auto& [expr, block] : ifStmt->elseIfs) {
        stack.enterScope(ifStmt);
        visitExpr(expr);
        stack.exitScope();
    }
    if (ifStmt->elseBlock) {
        stack.enterScope(ifStmt);
        visitStmtsBlock(ifStmt->elseBlock);
        stack.exitScope();
    }
}

void LgsSema::visitMacroIf(LgsIfStmt* ifStmt) {
    stack.enterScope(ifStmt);
    auto ifCond = ifStmt->ifCond;
    visitExpr(ifCond);
    if (!ifCond->type->asBool()) {
        addError(E10102, ifCond->location, {ifCond->type->pname()});
        stack.exitScope();
        return;
    }
    auto constValue = ifCond->getConstInt();
    if (!constValue) {
        addError(E10101, ifCond->location);
        stack.exitScope();
        return;
    }
    bool condition = *constValue;
    if (condition) {
        ifStmt->macroTrueBlock = ifStmt->ifBlock;
        stack.exitScope();
        return;
    }
    for (auto& [expr, block] : ifStmt->elseIfs) {
        stack.enterScope(ifStmt);
        visitExpr(expr);
        if (!expr->type->asBool()) {
            addError(E10102, expr->location, {expr->type->pname()});
            stack.exitScope();
            return;
        }
        constValue = expr->getConstInt();
        if (!constValue) {
            addError(E10101, expr->location);
            stack.exitScope();
            return;
        }
        condition = *constValue;
        if (condition) {
            visitStmtsBlock(block);
            ifStmt->macroTrueBlock = block;
            stack.exitScope();
            return;
        }
    }
    if (ifStmt->elseBlock) {
        stack.enterScope(ifStmt);
        visitStmtsBlock(ifStmt->elseBlock);
        ifStmt->macroTrueBlock = ifStmt->elseBlock;
        stack.exitScope();
    }
}

void LgsSema::visitSwitch(LgsSwitch* switchStmt) {
    if (switchStmt->patterns.empty()) {
        return addError(E10097, switchStmt->location);
    }
    visitExpr(switchStmt->cond);
    stack.enterScope(switchStmt);
    const auto condType = switchStmt->cond->type;
    const auto isEnum = condType && condType->asEnum();
    // Allows local enum fields to not have a qualifier inside the block
    if (isEnum) {
        for (const auto& field : condType->fields) {
            addLocalSymbol(LgsSymbol(field));
        }
    }

    std::unordered_set<std::string> handledCases;
    for (auto [expr, block] : switchStmt->patterns) {
        if (!condType || expr->type->isUnknown()) continue;
        stack.enterScope(switchStmt);
        visitExpr(expr);
        if (expr->isMutable) {
            addError(E10044, expr->location, {expr->asText()});
        }
        visitStmtsBlock(block);
        if (expr->type && !expr->type->canCastTo(condType)) {
            addError(E10014, expr->location, {expr->type->pname(), condType->pname()});
        }
        if (isEnum) {
            handledCases.insert(expr->asVariable()->name);
        }
        stack.exitScope();
    }
    if (switchStmt->elseBlock) {
        switchStmt->isExhausted = true;
        stack.enterScope(switchStmt);
        visitStmtsBlock(switchStmt->elseBlock);
        stack.exitScope();
    }

    if (isEnum && !switchStmt->elseBlock) {
        std::vector<std::string> missingCases;
        for (const auto& field : condType->fields) {
            if (handledCases.contains(field->name)) continue;
            missingCases.push_back(field->name);
        }
        if (missingCases.empty()) {
            switchStmt->isExhausted = true;
        }
    }
    stack.exitScope();
}

void LgsSema::visitWhileLoop(LgsWhileLoop* whileLoop) {
    visitExpr(whileLoop->condExpr);
    const auto condType = whileLoop->condExpr->type;
    if (!condType->asBool()) {
        return addError(E10066, whileLoop->location, {whileLoop->condExpr->asText(), condType->pname()});
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
        addError(E10082, endRange->location, {endRange->asText(), endRange->type->pname()});
    }

    if (startRange) {
        if (startRange->type && !startRange->type->isNumber()) {
            addError(E10082, startRange->location, {startRange->asText(), startRange->type->pname()});
        }
        if (!startRange->type->equals(endRange->type)) {
            addError(E10081, startRange->location, {startRange->asText(), endRange->asText()});
        }
    } else {
        rangeLoop->startRange = LGS_INT.getZeroValue();
    }

    // Range loop can have only one var
    if (!rangeLoop->loopVars.empty()) {
        rangeLoop->loopVars.front()->setType(endRange->type);
        addLocalSymbol(LgsSymbol(rangeLoop->loopVars.front()));
    }
    visitStmtsBlock(rangeLoop->stmtsBlock);
}

void LgsSema::visitForeachLoop(LgsForeachLoop* foreachLoop) {
    auto iterExpr = foreachLoop->iterExpr;
    visitExpr(iterExpr);
    const auto iterable = iterExpr->type->asIterable();
    if (!iterable) {
        if (!iterExpr->type) return;
        addError(E10002, iterExpr->location, {iterExpr->asText()});
        return;
    }

    const bool unpacked = iterable->unpackLoopVarsTypes(foreachLoop);
    if (!unpacked) {
        addError(E10041, foreachLoop->iterExpr->location, {foreachLoop->iterExpr->asText(), foreachLoop->iterExpr->type->pname(), std::to_string(foreachLoop->loopVars.size())});
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
        const auto rt = stack.currentFunc()->funcType->rt;
        retExpr->castImplicitly(rt);
        validateExprType(returnStmt->expr, rt);
    }
    const auto rt = funcType->rt;
    if (rt->isVoid() && retExpr && retExpr->type && !retExpr->type->isVoid()) {
        addError(E10027, returnStmt->location, {retExpr->type->pname()});
    } else if (!rt->isVoid() && !retExpr) {
        addError(E10026, returnStmt->location, {funcType->name, rt->pname()});
    } else if (retExpr && retExpr->type && !rt->canCastTo(retExpr->type)) {
        addError(E10004, returnStmt->location, {funcType->name, rt->pname(), retExpr->type->pname()});
    }
}

void LgsSema::visitContinueStmt(const LgsContinue* continueStmt) {
    if (!stack.currentLoop()) {
        addError(E10038, continueStmt->location);
    }
}

void LgsSema::visitBreakStmt(const LgsBreak* breakStmt) {
    if (breakStmt->isBreakIf) {
        if (!stack.currentIfStmt()) addError(E10071, breakStmt->location);
    } else if (!stack.currentLoop() && breakStmt->tag == "") {
        addError(E10017, breakStmt->location);
    }
}

void LgsSema::visitCoroutine(const LgsCoroutine* coroutine) {
    const LgsFuncCall* fc = nullptr;
    if (coroutine->funcCall->name == "") { // Wrapped stmtsBlock
        visitStmtsBlock(coroutine->funcCall->func->stmtsBlock);
    } else if (coroutine->funcCall) {
        visitFuncCall(coroutine->funcCall);
        fc = coroutine->funcCall;
    } else if (coroutine->selection) {
        visitSelection(coroutine->selection);
        fc = coroutine->selection->asMethodCall();
    } else {
        assert(0);
    }

    const auto funcName = fc->func->funcType->getName() + LGS_CORO_SUFFIX;
    const auto coro = file->symbolTable.coroutines.find(funcName);
    if (coro != file->symbolTable.coroutines.end()) {
        coroutine->funcCall->func = coro->second;
    } else {
        const auto f = fc->func->clone();
        f->funcType->isCoroutine = true;
        coroutine->funcCall->func = f;
        file->symbolTable.coroutines[funcName] = f;
    }
}

void LgsSema::visitDeferStmt(const LgsDeferStmt* deferStmt) {
    if (deferStmt->funcCall->name == "") { // Wrapped stmtsBlock
        visitStmtsBlock(deferStmt->funcCall->func->stmtsBlock);
    } else if (deferStmt->selection) {
        visitSelection(deferStmt->selection);
    } else if (deferStmt->funcCall) {
        visitFuncCall(deferStmt->funcCall);
    } else {
        assert(0);
    }
    stack.currentFunc()->hasDefers = true;
}

void LgsSema::visitIOStmt(const LgsIOStmt* ioStmt) {
    visitVarDec(ioStmt->varDec);
    const auto expr = ioStmt->varDec->expr;
    const auto funcCall = expr->asFuncCall() ? expr->asFuncCall() : expr->asSelection()->asMethodCall();
    if (!funcCall->func->funcType->isIOMember) {
        addError(E10084, funcCall->location, {funcCall->asText()});
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
        else if (const auto matrixExpr = expr->asMatrixExpr()) visitMatrixExpr(matrixExpr);
        else if (const auto castExpr = expr->asCast()) visitCast(castExpr);
        else if (const auto json = expr->asJson()) visitJson(json);
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
    auto type = ltype->applyBinOp(rtype, binaryExpr->op);
    if (!type) {
        return addError(E10076, l->location, {binaryExpr->op.text, ltype->pname(), rtype->pname()});
    }
    if (const auto iter = type->asIterable()) visitExpr(iter->size);
    type = typeResolver.resolveType(type, file);
    binaryExpr->setType(type);
    binaryExpr->isMutable = l->isMutable || r->isMutable;
}

void LgsSema::visitTernaryExpr(LgsTernaryExpr* ternary) {
    auto condExpr = ternary->condExpr;
    auto thenExpr = ternary->thenExpr;
    auto elseExpr = ternary->elseExpr;
    visitExpr(condExpr);
    visitExpr(thenExpr);
    visitExpr(elseExpr);
    if (!condExpr->type->asBool()) {
        addError(E10092, ternary->location, {condExpr->asText(), condExpr->type->pname()});
    }
    if (!thenExpr->type->canCastTo(elseExpr->type)) {
        addError(E10021, ternary->location, {thenExpr->asText(), elseExpr->asText(), thenExpr->type->pname(), elseExpr->type->pname()});
    }
    ternary->setType(thenExpr->type);
}

void LgsSema::visitCast(LgsCast* cast) {
    visitExpr(cast->fromValue);
    if (!cast->fromValue->type) return;
    cast->toType = typeResolver.resolveType(cast->toType, file);
    cast->value = cast->fromValue->castExplicitly(cast->toType);
    if (!cast->value) {
        addError(E10018, cast->location, {cast->fromValue->asText(), cast->toType->pname()});
        return;
    }
    cast->setType(cast->value->type);
}

void LgsSema::visitArrayExpr(LgsArrayExpr* arrayExpr) {
    if (arrayExpr->elements.empty() && !arrayExpr->type) {
        return addError(E10049, arrayExpr->location, {arrayExpr->asText()});
    }
    for (auto element : arrayExpr->elements) {
        visitExpr(element);
    }
    if (!arrayExpr->type) {
        arrayExpr->type = new LgsDArray();
        visitDynamicArray(arrayExpr);
    } if (arrayExpr->type->asSet()) {
        visitDynamicArray(arrayExpr);
    } else if (arrayExpr->type->asSArray()) {
        visitStaticArray(arrayExpr);
    } else {
        assert(0);
    }
    const auto iter = arrayExpr->type->asIterable();
    if (!iter) return;
    for (const auto element : arrayExpr->elements) {
        if (element->type->canCastTo(iter->baseType)) continue;
        return addError(E10001, element->location, {iter->pname(), element->type->pname()});
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
    const auto iterable = arrayExpr->type->asIterable();
    if (!iterable->baseType && arrayExpr->elements.empty()) {
        return addError(E10049, arrayExpr->location, {arrayExpr->asText()});
    }
    if (!iterable->inferBaseType(arrayExpr->elements)) {
        return addError(E10095, arrayExpr->location);
    }
}

void LgsSema::visitHashMap(LgsHashMap* hashMap) {
    for (auto [key, value] : hashMap->elements) {
        visitExpr(key);
        visitExpr(value);
    }
    if (hashMap->type) return;
    if (hashMap->elements.empty()) {
        return addError(E10049, hashMap->location, {LgsMap::name});
    }
    const auto [key, value] = hashMap->elements.front();
    hashMap->setType(new LgsMap(key->type, value->type));
}

void LgsSema::visitVectorExpr(const LgsVectorExpr* vectorExpr) {
    const auto vec = vectorExpr->type->asVec();
    if (!vec->inferBaseType(vectorExpr->elements)) {
        return addError(E10095, vectorExpr->location);
    }
    auto sumDim = 0;
    for (auto arg : vectorExpr->elements) {
        visitExpr(arg);
        if (arg->type->isNumber()) {
            sumDim++;
        } else if (const auto otherVec = arg->type->asVec()) {
            sumDim += otherVec->vectorDim;
        } else {
            addError(E10073, vectorExpr->location, {arg->type->pname()});
            break;
        }
    }
    if (sumDim > vectorExpr->vecType->vectorDim) {
        addError(E10074, vectorExpr->location, {std::to_string(vectorExpr->vecType->vectorDim), std::to_string(sumDim)});
    }
}

void LgsSema::visitMatrixExpr(const LgsMatrixExpr* matrixExpr) {
    for (const auto element : matrixExpr->elements) {
        for (auto innerElement : element->elements) {
            visitExpr(innerElement);
            innerElement->castImplicitly(matrixExpr->matType->baseType);
        }
        const auto columnsInt = new LgsIntConst(&LGS_SIZE, matrixExpr->matType->columns);
        element->type = new LgsSArray(matrixExpr->matType->baseType, columnsInt);
    }
}

void LgsSema::visitVariable(LgsVariable* variable) {
    const auto symbol = getSymbol(variable->name, &variable->location);
    if (!symbol) return;
    variable->ref.symbolType = symbol->symbolType;
    switch (symbol->symbolType) {
    case VAR_DEC: {
        variable->ref.varDec = symbol->varDec;
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
        variable->isMutable = false;
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
        variable->isMutable = !symbol->field->isConst;
        variable->setType(symbol->field->type);
        if (symbol->field->isOwner) {
            variable->owner = symbol->field;
        }
        break;
    }
    default:
        assert(0);
    }
    assert(variable->ref.symbolType != UNKNOWN);
}

void LgsSema::visitSelection(LgsSelection* selection) {
    const auto exprs = selection->exprs;
    const auto firstExpr = exprs.front();
    visitFirstSelection(firstExpr);
    if (!firstExpr->type) return;
    if (const auto var = firstExpr->asVariable()) {
        if (var->ref.symbolType == OBJECT) {
            const auto typeExpr = new LgsTypeExpr(var->ref.object);
            freeExpr(firstExpr);
            selection->exprs[0] = typeExpr;
        }
    }

    if (!firstExpr->type) return;
    visitInnerSelections(selection);
    const auto lastExpr = selection->lastExpr();
    if (selection->hasNullables && !lastExpr->type->asNullable()) {
        lastExpr->setType(new LgsNullable(lastExpr->type));
    }
    selection->setType(lastExpr->type);
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
    const auto firstExpr = exprs.front();
    selection->hasNullables = firstExpr->type->asNullable();
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
        child->setType(field->type->clone());
        child->ref = LgsSymbol(field);
        if (field->isOwner && field->type->isHeapAlloc) {
            child->owner = field;
        }
        validateFieldVisibility(field, parentType);
    } else if (const auto method = parentType->getMethod(childName)) {
        child->setType(method->type);
        child->ref = LgsSymbol(method);
        validateMethodVisibility(method, parentType, method->location);
    } else {
        addError(E10005, child->location, {childName, parentType->pname()});
    }
}

void LgsSema::visitIterIndexSelection(LgsIterIndex* iterIndex, LgsType* parentType) {
    if (const auto innerIterIndex = iterIndex->baseExpr->asIterIndex()) {
        visitIterIndexSelection(innerIterIndex, parentType);
    } else {
        const auto baseExpr = iterIndex->baseExpr->asVariable();
        const auto field = parentType->getField(baseExpr->name);
        if (!field) {
            return addError(E10005, iterIndex->location, {baseExpr->name, parentType->pname()});
        }
        baseExpr->setType(field->type);
        baseExpr->ref = LgsSymbol(field);
    }
    visitIndex(iterIndex);
}

void LgsSema::visitMethodCall(LgsFuncCall* methodCall, LgsExpr* parent) {
    auto name = methodCall->name;
    const auto method = parent->type->getMethod(name);
    if (!method) {
        return addError(E10005, methodCall->location, {name, parent->type->pname()});
    }
    if (parent->asTypeExpr() && method->funcType->isMethod) {
        return addError(E10083, methodCall->location, {method->funcType->pname()});
    }

    methodCall->parentPtr = parent;
    if (method->funcType->isMethod) {
        methodCall->args.insert(methodCall->args.begin(), LgsFuncArg(LGS_SELF, parent, true));
    }
    visitFuncArgs(methodCall, method->funcType);
    if (methodCall->equals(method->funcType)) {
        methodCall->func = method;
        methodCall->setType(method->funcType->rt);
    } else {
        addError(E10034, methodCall->location, {parent->type->pname(), name, methodCall->asText(), method->asText()});
        return;
    }

    if (!validateMethodVisibility(method, parent->type, methodCall->location)) return;
    methodCall->isMock = stack.currentFunc()->isTest && parent->type->pname() == LgsTest::name && methodCall->name == "mock";
    if (methodCall->isMock) {
        const auto pair = std::make_pair(methodCall->args[0].expr, methodCall->args[1].expr);
        stack.currentFunc()->mocks.push_back(pair);
    }
}

void LgsSema::visitFuncCall(LgsFuncCall* funcCall) {
    const auto symbol = getSymbol(funcCall->name, &funcCall->location);
    if (!symbol) return;
    const auto ft = symbol->getType()->asFuncType();
    if (!ft) return addError(E10046, funcCall->location, {funcCall->name});

    visitFuncArgs(funcCall, ft);
    if (!funcCall->equals(ft)) {
        addError(E10015, funcCall->location, {funcCall->name, funcCall->asText(), ft->pname()});
        return;
    }
    if (symbol->symbolType != FUNC) {
        funcCall->ref = *symbol;
        funcCall->setType(ft->rt);
        return;
    }

    const auto func = symbol->func;
    if (!func->funcType->genericParams.empty()) {
        const auto funcName = funcCall->getGenericName();
        const auto generics = file->symbolTable.genericCalls.find(funcName);
        LgsFunc* genericFunc = nullptr;
        if (generics != file->symbolTable.genericCalls.end()) {
            genericFunc = generics->second;
        } else {
            genericFunc = createGenericFunc(funcCall, func);
            file->symbolTable.genericCalls[funcName] = genericFunc;
        }
        funcCall->func = genericFunc->clone();
        funcCall->setType(genericFunc->funcType->rt);
    } else {
        funcCall->func = func;
        funcCall->setType(ft->rt);
    }
}

void LgsSema::visitFuncArgs(LgsFuncCall* funcCall, LgsFuncType* ft) {
    if (funcCall->isNamed) {
        auto paramsByName = ft->getParamsByName();
        std::unordered_set<std::string> visited;
        for (auto arg : funcCall->args) {
            if (visited.contains(arg.name)) {
                addError(E10098, arg.expr->location, {arg.expr->asText()});
            }
            visited.insert(arg.name);
            if (!paramsByName.contains(arg.name)) {
                addError(E10094, arg.expr->location, {arg.expr->asText(), funcCall->name});
                continue;
            }
            const auto param = paramsByName[arg.name];
            arg.expr->castImplicitly(param->type);
            visitExpr(arg.expr);
            if (arg.name == "") {
                addError(E10096, funcCall->location);
                break;
            }
        }
    } else {
        for (size_t i = ft->isMethod; i < ft->params.size(); ++i) {
            if (i >= funcCall->args.size()) break;
            auto& arg = funcCall->args[i];
            const auto& param = ft->params[i];
            arg.expr->castImplicitly(param.type);
            visitExpr(arg.expr);
            if (arg.name != "") {
                addError(E10096, funcCall->location);
                break;
            }
        }
    }
}

void LgsSema::visitPrefixExpr(LgsPrefixExpr* prefixExpr) {
    auto baseExpr = prefixExpr->expr;
    visitExpr(baseExpr);
    switch (prefixExpr->op) {
    case MINUS_PREFIX: {
        if (!baseExpr->type->isNumber()) {
            addError(E10090, prefixExpr->location, {"-", baseExpr->type->pname()});
            return;
        }
        prefixExpr->setType(baseExpr->type);
        break;
    }
    case NOT_PREFIX: {
        if (!baseExpr->type->asBool()) {
            addError(E10091, prefixExpr->location, {baseExpr->type->pname()});
            return;
        }
        prefixExpr->setType(baseExpr->type);
        break;
    }
    case SQRT_PREFIX: {
        if (!baseExpr->type->isNumber()) {
            addError(E10090, prefixExpr->location, {"_/", baseExpr->type->pname()});
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
        return addError(E10050, postfixExpr->location, {type->pname()});
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
    typeExpr->setType(typeResolver.resolveType(typeExpr->type, file));
}

void LgsSema::visitJson(const LgsJson* json) {
    assert(0);
}

void LgsSema::visitInstance(LgsInstance* instance) {
    const auto objName = instance->name;
    const auto symbol = getSymbol(objName, &instance->location);
    if (!symbol) return;
    if (symbol->symbolType != OBJECT && symbol->symbolType != INTERFACE) {
        return addError(E10022, instance->location, {objName});
    }
    if (symbol->symbolType == INTERFACE) {
        return visitInterfaceInstance(instance, symbol->interface);
    }

    const auto obj = symbol->object;
    if (obj->singleton) {
        return addError(E10032, instance->location, {objName});
    }
    instance->setObject(obj->clone());

    // Args
    std::unordered_set<std::string> visited;
    for (auto& [argName, arg] : instance->args) {
        if (visited.contains(argName)) {
            addError(E10054, arg.expr->location, {argName});
        }
        visited.insert(argName);
        const auto field = instance->obj->getField(argName);
        if (!field) {
            addError(E10005, arg.expr->location, {argName, objName});
            continue;
        }
        if (!validateFieldVisibility(field, instance->obj)) continue;
        visitExpr(arg.expr);
        validateExprType(arg.expr, field->type);
        if (field->isOwner && field->type->isHeapAlloc) {
            field->expr->owner = field;
        }
    }

    // Missing required fields
    for (const auto& field : instance->obj->fields) {
        if (field->isConst && !instance->args.contains(field->name)) {
            addError(E10029, field->location, {field->name});
        }
    }
}

void LgsSema::visitInterfaceInstance(LgsInstance* instance, LgsInterface* interface) {
    instance->setObject(new LgsObject(interface->name));
    instance->obj->location = instance->location;
    instance->obj->implements.push_back(interface);
    auto isValid = true;
    for (auto& [name, arg] : instance->args) {
        auto expr = arg.expr;
        visitExpr(expr);
        const auto field = interface->getField(name);
        if (field) {
            const auto newField = new LgsField(*field);
            newField->expr = expr;
            instance->obj->addField(newField);
            continue;
        }
        const auto method = interface->getMethod(name);
        if (method) {
            const auto newMethod = expr->asFunc();
            newMethod->funcType->name = method->funcType->name;
            newMethod->funcType->params.insert(newMethod->funcType->params.begin(), LgsParam(interface, LGS_SELF));
            newMethod->funcType->params.front().isSelf = true;
            instance->obj->addMethod(newMethod);
            continue;
        }
        addError(E10005, expr->location, {name, interface->name});
        isValid = false;
    }
    if (isValid) {
        visitObject(instance->obj);
    }
}

void LgsSema::visitIterIndex(LgsIterIndex* iterIndex) {
    auto baseExpr = iterIndex->baseExpr;
    visitExpr(baseExpr);
    if (!baseExpr->type) return;
    const auto iterable = baseExpr->type->asIterable();
    if (!iterable) {
        return addError(E10002, iterIndex->location, {baseExpr->asText()});
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
            return addError(E10036, iterIndex->location, {iterIndex->asText(), exprFrom->type->pname()});
        }
        if (iterable->isStatic) {
            const auto index = exprFrom->getConstInt();
            const auto bounds = iterable->size->getConstInt();
            if (index && bounds && *index >= *bounds) {
                addError(E10048, iterIndex->location, {iterIndex->asText(), std::to_string(*bounds)});
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
        return addError(E10042, iterIndex->location, {iterIndex->asText(), baseExpr->type->pname()});
    }
    if (!exprFrom->type->canCastTo(iterable->getIndexType())) {
        return addError(E10036, iterIndex->location, {iterIndex->asText(), exprFrom->type->pname()});
    }
    if (!iterable->getIndexType()->canCastTo(exprTo->type)) {
        return addError(E10036, iterIndex->location, {iterIndex->asText(), exprTo->type->pname()});
    }
    if (iterable->isStatic) {
        const auto sizeFrom = exprFrom->getConstInt();
        const auto sizeTo = exprTo->getConstInt();
        if (!sizeFrom || !sizeTo) return;
        if (*sizeFrom > *sizeTo) {
            return addError(E10037, iterIndex->location);
        }
        const auto bounds = iterable->size->getConstInt();
        if (!bounds) return;
        if (*sizeFrom >= *bounds) {
            return addError(E10048, exprFrom->location, {std::to_string(*sizeFrom), std::to_string(*bounds - 1)});
        }
        if (*sizeTo >= *bounds) {
            return addError(E10048, exprTo->location, {std::to_string(*sizeTo), std::to_string(*bounds - 1)});
        }
    }
}

void LgsSema::visitLoopMetaVar(LgsMetaVar* metaVar) {
    const auto loop = stack.currentLoop();
    if (!loop) {
        return addError(E10060, metaVar->location);
    }

    const auto name = metaVar->asText();
    if (loop->asWhileLoop() || loop->asWhileLoop()) {
        return addError(E10061, metaVar->location, {name});
    }

    if (!loop->metaVars.contains(metaVar->varType)) {
        loop->metaVars[metaVar->varType] = metaVar;
    }
}

bool LgsSema::validateExprType(LgsExpr* expr, LgsType* type) {
    if (expr->asNull()) {
        const auto nullable = type->asNullable();
        // null must have a type
        if (nullable && !nullable->baseType) {
            addError(E10024, expr->location);
            return false;
        }
        // type must be nullable
        if (!nullable) {
            addError(E10023, expr->location, {type->pname()});
            return false;
        }
    }
    if (!type || !expr->type || type->isUnknown() || expr->type->isUnknown()) return false;
    if (!expr->type->canCastTo(type)) {
        addError(E10001, expr->location, {type->pname(), expr->type->pname()});
        return false;
    }
    return true;
}

bool LgsSema::validateTypeName(const std::string& typeName, const LgsLocation* location) {
    if (islower(typeName[0])) {
        errHandler.addError(E10033, location, file->path, {typeName});
        return false;
    }
    return true;
}

bool LgsSema::validateLocalName(const std::string& typeName, const LgsLocation* location) {
    if (isupper(typeName[0])) {
        errHandler.addError(E10099, location, file->path, {typeName});
        return false;
    }
    return true;
}

void LgsSema::validateObjImplements(LgsObject* obj, const std::vector<LgsType*>& interfaces) {
    std::unordered_set<std::string> interfacesNames;
    std::unordered_set<std::string> seenNames;
    for (const auto implementsInterface : interfaces) {
        const auto interface = implementsInterface->asInterface();
        if (!interface) {
            addError(E10025, implementsInterface->location, {implementsInterface->pname()});
            continue;
        }

        // Fields
        std::vector<LgsField*> missingFields;
        for (const auto& interfaceField : interface->fields) {
            const auto objField = obj->getField(interfaceField->name);
            if (objField && objField->type->equals(interfaceField->type)) {
                if (!seenNames.insert(interfaceField->name).second) {
                    addError(E10058, objField->location, {objField->name});
                }
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
                auto objMethodName = objMethod->first;
                if (!seenNames.insert(objMethodName).second) {
                    addError(E10064, objMethod->second->location, {objMethodName});
                }
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
            addError(E10016, obj->location, {obj->pname(), interface->name, getMissingImplementsStr(missingFields, missingMethods)});
        }
    }
}

void LgsSema::validateIndex(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto exprFrom = iterIndex->index.from;
    const auto iterable = baseExpr->type->asIterable();
    if (!exprFrom->type->canCastTo(iterable->getIndexType())) {
        return addError(E10036, iterIndex->location, {iterIndex->asText(), exprFrom->type->pname()});
    }
    if (const auto sArr = iterable->asSArray()) {
        const auto i = exprFrom->getConstInt();
        const auto bounds = sArr->size->getConstInt();
        if (!i || !bounds) return;
        if (*i >= *bounds) {
            return addError(E10048, iterIndex->location, {iterIndex->asText(), std::to_string(*bounds)});
        }
    }
}

bool LgsSema::validateFieldVisibility(LgsField* field, LgsType* parent) {
    assert(parent);
    if (parent->asVec()) return true;
    if (parent->asObject() && parent->asObject()->singleton) return true;
    if (!field || field->isVirtual) return false;
    if (stack.currentFunc()->isTest) return true;
    if (!field->isPublic && file->path != *field->location.filepath) {
        if (parent) addError(E10030, field->location, {field->name, parent->pname()});
        return false;
    }
    return true;
}

bool LgsSema::validateMethodVisibility(const LgsFunc* method, LgsType* parent, const LgsLocation& location) {
    if (parent && parent->asObject() && parent->asObject()->singleton) return true;
    if (!method || method->funcType->isVirtual) return false;
    if (!method->funcType->isPublic && file->path != *method->location.filepath && !stack.currentFunc()->isTest) {
        addError(E10031, location, {method->funcType->name, method->funcType->parentName});
        return false;
    }
    return true;
}

bool LgsSema::validateVecElements(const LgsVariable* fieldVar, LgsVec* vec) {
    const auto fieldName = fieldVar->name;
    const auto dim = vec->vectorDim;
    if (fieldName.empty() || fieldName.size() > 4) {
        addError(E10069, fieldVar->location, {vec->pname()});
        return false;
    }

    const auto expectedSet = LgsVec::getSwizzleSet(fieldName[0]);
    if (expectedSet < 0) {
        addError(E10070, fieldVar->location, {fieldName, vec->pname()});
        return false;
    }

    for (const char c : fieldName) {
        if (LgsVec::getSwizzleSet(c) != expectedSet) {
            addError(E10070, fieldVar->location, {fieldName, vec->pname()});
            return false;
        }
        const auto componentIndex = LgsVec::getComponentIndex(c);
        if (componentIndex >= dim) {
            addError(E10070, fieldVar->location, {fieldName, vec->pname()});
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
        if (!names.insert(name).second) {
            addError(E10056, type->location, {type->pname(), name});
            break;
        }
    }
    for (const auto& [name, func] : type->methods) {
        if (!names.insert(name).second) {
            addError(E10056, type->location, {type->pname(), name});
            break;
        }
    }
}

bool LgsSema::validateBlockControlFlow(const LgsStmtsBlock* stmtBlock, const LgsFunc* func) {
    assert(func->funcType->rt);
    if (func->funcType->rt->isVoid()) return true;
    if (!stmtBlock) return true;
    if (stmtBlock->returnStmt) return true;
    auto isValid = false;
    for (const auto stmt : stmtBlock->stmts) {
        if (stmt.type == LgsObjOrStmt::Type::Object) continue;
        if (const auto ifStmt = stmt.stmt->asIfStmt()) {
            isValid = validateBlockControlFlow(ifStmt->ifBlock, func);
            for (const auto [_, elseIfStmt] : ifStmt->elseIfs) {
                isValid = isValid && validateBlockControlFlow(elseIfStmt, func);
            }
            isValid = isValid && validateBlockControlFlow(ifStmt->elseBlock, func);
        } else if (const auto loop = stmt.stmt->asLoop()) {
            isValid = isValid && validateBlockControlFlow(loop->stmtsBlock, func);
        } else if (const auto switch_ = stmt.stmt->asIfStmt()) {
            for (const auto [_, patternsStmtBlock] : switch_->elseIfs) {
                isValid = isValid && validateBlockControlFlow(patternsStmtBlock, func);
            }
            isValid = isValid && validateBlockControlFlow(switch_->elseBlock, func);
        }
    }
    return isValid;
}

void LgsSema::resolveImports() const {
    for (auto& [name, app] : file->symbolTable.imports) {
        const auto it = globals.table.imports.find(name);
        if (it == globals.table.imports.end()) continue;
        app = it->second;
    }
}

void LgsSema::mergeRTTypes() {
    std::lock_guard lock(mtx);
    auto& thisRegistry = typeResolver.rtTypesRegistry;
    auto& globalsRegistry = globals.rtTypes;
    globalsRegistry.insert(globalsRegistry.end(), thisRegistry.begin(), thisRegistry.end());
    for (auto [name, count] : refCount) {
        const auto symbol = globals.table.getSymbol(name);
        if (!symbol) continue;
        symbol->refCount += count;
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

void LgsSema::addLocalSymbol(const LgsSymbol& newSymbol) {
    auto symbolName = *newSymbol.name;
    const auto symbol = globals.table.getSymbol(symbolName);
    if (symbol && symbol->isBuiltin) {
        return addError(E10053, *newSymbol.location, {symbolName});
    }
    if (file->symbolTable.getSymbol(symbolName)) {
        return addError(E10011, *newSymbol.location, {symbolName});
    }
    stack.getSymbolTable().addSymbol(newSymbol, &errHandler);
}

LgsSymbol* LgsSema::getSymbol(const std::string& name, const LgsLocation* location) {
    if (const auto globalSymbol = globals.table.getSymbol(name)) {
        if (!globalSymbol->isBuiltin) refCount[*globalSymbol->name]++;
        return globalSymbol;
    }
    if (const auto fileSymbol = file->symbolTable.getSymbol(name)) {
        return fileSymbol;
    }
    for (auto [_, app] : file->symbolTable.imports) {
        if (const auto s = app->globals.table.getSymbol(name)) {
            return s;
        }
    }
    if (const auto symbol = stack.getSymbolTable().getSymbol(name)) {
        return symbol;
    }
    addError(E10006, *location, {name});
    return nullptr;
}

LgsFunc* LgsSema::createGenericFunc(LgsFuncCall* funcCall, const LgsFunc* originalFunc) {
    const auto newFunc = new LgsFunc(originalFunc->funcType->name, nullptr);
    const auto originalFT = originalFunc->funcType;
    newFunc->location = originalFunc->location;
    newFunc->funcType->location = originalFT->location;

    // Params
    std::unordered_map<std::string, LgsType*> genericArgs;
    for (size_t i = 0; i < originalFT->params.size(); ++i) {
        const auto& param = originalFT->params[i];
        const auto& arg = funcCall->args[i];
        if (!param.type->asGeneric()) continue;
        const auto paramTypeName = param.type->getName();
        if (genericArgs.contains(paramTypeName)) continue;
        if (originalFT->rt->asGeneric()) {
            const auto newType = arg.expr->type->clone();
            genericArgs[paramTypeName] = newType;
            newFunc->funcType->params.emplace_back(newType, param.name);
        } else {
            newFunc->funcType->params.emplace_back(param.type->clone(), param.name);
        }
    }

    // Set generic IRName
    newFunc->funcType->IRName = newFunc->funcType->getName();
    for (const auto& t : std::views::values(genericArgs)) {
        newFunc->funcType->IRName += "_" + t->getName();
    }

    // Return type
    if (originalFT->rt->asGeneric()) {
        newFunc->funcType->rt = genericArgs[originalFT->rt->getName()];
    } else {
        newFunc->funcType->rt = originalFT->rt->clone();
    }

    newFunc->stmtsBlock = originalFunc->stmtsBlock->clone();
    visitFunc(newFunc);
    funcCall->func = newFunc;
    return newFunc;
}

static std::string getMissingImplementsStr(const std::vector<LgsField*>& fields, const std::vector<LgsFunc*>& methods) {
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

void LgsSema::addError(const LgsBaseMsg& lgsErr, const LgsLocation& location, const std::vector<std::string>& args) {
    errHandler.addError(lgsErr, &location, file->path, args);
}
