#include "SemaAnalyser.h"
#include "LgsErrors.h"
#include "LgsGlobals.h"
#include "LgsInterfaceFile.h"
#include "LgsObjectFile.h"
#include "LgsProject.h"
#include "ThreadPool.h"
#include "exprs/LgsCast.h"
#include "exprs/LgsNull.h"
#include "stmts/LgsField.h"
#include "stmts/LgsReturn.h"
#include "types/LgsBool.h"
#include "exprs/unary/LgsDArray.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/binary/LgsBinaryExpr.h"
#include "exprs/unary/constants/LgsTypeConst.h"
#include "stmts/LgsBreakStmt.h"
#include "types/LgsEnum.h"
#include "exprs/unary/LgsEnumField.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsSArray.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsContinueStmt.h"
#include "stmts/LgsPatternMatch.h"
#include "types/LgsArray.h"
#include "types/LgsUnknownType.h"
#include "types/LgsVoid.h"

#include <loops/LgsForeachLoop.h>
#include <loops/LgsLoop.h>
#include <loops/LgsRangeLoop.h>
#include <stmts/LgsAssignment.h>
#include <stmts/LgsIfStmt.h>

void SemaAnalyser::analyseFiles(const LogosProject* project, vector<LgsError>& errors) {
    ThreadPool threadPool;
    threadPool.start();
    for (const auto& file : project->files) {
        threadPool.runTask([=, &file, &errors] {
            SemaAnalyser semaAnalyser(file);
            semaAnalyser.analyse();
            lock_guard lock(mtx);
            errors.insert(errors.end(), semaAnalyser.errHandler.errors.begin(), semaAnalyser.errHandler.errors.end());
        });
    }
    threadPool.wait();
}

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
    for (const auto& obj : mainFile->objects) {
        visitObject(obj);
    }
    for (const auto& lgsEnum : mainFile->enums) {
        visitEnum(lgsEnum);
    }
    for (const auto& [_, overloads] : mainFile->funcs) {
        checkDuplicateFuncs(overloads);
    }
    for (const auto& func : mainFile->getAllFuncs()) {
        visitFunc(func);
    }
    visitFunc(mainFile->mainFunc);
}

void SemaAnalyser::visitObject(LgsObject* obj) {
    for (const auto& [_, field] : obj->fields) {
        visitField(field);
    }
    for (const auto& overload : obj->getAllMethods()) {
        visitFunc(overload);
    }
}

void SemaAnalyser::visitInterface(LgsInterface* interface) {

}

void SemaAnalyser::visitFunc(LgsFunc* func) {
    func->path = file->absPath;
    lgsStack.enterScope(func);
    visitFuncType(&func->funcType);
    visitStmtBlock(func->stmtBlock);
    lgsStack.exitScope();
    validateFuncControlFlow(func);
}

void SemaAnalyser::visitFuncType(const LgsFuncType* funcType) {
    for (const auto param : funcType->params) {
        visitParam(param);
    }
}

void SemaAnalyser::visitParam(LgsParam* param) {
    if (param->expr) {
        visitExpr(param->expr);
        checkExprType(param->expr, param->type);
    }
    addLocalSymbol(param->name, LgsSymbol(param));
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
    } else if (const auto ifStmt = lastStmt->asIfStmt()) {
        stmtBlock->hasReturn = ifStmt->hasReturn;
    }
}

void SemaAnalyser::visitField(const LgsField* field) {
    visitExpr(field->expr);
    checkExprType(field->expr, field->type);
}

void SemaAnalyser::visitAssignment(const LgsAssignment* assignment) {
    const auto rExpr = assignment->rvalue;
    const auto lExpr = assignment->lvalue;
    visitExpr(rExpr);
    if (const auto selection = dynamic_cast<LgsSelection*>(lExpr)) {
        visitSelection(selection);
    } else if (const auto iterIndex = dynamic_cast<LgsIterIndex*>(lExpr)) {
        visitIterIndex(iterIndex);
    } else {
        assert(false);
    }
    checkExprType(rExpr, lExpr->type);
}

