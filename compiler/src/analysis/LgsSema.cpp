#include "analysis/LgsSema.h"

#include "../../include/symbols/exprs/constants/LgsComplexConst.h"
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
#include "exprs/LgsMetaSelection.h"
#include "exprs/LgsNullableExpr.h"
#include "loops/LgsInfiniteLoop.h"
#include "loops/LgsWhileLoop.h"
#include "stmts/LgsBreak.h"
#include "stmts/LgsContinue.h"
#include "stmts/LgsDeferStmt.h"
#include "stmts/LgsVarDec.h"
#include "types/iterables/LgsDArray.h"
#include "types/LgsInterface.h"
#include "loops/LgsForeachLoop.h"
#include "loops/LgsForLoop.h"
#include "loops/LgsMetaVar.h"
#include "loops/LgsRangeLoop.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsIOPair.h"
#include "stmts/LgsIOStmt.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsSwitch.h"
#include "tools/LgsFormatter.h"
#include "types/primitives/LgsDouble.h"
#include "types/iterables/LgsVariadic.h"
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
        } else {
            visitFunc(func);
        }
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
    validateTypeName(obj->name, obj->location);
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
    validateTypeName(interface->name, interface->location);
    for (const auto& [_, method] : interface->methods) {
        visitFunc(method);
    }
}

void LgsSema::visitEnum(const LgsEnum* enum_) {
    validateTypeName(enum_->name, enum_->location);
}

void LgsSema::visitTestFile(const LgsTestFile* testFile) {
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
        addError(E10013, field->location, {field->name});
    }
    if (!field->type->isHeapAlloc && field->isOwner) {
        field->isOwner = false;
    }
    addRTType(field->type);
}
void LgsSema::visitFuncHeader(LgsFuncType* ft) {
    if (ft->name != "") validateLocalName(ft->name, ft->location);
    if (!ft->genericTypes.empty()) return;
    auto defaultParamsStarted = false;
    for (auto& param : ft->params) {
        visitParam(&param);
        if (defaultParamsStarted && !param.expr) {
            addError(E10028, param.location);
            break;
        }
        defaultParamsStarted = !!param.expr;
    }
}

void LgsSema::visitFunc(LgsFunc* func) {
    const auto ft = func->funcType;
    visitFuncHeader(ft);
    stack.enterScope(func);
    visitStmtsBlock(func->stmtsBlock);
    if (ft->isVariadic && ft->hasDefaults) {
        addError(E10043, func->location);
    }
    if (!validateBlockControlFlow(func->stmtsBlock, func)) {
        addError(E10055, func->location, {func->asText()});
    }
    stack.exitScope();
}

void LgsSema::visitLambda(LgsFunc* lambda) {
    const auto ft = lambda->funcType;
    typeResolver.resolveFuncType(ft);
    visitFuncHeader(ft);
    stack.enterScope(lambda);
    visitStmtsBlock(lambda->stmtsBlock);
    if (ft->isVariadic && ft->hasDefaults) {
        addError(E10043, lambda->location);
    }
    if (!validateBlockControlFlow(lambda->stmtsBlock, lambda)) {
        addError(E10055, lambda->location, {lambda->asText()});
    }
    stack.exitScope();
    assert(lambda->funcType->rt);
}

void LgsSema::visitMainFunc(LgsMainFunc* mainFunc) {
    stack.enterScope(mainFunc);
    const auto ft = mainFunc->funcType;
    const auto paramSize = ft->params.size();
    if (paramSize > 1) {
        return addError(E10039, mainFunc->location);
    }
    if (paramSize == 1) {
        auto& firstParam = ft->params.front();
        const auto iterable = firstParam.type->asIterable();
        if (!iterable || !iterable->baseType->asStr()) {
            return addError(E10039, mainFunc->location);
        }
        // Replaces dyn array to static array
        freeType(firstParam.type);
        const auto sArray = new LgsSArray(new LgsStr(), new LgsIntConst(0));
        firstParam.setType(sArray);
        firstParam.expr = new LgsArrayExpr(sArray);
    }
    visitStmtsBlock(mainFunc->stmtsBlock);
    stack.exitScope();
}

void LgsSema::visitParam(LgsParam* param) {
    validateLocalName(param->name, param->location);
    if (param->isVariadic) {
        if (param->expr) {
            addError(E10045, param->location);
        } else {
            param->type = new LgsVariadic(param->type);
        }
    } else if (param->expr) {
        castExprImplicitly(param->expr, param->type);
        visitExpr(param->expr);
        validateExprType(param->expr, param->type);
    }
    addLocalSymbol(LgsSymbol(param));
    addRTType(param->type);
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

void LgsSema::visitStmt(LgsStmtWrapper& stmt) {
    if (const auto pattern = stmt.stmt->asSwitch()) visitSwitch(pattern);
    else if (const auto ifStmt = stmt.stmt->asIfStmt()) visitIfStmt(ifStmt);
    else if (const auto varDec = stmt.stmt->asVarDec()) visitVarDec(varDec);
    else if (const auto coroutine = stmt.stmt->asCoroutine()) visitCoroutine(coroutine);
    else if (const auto deferStmt = stmt.stmt->asDefer()) visitDeferStmt(deferStmt);
    else if (const auto assignment = stmt.stmt->asAssignment()) visitAssignment(assignment);
    else if (const auto returnStmt = stmt.stmt->asReturn()) visitReturnStmt(returnStmt);
    else if (const auto continueStmt = stmt.stmt->asContinue()) visitContinueStmt(continueStmt);
    else if (const auto ioStmt = stmt.stmt->asIOStmt()) visitIOStmt(ioStmt);
    else if (const auto breakStmt = stmt.stmt->asBreak()) visitBreakStmt(breakStmt);
    else if (stmt.stmt->asLoop()) {
        replaceForLoop(stmt);
        visitLoop(stmt.stmt->asLoop());
    }
    else assert(0);
}

void LgsSema::visitStmtsBlock(LgsStmtsBlock* stmtsBlock) {
    if (!stmtsBlock || stmtsBlock->stmts.empty()) return;

    // Check if it's lambda with one expr line and replace with return stmt
    auto& firstStmt = stmtsBlock->stmts.front();
    const auto& ft = stack.currentFunc()->funcType;
    const auto isExpr = firstStmt.wrapperType == LgsStmtWrapper::WrapperType::Expr;
    if (isExpr && stmtsBlock->isSingleLine && ft->isLambda && !ft->rt) {
        visitExpr(firstStmt.expr);
        if (firstStmt.expr->type->isVoid()) return;
        ft->rt = firstStmt.expr->type;
        firstStmt.stmt = new LgsReturn(firstStmt.expr);
        firstStmt.wrapperType = LgsStmtWrapper::WrapperType::Stmt;
        return;
    }

    for (auto& stmt : stmtsBlock->stmts) {
        switch (stmt.wrapperType) {
        case LgsStmtWrapper::WrapperType::Object:
            visitObject(stmt.obj);
            addLocalSymbol(LgsSymbol(stmt.obj));
            break;
        case LgsStmtWrapper::WrapperType::Stmt:
            visitStmt(stmt);
            break;
        case LgsStmtWrapper::WrapperType::Expr:
            visitExpr(stmt.expr);
            break;
        }
    }
    if (stmtsBlock->stmts.empty()) return;

    // Check unreachable code
    const auto lastStmt = stmtsBlock->stmts[stmtsBlock->stmts.size() - 1];
    for (size_t i = 0; i < stmtsBlock->stmts.size() - 1; ++i) {
        if (stmtsBlock->stmts[i].isTerminator()) {
            return addError(E10059, lastStmt.stmt->location);
        }
    }
}

void LgsSema::replaceForLoop(LgsStmtWrapper& stmt) {
    const auto rangeLoop = stmt.stmt->asLoop()->asRangeLoop();
    if (!rangeLoop) return;
    visitExpr(rangeLoop->endRange);
    if (rangeLoop->endRange->type && rangeLoop->endRange->type->asIterable()) {
        const auto foreach = new LgsForeachLoop(rangeLoop->endRange);
        foreach->stmtsBlock = rangeLoop->stmtsBlock;
        rangeLoop->stmtsBlock = nullptr;
        rangeLoop->endRange = nullptr;
        delete rangeLoop;
        stmt.stmt = foreach;
    }
}

void LgsSema::visitVarDec(LgsVarDec* varDec) {
    validateLocalName(varDec->name, varDec->location);
    if (const auto iter = varDec->type->asIterable()) visitExpr(iter->size);

    if (varDec->expr && varDec->type) {
        if (varDec->isOwner) {
            varDec->expr->owner = varDec;
        }
        typeResolver.resolveType(varDec->type);
        castExprImplicitly(varDec->expr, varDec->type);
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
        typeResolver.resolveType(varDec->type);
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
        addError(E10109, varDec->location);
    }
    addLocalSymbol(LgsSymbol(varDec));
    addRTType(varDec->type);
}

void LgsSema::visitAssignment(LgsAssignment* assignment) {
    const auto l = assignment->lValue;
    auto& r = assignment->rValue;
    visitExpr(r);
    if (const auto iterIndex = l->asIterIndex()) {
        visitIterIndex(iterIndex);
    } else if (const auto variable = l->asVariable()) {
        visitVariable(variable);
    } else if (const auto selection = l->asSelection()) {
        visitSelection(selection);
    } else if (const auto nullableExpr = l->asNullableExpr()) {
        visitNullableExpr(nullableExpr);
    } else {
        assert(0);
    }

    r->castImplicitly(l->type);
    if (!l->type || !r->type) return;
    if (!validateExprType(r, l->type)) return;

    auto canAssign = false;
    if (l->asIterIndex() || l->asVariable() || l->asNullableExpr()) {
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
        return addError(E10012, l->location, {l->asText(), assignment->assignmentType.text, r->type->pname()});
    }
}

void LgsSema::visitIfStmt(LgsIfStmt* ifStmt) {
    if (ifStmt->ifBlock->isMacro) return visitMacroIf(ifStmt);
    stack.enterScope(ifStmt);
    auto ifCond = ifStmt->ifCond;
    visitExpr(ifCond);
    if (ifCond->type && !ifCond->type->asBool()) {
        addError(E10092, ifCond->location, {ifCond->type->pname()});
    }
    visitStmtsBlock(ifStmt->ifBlock);
    stack.exitScope();
    for (auto& [expr, block] : ifStmt->elseIfs) {
        stack.enterScope(ifStmt);
        visitExpr(expr);
        if (expr->type && !expr->type->asBool()) {
            addError(E10092, expr->location, {expr->type->pname()});
        }
        visitStmtsBlock(block);
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
    if (!constValue.has_value()) {
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
        if (!constValue.has_value()) {
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

void LgsSema::visitLoop(LgsForLoop* loopStmt) {
    stack.enterScope(loopStmt);
    if (const auto rangeLoop = loopStmt->asRangeLoop()) {
        if (rangeLoop->endRange->type && rangeLoop->endRange->type->asIterable()) {
            const auto foreach = new LgsForeachLoop(rangeLoop->endRange);
            foreach->stmtsBlock = rangeLoop->stmtsBlock;
            rangeLoop->stmtsBlock = nullptr;
            rangeLoop->endRange = nullptr;
            delete rangeLoop;
            visitForeachLoop(foreach);
        } else {
            visitRangeLoop(rangeLoop);
        }
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
    // endRange is already visited at replaceForLoops()
    const auto endRange = rangeLoop->endRange;
    assert(endRange);
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

    if (stack.getInnermostForeachLoop() == foreachLoop && foreachLoop->loopVars.size() == 0) {
        auto varDec = new LgsVarDec("for.element", nullptr);
        varDec->type = iterable->baseType;
        foreachLoop->loopVars.emplace_back(varDec);
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

void LgsSema::visitWhileLoop(LgsWhileLoop* whileLoop) {
    visitExpr(whileLoop->condExpr);
    const auto condType = whileLoop->condExpr->type;
    if (!condType->asBool()) {
        addError(E10066, whileLoop->location, {whileLoop->condExpr->asText(), condType->pname()});
    }
    visitStmtsBlock(whileLoop->stmtsBlock);
}

void LgsSema::visitReturnStmt(const LgsReturn* returnStmt) {
    const auto currentFunc = stack.currentFunc();
    const auto ft = currentFunc->funcType;
    auto retExpr = returnStmt->expr;
    if (retExpr) {
        castExprImplicitly(retExpr, ft->rt);
        visitExpr(retExpr);
        validateExprType(returnStmt->expr, ft->rt);
        currentFunc->returnStmts.push_back(returnStmt);
    }
    const auto rt = ft->rt;
    if (!rt && ft->isLambda) return;
    if (rt->isVoid() && retExpr && retExpr->type && !retExpr->type->isVoid()) {
        addError(E10027, returnStmt->location, {retExpr->type->pname()});
    } else if (!rt->isVoid() && !retExpr) {
        addError(E10026, returnStmt->location, {ft->name, rt->pname()});
    } else if (retExpr && retExpr->type && !rt->canCastTo(retExpr->type)) {
        addError(E10004, returnStmt->location, {ft->name, rt->pname(), retExpr->type->pname()});
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
    LgsFuncCall* fc = nullptr;
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
        coroutine->funcCall->coroutine = coro->second;
    } else {
        createCoroutineFunc(fc);
        file->symbolTable.coroutines[funcName] = fc->coroutine;
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
        else if (const auto complexConst = expr->asComplexConst()) visitComplexConst(complexConst);
        else if (const auto selection = expr->asSelection()) visitSelection(selection);
        else if (const auto metaSelection = expr->asMetaSelection()) visitMetaSelection(metaSelection);
        else if (const auto arrayExpr = expr->asArrayExpr()) visitArrayExpr(arrayExpr);
        else if (const auto hashMap = expr->asHashMap()) visitHashMap(hashMap);
        else if (const auto iterIndex = expr->asIterIndex()) visitIterIndex(iterIndex);
        else if (const auto postfixExpr = expr->asPostfixExpr()) visitPostfixExpr(postfixExpr);
        else if (const auto prefixExpr = expr->asPrefixExpr()) visitPrefixExpr(prefixExpr);
        else if (const auto forVar = expr->asLoopMetaVar()) visitLoopMetaVar(forVar);
        else if (const auto vecExpr = expr->asVectorExpr()) visitVectorExpr(vecExpr);
        else if (const auto matrixExpr = expr->asMatrixExpr()) visitMatrixExpr(matrixExpr);
        else if (const auto nullableExpr = expr->asNullableExpr()) visitNullableExpr(nullableExpr);
        else if (const auto castExpr = expr->asCast()) visitCast(castExpr);
        else if (const auto json = expr->asJson()) visitJson(json);
        visitUnwrap(expr);
    }
    addRTType(expr->type);
}

void LgsSema::visitBinaryExpr(LgsBinaryExpr* binaryExpr) {
    auto& l = binaryExpr->left;
    auto& r = binaryExpr->right;
    l->isReturnExpr = binaryExpr->isReturnExpr;
    r->isReturnExpr = binaryExpr->isReturnExpr;
    visitExpr(l);
    visitExpr(r);
    const auto ltype = l->type;
    const auto rtype = r->type;
    if (!ltype || !rtype) return;
    LgsType* type = nullptr;
    if (binaryExpr->op.opType == IN) {
        type = rtype->applyBinOp(ltype, binaryExpr->op);
    } else {
        type = ltype->applyBinOp(rtype, binaryExpr->op);
    }
    if (!type) {
        return addError(E10076, l->location, {binaryExpr->op.text, ltype->pname(), rtype->pname()});
    }
    if (const auto iter = type->asIterable()) visitExpr(iter->size);
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
    if (!thenExpr->type->canCastTo(elseExpr->type)) {
        addError(E10021, ternary->location, {thenExpr->asText(), elseExpr->asText(), thenExpr->type->pname(), elseExpr->type->pname()});
    }
    ternary->setType(thenExpr->type);
}

void LgsSema::visitCast(LgsCast* cast) {
    visitExpr(cast->fromValue);
    if (!cast->fromValue->type) return;
    typeResolver.resolveType(cast->toType);
    cast->value = cast->fromValue->castExplicitly(cast->toType);
    if (!cast->value) {
        addError(E10018, cast->location, {cast->fromValue->asText(), cast->toType->pname()});
        return;
    }
    cast->setType(cast->value->type);
}

void LgsSema::visitNullableExpr(LgsNullableExpr* nullableExpr) {
    if (nullableExpr->isNull) return;
    visitExpr(nullableExpr->baseExpr);
    if (nullableExpr->type) return;
    nullableExpr->type = new LgsNullable(nullableExpr->baseExpr->type);
}

void LgsSema::visitUnwrap(LgsExpr* expr) {
    if (!expr->type || !expr->hasUnwrapSuffix) return;
    if (!expr->type->asNullable()) {
        addError(E10113, expr->location, {expr->type->pname()});
        return;
    }
    const auto nullable = expr->type->asNullable();
    expr->type = nullable->baseType;
}

void LgsSema::visitArrayExpr(LgsArrayExpr* arrayExpr) {
    if (arrayExpr->elements.empty() && !arrayExpr->type) {
        return addError(E10049, arrayExpr->location, {arrayExpr->asText()});
    }
    for (auto element : arrayExpr->elements) {
        visitExpr(element);
    }
    if (!arrayExpr->type) {
        arrayExpr->setType(new LgsDArray());
        visitDynamicArray(arrayExpr);
    } else if (arrayExpr->type->asDArray() || arrayExpr->type->asSet()) {
        visitDynamicArray(arrayExpr);
    } else if (arrayExpr->type->asSArray()) {
        visitStaticArray(arrayExpr);
    } else {
        return;
    }
    const auto iterable = arrayExpr->type->asIterable();
    if (!iterable) return;
    for (const auto element : arrayExpr->elements) {
        if (iterable->baseType && element->type->canCastTo(iterable->baseType)) continue;
        return addError(E10111, element->location, {iterable->baseType->pname(), element->type->pname()});
    }
}

void LgsSema::visitStaticArray(const LgsArrayExpr* arrayExpr) {
    const auto sArr = arrayExpr->type->asSArray();
    const auto size = sArr->size->getConstInt();
    if (!size.has_value()) {
        addError(E10114, arrayExpr->location);
    } else if (size.value() < static_cast<int64_t>(arrayExpr->elements.size())) {
        addError(E10105, arrayExpr->location, {std::to_string(*size)});
    }
    for (auto element : arrayExpr->elements) {
        visitExpr(element);
    }
}

void LgsSema::visitDynamicArray(LgsArrayExpr* arrayExpr) {
    const auto dArr = arrayExpr->type->asDArray();
    if (!dArr->baseType && arrayExpr->elements.empty()) {
        return addError(E10049, arrayExpr->location, {arrayExpr->asText()});
    }
    if (!dArr->inferBaseType(arrayExpr->elements)) {
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

void LgsSema::visitVectorExpr(LgsVectorExpr* vectorExpr) {
    const auto vec = vectorExpr->type->asVec();
    size_t sumDim = 0;
    for (auto arg : vectorExpr->elements) {
        visitExpr(arg);
        if (arg->type->isNumber()) {
            sumDim++;
        } else if (const auto otherVec = arg->type->asVec()) {
            sumDim += otherVec->dimVec;
        } else {
            addError(E10073, vectorExpr->location);
            break;
        }
    }
    if (!vec->inferBaseType(vectorExpr->elements)) {
        return addError(E10095, vectorExpr->location);
    }
    if (sumDim > vectorExpr->vecType->dimVec) {
        addError(E10074, vectorExpr->location, {vec->pname(), std::to_string(sumDim)});
    }
    for (size_t i = 0; i < vectorExpr->elements.size(); ++i) {
        auto& arg = vectorExpr->elements[i];
        if (arg->type->equals(vec->baseType)) continue;
        const auto castArg = arg->castExplicitly(vec->baseType);
        if (castArg != arg) freeExpr(arg);
        arg = castArg;
    }
}

void LgsSema::visitMatrixExpr(const LgsMatrixExpr* matrixExpr) {
    if (matrixExpr->elements.size() != matrixExpr->matType->rows) {
        addError(E10103, matrixExpr->location, {matrixExpr->matType->pname(), std::to_string(matrixExpr->elements.size())});
        return;
    }
    for (const auto vector : matrixExpr->elements) {
        if (vector->elements.size() != matrixExpr->matType->columns) {
            addError(E10104, matrixExpr->location, {matrixExpr->matType->pname(), std::to_string(vector->elements.size())});
            return;
        }
        for (auto innerElement : vector->elements) {
            visitExpr(innerElement);
            castExprImplicitly(innerElement, matrixExpr->matType->baseType);
        }
        const auto columnsInt = new LgsIntConst(&LGS_SIZE, matrixExpr->matType->columns);
        vector->setType(new LgsSArray(matrixExpr->matType->baseType, columnsInt));
    }
}

void LgsSema::visitVariable(LgsVariable* variable) {
    const auto symbol = getSymbol(variable->name);
    if (!symbol) return addError(E10006, variable->location, {variable->name});
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
        if (symbol->param->isOwner) {
            variable->owner = symbol->param;
        }
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
    visitFirstSelection(selection);
    const auto firstExpr = exprs.front();
    if (!firstExpr->type) return;
    if (const auto var = firstExpr->asVariable()) {
        if (var->ref.symbolType == OBJECT) {
            const auto typeExpr = new LgsTypeExpr(var->ref.object);
            freeExpr(firstExpr);
            selection->exprs[0] = typeExpr;
        }
    }
    visitInnerSelections(selection);
    const auto lastExpr = selection->lastExpr();
    selection->setType(lastExpr->type);
    selection->owner = lastExpr->owner;
}

void LgsSema::visitFirstSelection(LgsSelection* selection) {
    auto& firstExpr = selection->exprs.front();
    visitExpr(firstExpr);
    if (!firstExpr->asNullableExpr() && firstExpr->type->asNullable()) {
        wrapInNullable(firstExpr, firstExpr->type->asNullable());
        selection->hasNullables = true;
    }
}

void LgsSema::visitInnerSelections(LgsSelection* selection) {
    auto& exprs = selection->exprs;
    for (size_t i = 0; i < exprs.size() - 1; ++i) {
        const auto parentExpr = exprs[i];
        auto& childExpr = exprs[i + 1];
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
        // Only the parts that comes after the first nullable encounter
        // will be wrapped in nullable
        selection->hasNullables = selection->hasNullables || childExpr->type->asNullable();
        if (selection->hasNullables) {
            assert(!childExpr->asNullableExpr());
            if (childExpr->type->asNullable()) {
                wrapInNullable(childExpr, childExpr->type->asNullable());
            } else {
                wrapInNullable(childExpr, new LgsNullable(childExpr->type));
            }
        }
    }
}

void LgsSema::visitFieldSelection(LgsVariable* child, LgsType* parentType) {
    if (!parentType) return;
    if (parentType->asVec() && !validateVecElements(child, parentType->asVec())) return;
    auto childName = child->name;
    if (const auto field = parentType->getField(childName)) {
        child->setType(field->type);
        child->ref = LgsSymbol(field);
        validateFieldVisibility(field, parentType, child->location);
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

void LgsSema::visitMetaSelection(LgsMetaSelection* metaSelection) {
    visitExpr(metaSelection->baseExpr);
    const auto obj = metaSelection->baseExpr->type->asObject();
    if (const auto methodCall = metaSelection->child->asFuncCall()) {
        if (!obj->metaMethods.contains(methodCall->name)) {
            return addError(E10005, metaSelection->location, {methodCall->name, obj->pname()});
        }
        const auto method = obj->metaMethods[methodCall->name];
        if (!visitFuncArgs(methodCall, method->funcType)) return;
        if (methodCall->equals(method->funcType)) {
            methodCall->func = method;
            methodCall->setType(method->funcType->rt);
        } else {
            addError(E10034, methodCall->location, {obj->name, methodCall->name, methodCall->asText(), method->asText()});
        }
        if (method->funcType->isMethod) {
            methodCall->args.insert(methodCall->args.begin(), LgsFuncArg(metaSelection->baseExpr, LGS_SELF, true));
        }
    }
}

LgsFunc* clone(const LgsFunc* func, const LgsFuncCall* funcCall) {
    const auto funcType = func->funcType;
    const auto newFuncType = new LgsFuncType(*funcType);
    newFuncType->params.clear();
    newFuncType->genericTypes.clear();

    std::unordered_map<std::string, LgsType*> replacements;
    for (size_t i = 0; i < funcCall->args.size(); ++i) {
        const auto& param = funcType->params[i];
        LgsType* newType = nullptr;
        if (funcType->isGenericType(param.type)) {
            newType = funcCall->args[i].expr->type;
            replacements[param.type->getName()] = funcCall->args[i].expr->type;
        } else {
            newType = param.type;
        }
        LgsParam newParam(newType, param.name);
        newParam.isSelf = param.isSelf;
        newParam.isVariadic = param.isVariadic;
        newFuncType->params.push_back(newParam);
    }

    if (funcType->isGenericType(funcType->rt)) {
        newFuncType->rt = replacements[funcType->rt->getName()];
    } else {
        newFuncType->rt = funcType->rt;
    }

    for (auto& [_, t] : replacements) {
        newFuncType->name += '_' + t->getName();
    }
    const auto newFunc = new LgsFunc(newFuncType);
    newFunc->stmtsBlock = func->stmtsBlock->clone();
    return newFunc;
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
    if (method->funcType->isMethod) {
        methodCall->args.insert(methodCall->args.begin(), LgsFuncArg(parent, LGS_SELF, true));
    }
    if (!visitFuncArgs(methodCall, method->funcType)) return;
    if (methodCall->equals(method->funcType)) {
        methodCall->func = method;
        methodCall->setType(method->funcType->rt);
    } else {
        addErrorIfSuccessful(E10034, methodCall->location, {parent->type->pname(), name, methodCall->asText(), method->asText()});
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
    const auto symbol = getSymbol(funcCall->name);
    if (!symbol) return addError(E10006, funcCall->location, {funcCall->name});
    const auto ft = symbol->getType()->asFuncType();
    if (!ft) return addError(E10046, funcCall->location, {funcCall->name});

    if (!visitFuncArgs(funcCall, ft)) return;
    if (!funcCall->equals(ft)) {
        addErrorIfSuccessful(E10015, funcCall->location, {funcCall->name, funcCall->asText(), ft->pname()});
        return;
    }
    if (symbol->symbolType != FUNC) {
        funcCall->ref = *symbol;
        funcCall->setType(ft->rt);
        return;
    }

    const auto func = symbol->func;
    if (!func->funcType->genericTypes.empty()) {
        const auto funcName = funcCall->getGenericName();
        const auto generics = file->symbolTable.genericFuncCalls.find(funcName);
        LgsFunc* genericFunc = nullptr;
        if (generics != file->symbolTable.genericFuncCalls.end()) {
            genericFunc = generics->second;
        } else {
            genericFunc = clone(func, funcCall);
            visitFunc(genericFunc);
            file->symbolTable.genericFuncCalls[funcName] = genericFunc;
        }
        funcCall->func = genericFunc;
        funcCall->setType(genericFunc->funcType->rt);
    } else {
        funcCall->func = func;
        funcCall->setType(ft->rt);
    }
}

bool LgsSema::visitFuncArgs(LgsFuncCall* funcCall, LgsFuncType* ft) {
    if (funcCall->isNamed) {
        auto paramsByName = ft->getParamsByName();
        std::unordered_set<std::string> visited;
        for (auto arg : funcCall->args) {
            if (visited.contains(arg.name)) {
                addError(E10098, arg.expr->location, {arg.expr->asText()});
                return false;
            }
            visited.insert(arg.name);
            if (!paramsByName.contains(arg.name)) {
                addError(E10094, arg.expr->location, {arg.expr->asText(), funcCall->name});
                return false;
            }
            const auto param = paramsByName[arg.name];
            castExprImplicitly(arg.expr, param->type);
            visitExpr(arg.expr);
            if (arg.name == "") {
                addError(E10096, funcCall->location);
                return false;
            }
        }
    } else {
        for (size_t i = ft->isMethod; i < ft->params.size(); ++i) {
            if (i >= funcCall->args.size()) break;
            auto& arg = funcCall->args[i];
            const auto& param = ft->params[i];
            castExprImplicitly(arg.expr, param.type);
            visitExpr(arg.expr);
            if (arg.name != "") {
                addError(E10096, funcCall->location);
                return false;
            }
        }
    }
    return true;
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

void LgsSema::visitComplexConst(LgsComplexConst* complex) {
    visitExpr(complex->real);
    visitExpr(complex->imaginary);
    complex->type = new LgsComplex(complex->real->type, complex->imaginary->type);
}

void LgsSema::visitTypeExpr(LgsTypeExpr* typeExpr) {
    typeResolver.resolveType(typeExpr->type);
}

void LgsSema::visitJson(const LgsJson* json) {
    switch (json->jsonType->kind) {
    case JSON_OBJECT:
        visitJsonObj(json->obj);
        break;
    case JSON_ARRAY:
        visitJsonArr(json->arr);
        break;
    case JSON_STRING:
        visitStrConst(json->strConst);
        break;
    case JSON_NULL:
    case JSON_INT:
    case JSON_FLOAT:
        break;
    case JSON_UNKNOWN:
        assert(0);
    }
}

void LgsSema::visitJsonArr(const LgsJsonArray* jsonArr) {
    for (const auto element : jsonArr->elements) {
        visitJson(element);
    }
}

void LgsSema::visitJsonObj(const LgsJsonObject* jsonObj) {
    for (auto &[_, v] : jsonObj->entries) {
        visitJson(v);
    }
}

void LgsSema::visitInstance(LgsInstance* instance) {
    const auto objName = instance->name;
    const auto symbol = getSymbol(objName);
    if (!symbol) return addError(E10006, instance->location, {instance->name});
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
    instance->setObject(obj);

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
        if (!validateFieldVisibility(field, instance->obj, arg.expr->location)) continue;
        castExprImplicitly(arg.expr, field->type);
        visitExpr(arg.expr);
        validateExprType(arg.expr, field->type);
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
    if (!iterable || iterable->asVariadic()) {
        return addError(E10108, iterIndex->location, {baseExpr->asText()});
    }
    visitIndex(iterIndex);
}

void LgsSema::visitIndex(LgsIterIndex* iterIndex) {
    const auto iterable = iterIndex->baseExpr->type->asIterable();
    if (iterIndex->index.to) {
        visitSlice(iterIndex);
    }
    auto exprFrom = iterIndex->index.from;
    visitExpr(exprFrom);
    if (!exprFrom->type->canCastTo(iterable->getIndexType())) {
        return addError(E10036, iterIndex->location, {iterIndex->asText(), exprFrom->type->pname()});
    }
    if (iterable->isStatic) {
        const auto index = exprFrom->getConstInt();
        const auto bounds = iterable->size->getConstInt();
        if (index.has_value() && bounds.has_value()) {
            if (index.value() >= bounds.value()) {
                addError(E10048, iterIndex->location, {iterIndex->asText(), std::to_string(*bounds)});
            }
            iterIndex->boundsChecked = true;
        }
    }
    iterIndex->setType(iterable->getValueType());
}

void LgsSema::visitSlice(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto iterable = baseExpr->type->asIterable();
    auto exprFrom = iterIndex->index.from;
    auto exprTo = iterIndex->index.to;
    visitExpr(exprFrom);
    visitExpr(exprTo);
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
        if (!sizeFrom.has_value() || !sizeTo.has_value()) return;
        if (sizeFrom.value() > sizeTo.value()) {
            return addError(E10037, iterIndex->location);
        }
        const auto bounds = iterable->size->getConstInt();
        if (!bounds.has_value()) return;
        if (sizeFrom.value() >= bounds.value()) {
            return addError(E10048, exprFrom->location, {std::to_string(*sizeFrom), std::to_string(*bounds)});
        }
        if (sizeTo.value() >= bounds.value()) {
            return addError(E10048, exprTo->location, {std::to_string(*sizeTo), std::to_string(*bounds)});
        }
    }
    iterIndex->setType(iterable);
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
    if (metaVar->varType == FOR_ELEMENT) {
        metaVar->type = stack.getInnermostForeachLoop()->loopVars.front()->type;
    }

    if (!loop->metaVars.contains(metaVar->varType)) {
        loop->metaVars[metaVar->varType] = metaVar;
    }
}

bool LgsSema::validateExprType(const LgsExpr* expr, LgsType* type) {
    if (const auto nullable = type->asNullable()) {
        // null must have a type
        if (expr->isNull && !nullable->baseType) {
            addError(E10024, expr->location);
            return false;
        }
        // // type must be nullable
        // if (!nullable) {
        //     addError(E10023, expr->location, {type->pname()});
        //     return false;
        // }
    }
    if (!type || !expr->type || type->isUnknown() || expr->type->isUnknown()) return false;
    if (!expr->type->canCastTo(type)) {
        addError(E10001, expr->location, {type->pname(), expr->type->pname()});
        return false;
    }
    return true;
}

bool LgsSema::validateTypeName(const std::string& name, const LgsLocation& location) {
    if (islower(name[0])) {
        addError(E10033, location);
        return false;
    }
    const auto symbol = getSymbol(name);
    if (symbol && symbol->isBuiltin) {
        addError(E10053, location, {name});
        return false;
    }
    return true;
}

bool LgsSema::validateLocalName(const std::string& name, const LgsLocation& location) {
    if (isupper(name[0])) {
        addError(E10099, location);
        return false;
    }
    const auto symbol = getSymbol(name);
    if (symbol && symbol->isBuiltin) {
        addError(E10053, location, {name});
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
        if (!i.has_value() || !bounds.has_value()) return;
        if (i.value() >= bounds.value()) {
            return addError(E10048, iterIndex->location, {iterIndex->asText(), std::to_string(*bounds)});
        }
    }
}

bool LgsSema::validateFieldVisibility(LgsField* field, LgsType* parent, const LgsLocation& location) {
    assert(parent);
    if (parent->asVec()) return true;
    if (parent->asObject() && parent->asObject()->singleton) return true;
    if (!field || field->isVirtual) return false;
    if (stack.currentFunc()->isTest) return true;
    if (!field->isPublic && file->path != *field->location.filepath) {
        addError(E10030, location, {field->name, parent->pname()});
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
    const auto dim = vec->dimVec;
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
    if (!stmtBlock || func->funcType->rt->isVoid()) return true;
    const auto lastStmt = stmtBlock->stmts.back();
    constexpr auto objWrapper = LgsStmtWrapper::WrapperType::Object;
    constexpr auto stmtWrapper = LgsStmtWrapper::WrapperType::Stmt;
    constexpr auto exprWrapper = LgsStmtWrapper::WrapperType::Expr;
    const auto isStmt = lastStmt.wrapperType == stmtWrapper;
    if (isStmt && lastStmt.stmt->asReturn()) return true;
    auto isValid = false;
    for (const auto stmt : stmtBlock->stmts) {
        if (stmt.wrapperType == objWrapper || stmt.wrapperType == exprWrapper) continue;
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

void LgsSema::addLocalSymbol(const LgsSymbol& newSymbol) {
    auto symbolName = *newSymbol.name;
    const auto symbol = globals.table.getSymbol(symbolName);
    if (symbol && symbol->isBuiltin) {
        return addError(E10053, *newSymbol.location, {symbolName});
    }
    if (file->symbolTable.getSymbol(symbolName)) {
        return addError(E10011, *newSymbol.location, {symbolName});
    }
    stack.getSymbolTable().addSymbol(newSymbol, &errHandler, file->path);
}

LgsSymbol* LgsSema::getSymbol(const std::string& name) {
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
    return nullptr;
}

void LgsSema::createCoroutineFunc(LgsFuncCall* funcCall) {
    const auto originalFT = funcCall->func->funcType;
    const auto newFunc = new LgsFunc(originalFT);
    newFunc->location = funcCall->func->location;
    newFunc->funcType->location = originalFT->location;
    newFunc->funcType->isCoroutine = true;
    newFunc->stmtsBlock = funcCall->func->stmtsBlock;
    visitFunc(newFunc);
    funcCall->coroutine = newFunc;
    funcCall->func = nullptr;
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

void LgsSema::addErrorIfSuccessful(const LgsBaseMsg& lgsErr, const LgsLocation& location, const std::vector<std::string>& args) {
    if (!errHandler.successful) return;
    errHandler.addError(lgsErr, &location, file->path, args);
}

void LgsSema::addRTType(LgsType* type) const {
    if (!errHandler.successful) return;
    if (!type || type->isVoid()) return;
    if (type->asNullable() && !type->asNullable()->baseType) return;
    for (const auto rttType : globals.table.rttTypes) {
        if (rttType->equals(type)) return;
    }
    for (const auto rttType : file->symbolTable.rttTypes) {
        if (rttType->equals(type)) return;
    }
    file->symbolTable.rttTypes.push_back(type);
}

void LgsSema::deleteRTType(LgsType* type) const {
    if (!type || type->isVoid() || (type->asNullable() && !type->asNullable()->baseType)) return;
    auto& rttTypes = file->symbolTable.rttTypes;
    for (auto it = rttTypes.begin(); it != rttTypes.end(); ++it) {
        if ((*it)->equals(type)) {
            rttTypes.erase(it);
            return;
        }
    }
}