void SemaAnalyser::visitVarDec(LgsVarDec* varDec) {
    if (varDec->expr) {
        visitExpr(varDec->expr);
        varDec->expr->type = resolveType(varDec->expr->type, &errHandler);
        varDec->type = varDec->expr->type;
        if (!checkExprType(varDec->expr, varDec->type)) return;
    } else {
        const auto type = resolveType(varDec->type, &errHandler);
        varDec->expr = type->getZeroValue();
        varDec->type = varDec->expr->type;
    }
    assert(varDec->type);
    addLocalSymbol(varDec->name, LgsSymbol(varDec));
}

void SemaAnalyser::visitIfStmt(LgsIfStmt* ifStmt) {
    assert(ifStmt->ifCond);
    visitExpr(ifStmt->ifCond);
    visitStmtBlock(ifStmt->ifStmtBlock);
    ifStmt->hasReturn = ifStmt->ifStmtBlock->hasReturn;
    for (const auto& elseIfStmtBlock : ifStmt->elseIfStmtBlocks) {
        visitStmtBlock(elseIfStmtBlock);
        ifStmt->hasReturn = ifStmt->hasReturn && elseIfStmtBlock->hasReturn;
    }
    if (ifStmt->elseStmtBlock) {
        visitStmtBlock(ifStmt->elseStmtBlock);
        ifStmt->hasReturn = ifStmt->elseStmtBlock->hasReturn;
    }
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

void SemaAnalyser::visitLoopStmt(LgsLoop* loopStmt) {
    lgsStack.enterScope();
    lgsStack.currentLoop = loopStmt;
    if (const auto rangeLoop = dynamic_cast<LgsRangeLoop*>(loopStmt)) {
        visitRangeLoop(rangeLoop);
    } else if (const auto foreachLoop = dynamic_cast<LgsForeachLoop*>(loopStmt)) {
        visitForeachLoop(foreachLoop);
    }
    lgsStack.currentLoop = nullptr;
    lgsStack.exitScope();
}

void SemaAnalyser::visitRangeLoop(const LgsRangeLoop* rangeLoop) {
    // TODO check all loop vars
    const auto loopVar = rangeLoop->loopVars[0];
    addLocalSymbol(loopVar->name, LgsSymbol(loopVar));
    visitStmtBlock(rangeLoop->stmtBlock);
}

void SemaAnalyser::visitForeachLoop(const LgsForeachLoop* foreachLoop) {
    const auto iterableExpr = foreachLoop->iterExpr;
    visitUnaryExpr(iterableExpr);
    const auto iterable = iterableExpr->type->asIterable();
    if (!iterable) {
        return errHandler.handleError(E10002, &iterableExpr->location, {iterableExpr->getName()});
    }
    // TODO check all loop vars
    for (const auto varDec : foreachLoop->loopVars) {
        varDec->type = iterable->underlyingType;
        varDec->expr = iterable->getZeroValue();
        addLocalSymbol(varDec->name, LgsSymbol(varDec));
    }
    visitStmtBlock(foreachLoop->stmtBlock);
}

void SemaAnalyser::visitReturnStmt(const LgsReturn* returnStmt) {
    auto funcType = lgsStack.currentFunc->funcType;
    const auto rt = funcType.rt;
    if (returnStmt->expr) {
        returnStmt->expr->isReturnValue = true;
        visitExpr(returnStmt->expr);
    }
    if (rt->isVoidType) {
        if (returnStmt->expr) {
            const auto exprType = returnStmt->expr->type;
            if (!exprType->isVoidType) {
                errHandler.handleError(E10027, &returnStmt->location, {funcType.name, rt->prettyName(), exprType->prettyName()});
                return;
            }
        }
    } else if (!returnStmt->expr) {
        return errHandler.handleError(E10026, &returnStmt->location, {funcType.name, rt->prettyName()});
    } else if (!rt->equals(returnStmt->expr->type)) {
        return errHandler.handleError(E10027, &returnStmt->location, {funcType.name, rt->prettyName(), returnStmt->expr->type->prettyName()});
    }
}

void SemaAnalyser::visitBreakStmt(const LgsBreakStmt* breakStmt) {
    if (!lgsStack.currentLoop) {
        return errHandler.handleError(E10017, &breakStmt->location);
    }
}

void SemaAnalyser::visitContinueStmt(const LgsContinueStmt* continueStmt) {
    if (!lgsStack.currentLoop) {
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
    castExpr->toType = resolveType(castExpr->toType, &errHandler);
    if (!castExpr->cast()) {
        errHandler.handleError(E10018, &castExpr->location, {fromValue->type->prettyName(), castExpr->toType->prettyName()});
    }
}

void SemaAnalyser::visitUnaryExpr(LgsUnaryExpr* unaryExpr) {
    if (const auto instance = unaryExpr->asInstance()) {
        visitInstance(instance);
    } else if (const auto funcCall = unaryExpr->asFuncCall()) {
        visitFuncCall(funcCall);
    } else if (const auto selection = unaryExpr->asSelection()) {
        visitSelection(selection);
    } else if (const auto dArray = unaryExpr->asDArray()) {
        visitDArray(dArray);
    } else if (const auto sArray = unaryExpr->asSArray()) {
        visitSArray(sArray);
    } else if (const auto hashMap = unaryExpr->asHashMap()) {
        visitHashMap(hashMap);
    } else if (const auto iterIndex = unaryExpr->asArrayIndex()) {
        visitIterIndex(iterIndex);
    } else if (const auto variable = unaryExpr->asVariable()) {
        visitVariable(variable);
    }
}

void SemaAnalyser::visitBinaryExpr(LgsBinaryExpr* binaryExpr) {
    visitExpr(binaryExpr->left);
    visitExpr(binaryExpr->right);
    setBinaryExprType(binaryExpr);
}

void SemaAnalyser::visitDArray(LgsDArray* array) {
    for (const auto& element : array->initialElements) {
        visitExpr(element);
    }
    array->arrType.setUnderlyingType(array->initialElements);
}

void SemaAnalyser::visitSArray(LgsSArray* array) {
    for (const auto& element : array->initialElements) {
        visitExpr(element);
    }
    array->arrType.setUnderlyingType(array->initialElements);
    array->arrType.sizes.emplace_back(array->initialElements.size());
}

void SemaAnalyser::visitHashMap(LgsHashMap* hashMap) const {
    hashMap->mapType.setUnderlyingType(hashMap->initialElements);
}

void SemaAnalyser::visitVariable(LgsVariable* variable) {
    const auto symbol = getSymbol(variable->name, variable);
    if (!symbol) return;
    switch (symbol->type) {
    case VAR_DEC:
        symbol->varDec->refs.emplace_back(variable);
        setExprType(variable, symbol->varDec->type);
        break;
    case PARAM:
        symbol->param->refs.emplace_back(variable);
        setExprType(variable, symbol->param->type);
        break;
    case ENUM:
        setExprType(variable, symbol->lgsEnum);
        break;
    case ENUM_FIELD:
        setExprType(variable, symbol->enumField->type);
        break;
    case FUNC:
        // TODO add func matching
        setExprType(variable, symbol->func->overloads[0]->funcType.rt);
        break;
    default:
        assert(false);
    }
    assert(variable->type);
    variable->ref = symbol->clone();
}


void SemaAnalyser::visitSelection(LgsSelection* selection) {
    const auto exprs = selection->exprs;
    visitFirstSelection(exprs[0]);
    visitInnerSelections(selection);
    setExprType(selection, selection->lastExpr()->type);
}

void SemaAnalyser::visitFirstSelection(LgsExpr* firstExpr) {
    if (const auto variable = dynamic_cast<LgsVariable*>(firstExpr)) {
        visitVariable(variable);
    } else if (const auto funcCall = dynamic_cast<LgsFuncCall*>(firstExpr)) {
        visitFuncCall(funcCall);
    } else if (const auto typeConst = dynamic_cast<LgsTypeConst*>(firstExpr)) {
        typeConst->type = resolveType(typeConst->type, &errHandler);
    } else if (const auto iterIndex = dynamic_cast<LgsIterIndex*>(firstExpr)) {
        visitIterIndex(iterIndex);
    } else {
        assert(false);
    }
    assert(firstExpr->type);
}


void SemaAnalyser::visitInnerSelections(const LgsSelection* selection) {
    const auto exprs = selection->exprs;
    for (int i = 0; i < exprs.size() - 1; ++i) {
        const auto parentExpr = exprs[i];
        const auto childExpr = exprs[i + 1];
        if (const auto var = dynamic_cast<LgsVariable*>(childExpr)) {
            visitFieldCall(parentExpr, var);
        } else if (const auto methodCall = dynamic_cast<LgsFuncCall*>(childExpr)) {
            visitMethodCall(methodCall, parentExpr->type);
        }
    }
}

void SemaAnalyser::visitFieldCall(const LgsExpr* parentExpr, LgsVariable* childField) {
    const auto parentType = parentExpr->type;
    const auto field = parentType->getField(childField->name);
    if (!field) {
        return errHandler.handleError(E10005, &childField->location, {childField->getName(), parentType->prettyName()});
    }
    setExprType(childField, field->type);
    childField->ref = new LgsSymbol(field->clone());
    if (!field->isPublic && file->absPath != field->parent->path) {
        errHandler.handleError(E10030, &childField->location, {childField->getName(), field->parent->name});
    }
}

void SemaAnalyser::visitFuncCall(LgsFuncCall* funcCall) {
    vector<string> argTypeNames;
    for (const auto& arg : funcCall->args) {
        visitExpr(arg);
        if (!arg->type) return;
        argTypeNames.emplace_back(arg->type->prettyName());
    }
    resolveFuncCall(funcCall);
}

void SemaAnalyser::visitMethodCall(LgsFuncCall* methodCall, const LgsType* parentType) {
    vector<string> argTypeNames;
    for (const auto& arg : methodCall->args) {
        visitExpr(arg);
        argTypeNames.emplace_back(arg->type->prettyName());
    }
    auto name = methodCall->name;
    const auto overloads = parentType->getMethodOverloads(name);
    if (overloads.empty()) {
        return errHandler.handleError(E10013, &methodCall->location, {name, parentType->prettyName()});
    }
    if (!resolveMethodCall(overloads, methodCall, parentType->prettyName())) return;
    assert(methodCall->func);
    checkMethodVisibility(methodCall);
}

void SemaAnalyser::visitInstance(LgsInstance* instance) {
    instance->type = resolveType(instance->type, &errHandler);
    if (!instance->type) return;
    const auto symbol = getSymbol(instance->type->prettyName(), instance);
    if (!symbol) return;
    if (symbol->type != OBJECT) {
        return errHandler.handleError(E10022, &instance->location, {instance->type->prettyName()});
    }
    if (symbol->object->isSingleton) {
        return errHandler.handleError(E10032, &instance->location, {instance->type->prettyName()});
    }

    const auto obj = symbol->object->clone();
    for (const auto& arg : instance->args) {
        visitExpr(arg->expr);
        const auto lgsField = obj->getField(arg->name);
        if (!lgsField) {
            errHandler.handleError(E10005, &arg->location, {arg->name, obj->name});
            continue;
        }
        lgsField->expr = arg->expr;
    }

    for (const auto [_, field] : obj->fields) {
        if (field->isConst && !field->expr) {
            errHandler.handleError(E10029, &field->location, {field->name});
            continue;
        }
    }
    instance->obj = obj;
    instance->type = instance->obj;
}

void SemaAnalyser::visitIterIndex(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    visitUnaryExpr(baseExpr);
    for (const auto index : iterIndex->indices) {
        visitExpr(index->from);
        visitExpr(index->to);
    }
    const auto baseExprType = baseExpr->type;
    if (const auto iter = baseExprType->asIterable()) {
        if (iter->isStatic) {
            if (!checkIndexBoundaries(iterIndex)) return;
        }
        setIterIndexType(iterIndex);
    } else {
        return errHandler.handleError(E10002, &iterIndex->location, {baseExpr->getName()});
    }
}

void SemaAnalyser::setExprType(LgsExpr* expr, LgsType* type) {
    expr->type = resolveType(type, &errHandler);
}

bool SemaAnalyser::setSelectionFieldType(const LgsUnaryExpr* parent, LgsVariable* fieldVariable) {
    const auto type = parent->type;
    const auto field = type ? type->getField(fieldVariable->name) : nullptr;
    if (!type || !field) {
        errHandler.handleError(E10005, &fieldVariable->location, {fieldVariable->getName(), type->prettyName()});
        return false;
    }
    if (!field->isPublic) {}
    setExprType(fieldVariable, field->type);
    return true;
}

void SemaAnalyser::setIterIndexType(LgsIterIndex* iterIndex) const {
    const auto iterable = iterIndex->baseExpr->type->asIterable();
    iterIndex->type = iterable->getUnderlyingType();
    assert(iterIndex->type);
}

void SemaAnalyser::setBinaryExprType(LgsBinaryExpr* binaryExpr) {
    switch (binaryExpr->op) {
    case ADD:
    case SUB:
    case MUL:
    case DIV:
    case BIT_AND:
    case BIT_OR:
    case BIT_XOR:
    case LSHIFT:
    case RSHIFT: {
        const auto lType = binaryExpr->left->type;
        const auto rType = binaryExpr->right->type;
        if (!lType || !rType) return;
        setExprType(binaryExpr, lType->inferBinaryType(rType));
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
        setExprType(binaryExpr, &LGS_BOOL);
        return;
    }
    case NOOP:
        break;
    }
}

bool SemaAnalyser::checkExprType(LgsExpr* expr, LgsType* type) {
    if (!expr) return true;
    if (expr->isNull) {
        // null must have a type
        if (!type) {
            errHandler.handleError(E10024, &expr->location);
            return false;
        }
        // type must be nullable
        if (!type->isNullable) {
            errHandler.handleError(E10023, &type->location, {type->prettyName(), type->prettyName()});
            return false;
        }
        expr->type = type;
        return true;
    }
    if (type && expr->type && !expr->type->equals(type)) {
        errHandler.handleError(E10001, &expr->location, {type->prettyName(), expr->type->prettyName()});
        return false;
    }
    return true;
}

bool SemaAnalyser::checkIndexBoundaries(LgsIterIndex* iterIndex) {
    const LgsIterable* baseIterable = nullptr;
    if (const auto var = iterIndex->baseExpr->asVariable()) {
        const auto ref = var->ref;
        if (ref->type == VAR_DEC) {
            const auto expr = ref->varDec->expr;
            baseIterable = expr->type->asIterable();
        }
    }
    assert(baseIterable);
    const auto iterDims = baseIterable->getDims();
    if (iterDims < iterIndex->indices.size()) {
        errHandler.handleError(E10035, &iterIndex->location, {iterIndex->code, to_string(iterIndex->indices.size()), to_string(iterDims)});
        return false;
    }

    for (int i = 0; i < iterIndex->indices.size(); ++i) {
        const auto upperBound = baseIterable->sizes[i];
        const auto indexCallFrom = iterIndex->indices[i]->from;
        bool valid = checkSingleIndexBoundaries(iterIndex, indexCallFrom, upperBound);
        if (!valid) return false;
        const auto indexCallTo = iterIndex->indices[i]->to;
        if (indexCallTo) {
            valid = checkSingleIndexBoundaries(iterIndex, indexCallTo, upperBound);
        }
        if (!valid) return false;
    }
    return true;
}

bool SemaAnalyser::checkSingleIndexBoundaries(LgsIterIndex* iterIndex, LgsExpr* index, const size_t upperBound) {
    const auto baseExprType = iterIndex->baseExpr->type;
    if (!baseExprType->isIndexable(index->type)) {
        errHandler.handleError(E10036, &iterIndex->location, {baseExprType->prettyName(), index->type->prettyName()});
        return false;
    }

    if (index->type->isConst) {
        if (const auto indexInt = index->asIntConst()) {
            if (indexInt->value >= upperBound) {
                errHandler.handleError(E10003, &iterIndex->location, {iterIndex->code});
                return false;
            }
            return true;
        }
        assert(false);
    }
    return true;
}

bool SemaAnalyser::checkSliceBoundaries(LgsIterIndex* iterIndex, const LgsIndex* index, const size_t upperBound) {
    bool valid = checkSingleIndexBoundaries(iterIndex, index->from, upperBound);
    if (!valid) return false;
    valid = checkSingleIndexBoundaries(iterIndex, index->to, upperBound);
    if (!valid) return false;
    const auto fromIntConst = index->from->asIntConst()->value;
    const auto toIntConst = index->to->asIntConst()->value;
    if (fromIntConst >= toIntConst) {
        errHandler.handleError(E10037, &iterIndex->location, {iterIndex->code});
        return false;
    }
    return true;
}

void SemaAnalyser::resolveFuncCall(LgsFuncCall* funcCall) {
    const auto symbol = getSymbol(funcCall->name);
    if (!symbol) return;
    switch (symbol->type) {
    case VAR_DEC: {
        const auto funcType = symbol->param->type->asFuncType();
        if (isFuncCallEqual(funcType, funcCall)) break;
        errHandler.handleError(E10015, &funcCall->location, {funcCall->name, funcCall->getText(), funcType->getAsStr()});
        break;
    }
    case PARAM: {
        const auto funcType = symbol->varDec->type->asFuncType();
        if (isFuncCallEqual(funcType, funcCall)) break;
        errHandler.handleError(E10015, &funcCall->location, {funcCall->name, funcCall->getText(), funcType->getAsStr()});
        break;
    }
    case FUNC: {
        auto found = false;
        const auto& overloads = symbol->func->overloads;
        for (const auto overload : overloads) {
            if (!isFuncCallEqual(overload, funcCall)) continue;
            found = true;
        }
        if (!found) {
            errHandler.handleError(E10015, &funcCall->location, {funcCall->name, funcCall->getText(), getOverloadsAsStr(overloads)});
        }
        break;
    }
    default:
        assert(false);
    }
}

LgsFunc* SemaAnalyser::resolveMethodCall(const vector<LgsMethodImpl*>& overloads, LgsFuncCall* methodCall, const string& parentName) {
    for (const auto overload : overloads) {
        if (isFuncCallEqual(overload, methodCall)) return overload;
    }
    errHandler.handleError(E10034, &methodCall->location, {parentName, methodCall->name, methodCall->getText(), getOverloadsAsStr(overloads)});
    return nullptr;
}

bool SemaAnalyser::resolveFuncCallWithDefaultParams(const LgsFuncType* funcType, const LgsFuncCall* funcCall) const {
    const auto params = funcType->params;
    const auto argsSize = funcCall->args.size();
    for (size_t i = funcCall->isMethodCall; i < params.size(); ++i) {
        const auto param = params[i];
        if (i >= argsSize) continue;
        const auto arg = funcCall->args[i];
        if (!param->type->equals(arg->type)) return false;
    }
    return true;
}

bool SemaAnalyser::isFuncCallEqual(const LgsFuncType* funcType, LgsFuncCall* funcCall) const {
    if (!funcType) return false;
    auto equal = false;
    if (funcType->hasDefaultParams) {
        equal =resolveFuncCallWithDefaultParams(funcType, funcCall);
    } else {
        equal = funcType->equals(funcCall);
    }
    if (equal) {
        funcCall->type = funcType->rt;
        funcCall->func = new LgsFuncImpl(funcType);
    }
    return equal;
}

bool SemaAnalyser::isFuncCallEqual(LgsFunc* func, LgsFuncCall* funcCall) const {
    auto equal = false;
    if (func->funcType.hasDefaultParams) {
        equal = resolveFuncCallWithDefaultParams(&func->funcType, funcCall);
    } else {
        equal = func->funcType.equals(funcCall);
    }
    if (equal) {
        funcCall->func = func;
        funcCall->type = func->funcType.rt;
    }
    return equal;
}

void SemaAnalyser::checkDuplicateFuncs(const vector<LgsFuncImpl*>& overloads) {
    for (size_t i = 0; i < overloads.size(); ++i) {
        const auto overload1 = overloads[i];
        for (size_t j = i + 1; j < overloads.size(); ++j) {
            const auto overload2 = overloads[j];
            const auto funcType1 = &overload1->funcType;
            const auto funcType2 = &overload2->funcType;
            if (funcType1->hasDefaultParams && funcType2->hasDefaultParams) {
                if (!funcType1->equals(funcType2)) {
                    return errHandler.handleError(E10033, &overload1->location, {funcType1->getAsStr()});
                }
            } else if (funcType1->hasDefaultParams) {
                assert(false);
            } else if (funcType2->hasDefaultParams) {
                assert(false);
            }
            if (funcType1->equals(funcType2)) {
                errHandler.handleError(E10033, &overload1->location, {funcType1->getAsStr()});
            }
        }
    }
}

void SemaAnalyser::checkMethodVisibility(const LgsFuncCall* methodCall) {
    const auto method = methodCall->func;
    if (!method->funcType.isPublic && file->absPath != method->path) {
        errHandler.handleError(E10031, &method->location, {method->funcType.name, method->funcType.parentName});
    }
}

void SemaAnalyser::validateFuncControlFlow(const LgsFunc* func) {
    if (dynamic_cast<LgsVoid*>(func->funcType.rt)) return;
    const auto stmtBlock = func->stmtBlock;
    const bool isFlowCorrect = func->funcType.name != LOGOS_MAIN_FUNC && !stmtBlock->hasReturn;
    if (isFlowCorrect) {
        errHandler.handleError(E10004, &func->location, {func->funcType.name, func->funcType.rt->prettyName()});
    }
}

string getOverloadsAsStr(const vector<LgsMethodImpl*>& overloads) {
    stringstream str;
    for (const auto& overload : overloads) {
        str << "\n\t     - " << overload->funcType.getAsStr();
    }
    return str.str();
}

string getOverloadsAsStr(const vector<LgsFunc*>& overloads) {
    stringstream str;
    for (const auto& overload : overloads) {
        str << "\n\t     - " << overload->funcType.getAsStr();
    }
    return str.str();
}

LgsSymbol* SemaAnalyser::getSymbol(const string& name, const LgsValue* value) {
    LgsSymbol* symbol = nullptr;
    // Globals symbols
    if (globals.symbols.find(name) != globals.symbols.end()) {
        symbol = &globals.symbols[name];
    } else {
        // Locals
        auto& symbols = lgsStack.top().symbols;
        if (symbols.find(name) != symbols.end()) {
            symbol = &symbols[name];
        }
    }
    if (!symbol && value) {
        errHandler.handleError(E10006, &value->location, {name});
    }
    return symbol;
}

void SemaAnalyser::addLocalSymbol(const string&name, const LgsSymbol& symbol) {
    if (getSymbol(name)) {
        const auto location = symbol.getLocation();
        return errHandler.handleError(E10011, location, {name, to_string(location->lineNumber)});
    }
    lgsStack.addLocalSymbol(name, symbol);
}

LgsType* resolveType(LgsType* type, LgsErrHandler* errorHandler) {
    if (const auto iterable = type->asIterable()) {
        if (dynamic_cast<LgsUnknownType*>(iterable->underlyingType)) {
            iterable->underlyingType = resolveType(iterable->underlyingType, errorHandler);
        }
        return type;
    }

    if (!dynamic_cast<LgsUnknownType*>(type)) return type;
    auto typeName = type->prettyName();
    const auto nullable = type->isNullable;
    if (globals.symbols.find(typeName) == globals.symbols.end()) {
        errorHandler->handleError(E10006, &type->location, {typeName});
        return nullptr;
    }

    const auto symbol = &globals.symbols[typeName];
    delete type;
    LgsType* newType = nullptr;
    if (symbol->type == OBJECT) {
        symbol->object->isNullable = nullable;
        newType = symbol->object;
    }
    if (symbol->type == INTERFACE) {
        symbol->interface->isNullable = nullable;
        newType = symbol->interface;
    }
    if (symbol->type == ENUM) {
        symbol->lgsEnum->isNullable = nullable;
        newType = symbol->lgsEnum;
    }
    if (symbol->type == ENUM_FIELD) {
        symbol->enumField->parent->isNullable = nullable;
        newType = symbol->enumField->parent;
    }
    assert(newType);
    return newType;
}

bool resolveGlobalTypes(const vector<LgsFile*>& files) {
    for (const auto& file : files) {
        LgsErrHandler errHandler;
        errHandler.filePath = file->absPath;
        if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
            for (const auto& object : mainFile->objects) {
                resolveObjMemberTypes(object, &errHandler);
            }
            for (const auto& func : mainFile->getAllFuncs()) {
                resolveFuncTypes(&func->funcType, &errHandler);
            }
        } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
            resolveObjMemberTypes(objFile->obj, &errHandler);
        } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
            auto overloads = interfaceFile->interface->getAllMethods();
            for (const auto& overload : overloads) {
                resolveFuncTypes(&overload->funcType, &errHandler);
            }
        }
        if (!errHandler.successful) return false;
    }
    return true;
}

void resolveObjMemberTypes(LgsObject* const& obj, LgsErrHandler* errHandler) {
    for (const auto& [_, field] : obj->fields) {
        field->type = resolveType(field->type, errHandler);
        field->parent = obj;
    }
    for (const auto& overload : obj->getAllMethods()) {
        resolveFuncTypes(&overload->funcType, errHandler);
    }
    for (int i = 0; i < obj->implements.size(); ++i) {
        obj->implements[i] = resolveType(obj->implements[i], errHandler);
    }
    resolveObjectImplements(obj, errHandler);
}

void resolveFuncTypes(LgsFuncType* signature, LgsErrHandler* errHandler) {
    signature->rt = resolveType(signature->rt, errHandler);
    for (int i = 0; i < signature->params.size(); ++i) {
        signature->params[i]->type = resolveType(signature->params[i]->type, errHandler);
    }
}

void resolveObjectImplements(LgsObject* obj, LgsErrHandler* errHandler) {
    for (int i = 0; i < obj->implements.size(); ++i) {
        const auto implement = obj->implements[i];
        if (!implement) continue;
        const auto interface = implement->asInterface();
        if (!interface) {
            errHandler->handleError(E10025, &implement->location, {implement->prettyName()});
            continue;
        }

        vector<LgsFunc*> missingFuncs;
        for (const auto& [name, interfaceOverloads] : interface->methods) {
            const auto& objOverloads = obj->getMethodOverloads(name);
            for (const auto interfaceOverload : interfaceOverloads) {
                auto found = false;
                for (const auto objOverload : objOverloads) {
                    if (objOverload->funcType.equals(&interfaceOverload->funcType)) {
                        objOverload->implements = interfaceOverload;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    missingFuncs.emplace_back(interfaceOverload);
                } else {
                    break;
                }
            }
        }
        if (!missingFuncs.empty()) {
            errHandler->handleError(E10016, &obj->location, {obj->name, interface->name, getOverloadsAsStr(missingFuncs)});
        }
    }
}