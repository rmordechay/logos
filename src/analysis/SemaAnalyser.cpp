#include "SemaAnalyser.h"
#include "LgsErrors.h"
#include "LgsGlobals.h"
#include "LgsInterfaceFile.h"
#include "LgsObjectFile.h"
#include "LgsProject.h"
#include "ThreadPool.h"
#include "exprs/LgsCast.h"
#include "stmts/LgsField.h"
#include "stmts/LgsReturn.h"
#include "types/primitives/LgsBool.h"
#include "exprs/unary/LgsArrayExpr.h"
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
#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsContinueStmt.h"
#include "stmts/LgsPatternMatch.h"
#include "types/array/LgsArray.h"
#include "types/primitives/LgsVoid.h"
#include <loops/LgsForeachLoop.h>
#include <loops/LgsLoop.h>
#include <loops/LgsRangeLoop.h>
#include <stmts/LgsAssignment.h>
#include <stmts/LgsIfStmt.h>

inline std::mutex mtx;

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

void SemaAnalyser::visitInterface(LgsInterface* interface) const {

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
        if (validateExprType(param->expr, param->type)) {
            param->expr->setType(param->type);
        }
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
    if (field->expr) validateExprType(field->expr, field->type);
}

void SemaAnalyser::visitVarDec(LgsVarDec* varDec) {
    varDec->type = resolveType(varDec->type);
    if (varDec->expr) {
        visitExpr(varDec->expr);
        if (validateExprType(varDec->expr, varDec->type)) {
            varDec->type = varDec->expr->type;
        }
    } else {
        varDec->expr = varDec->type->getZeroValue();
        varDec->type = varDec->expr->type;
    }
    addLocalSymbol(varDec->name, LgsSymbol(varDec));
}

void SemaAnalyser::visitAssignment(const LgsAssignment* assignment) {
    const auto rightExpr = assignment->rValue;
    const auto leftExpr = assignment->lValue;
    visitExpr(leftExpr);
    visitExpr(rightExpr);
    if (!validateExprType(rightExpr, leftExpr->type)) return;
    if (const auto iterIndex = leftExpr->asIterIndex()) {
        visitAssignIterIndex(iterIndex, rightExpr);
    } else {
        assert(false);
    }
}

void SemaAnalyser::visitAssignIterIndex(const LgsIterIndex* iterIndex, LgsExpr* expr) const {
    if (const auto arr = expr->asArrayExpr()) {
        arr->arrType.isStatic = iterIndex->type->isConst;
    }
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
    const auto loopVar = rangeLoop->loopVars[0];
    addLocalSymbol(loopVar->name, LgsSymbol(loopVar));
    visitStmtBlock(rangeLoop->stmtBlock);
}

void SemaAnalyser::visitForeachLoop(const LgsForeachLoop* foreachLoop) {
    const auto iterExpr = foreachLoop->iterExpr;
    visitUnaryExpr(iterExpr);
    const auto iterable = iterExpr->type->asIterable();
    if (!iterable) {
        return errHandler.handleError(E10002, &iterExpr->location, {iterExpr->prettyName()});
    }
    if (iterable->unpackLength != foreachLoop->loopVars.size()) {
        errHandler.handleError(E10041, &iterExpr->location, {iterExpr->prettyName(), to_string(iterable->unpackLength), to_string(foreachLoop->loopVars.size())});
        return;
    }
    iterable->unpackTypes(foreachLoop->loopVars);
    for (const auto varDec : foreachLoop->loopVars) {
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
    if (rt->isVoid) {
        if (returnStmt->expr) {
            const auto exprType = returnStmt->expr->type;
            if (!exprType->isVoid) {
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
    castExpr->toType = resolveType(castExpr->toType);
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
    } else if (const auto arrayExpr = unaryExpr->asArrayExpr()) {
        visitArrayExpr(arrayExpr);
    } else if (const auto hashMap = unaryExpr->asHashMap()) {
        visitHashMap(hashMap);
    } else if (const auto iterIndex = unaryExpr->asIterIndex()) {
        visitIterIndex(iterIndex);
    } else if (const auto variable = unaryExpr->asVariable()) {
        visitVariable(variable);
    } else if (const auto strConst = unaryExpr->asStrConst()) {
        visitStrConst(strConst);
    }
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
    array->arrType.inferArrayType(array->initialElements);
}

void SemaAnalyser::visitHashMap(LgsHashMap* hashMap) const {
    hashMap->mapType.setBaseType(hashMap->initialElements);
}

void SemaAnalyser::visitStrConst(LgsStrConst* strConst) const {
    const auto size = new LgsIntConst(strConst->value.size());
    strConst->strType.dimsExprs.push_back(size);
}

void SemaAnalyser::visitVariable(LgsVariable* variable) {
    const auto symbol = getSymbol(variable->name, variable);
    if (!symbol) return;
    LgsType* type = nullptr;
    switch (symbol->type) {
    case VAR_DEC:
        symbol->varDec->refs.emplace_back(variable);
        type = symbol->varDec->type;
        break;
    case PARAM:
        symbol->param->refs.emplace_back(variable);
        type = symbol->param->type;
        break;
    case ENUM:
        type = symbol->lgsEnum;
        break;
    case ENUM_FIELD:
        type = symbol->enumField->type;
        break;
    case FUNC:
        // TODO add func matching
        type = symbol->func->overloads[0]->funcType.rt;
        break;
    default:
        assert(false);
    }
    variable->setType(type);
    variable->ref = symbol->clone();
}


void SemaAnalyser::visitSelection(LgsSelection* selection) {
    const auto exprs = selection->exprs;
    visitFirstSelection(exprs[0]);
    visitInnerSelections(selection);
    selection->setType(selection->lastExpr()->type);
}

void SemaAnalyser::visitFirstSelection(LgsExpr* firstExpr) {
    if (const auto variable = dynamic_cast<LgsVariable*>(firstExpr)) {
        visitVariable(variable);
    } else if (const auto funcCall = dynamic_cast<LgsFuncCall*>(firstExpr)) {
        visitFuncCall(funcCall);
    } else if (const auto typeConst = dynamic_cast<LgsTypeConst*>(firstExpr)) {
        typeConst->type = resolveType(typeConst->type);
    } else if (const auto iterIndex = dynamic_cast<LgsIterIndex*>(firstExpr)) {
        visitIterIndex(iterIndex);
    } else if (const auto strConst = dynamic_cast<LgsStrConst*>(firstExpr)) {
        visitStrConst(strConst);
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
            visitFieldSelection(parentExpr, var);
        } else if (const auto methodCall = dynamic_cast<LgsFuncCall*>(childExpr)) {
            visitMethodCall(methodCall, parentExpr->type);
        }
    }
}

void SemaAnalyser::visitFieldSelection(const LgsExpr* parentExpr, LgsVariable* childField) {
    const auto parentType = parentExpr->type;
    const auto field = parentType->getField(childField->name);
    if (!field) {
        return errHandler.handleError(E10005, &childField->location, {childField->getName(), parentType->prettyName()});
    }
    childField->setType(field->type);
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
    instance->type = resolveType(instance->type);
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
    setIterIndexType(iterIndex);
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

void SemaAnalyser::setIterIndexType(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto iterable = baseExpr->type->asIterable();
    if (!iterable) {
        return errHandler.handleError(E10002, &iterIndex->location, {iterIndex->prettyName()});
    }
    const auto iterBaseType = iterable->getBaseType();
    const int diff = iterable->getDims() - iterIndex->indices.size();
    const auto index = iterIndex->indices[diff];
    if (diff > 0) {
        iterIndex->type = iterable->createInnerType(diff, index);
    } else if (diff == 0) {
        if (index->to) {
            iterIndex->type = iterable->createInnerType(diff, index);
        } else {
            iterIndex->type = iterBaseType;
        }
    } else {
        assert(false);
    }
    assert(iterIndex->type);
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
    case BIT_AND:
    case BIT_OR:
    case BIT_XOR:
    case LSHIFT:
    case RSHIFT: {
        const auto lType = binaryExpr->left->type;
        const auto rType = binaryExpr->right->type;
        if (!lType || !rType) return;
        type = lType->inferBinaryType(rType);
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

bool SemaAnalyser::validateExprType(const LgsExpr* expr, LgsType* type) {
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
        return true;
    }
    if (type && expr->type && !expr->type->equals(type)) {
        errHandler.handleError(E10001, &expr->location, {type->prettyName(), expr->type->prettyName()});
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
        break;
    }
    case PARAM: {
        const auto funcType = symbol->varDec->type->asFuncType();
        if (isFuncCallEqual(funcType, funcCall)) break;
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
            errHandler.handleError(E10015, &funcCall->location, {funcCall->name, funcCall->getAsStr(), getOverloadsAsStr(overloads)});
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
    errHandler.handleError(E10034, &methodCall->location, {parentName, methodCall->name, methodCall->getAsStr(), getOverloadsAsStr(overloads)});
    return nullptr;
}

bool SemaAnalyser::isFuncCall(const LgsFuncType* funcType, const LgsFuncCall* funcCall) const {
    if (!funcType) return false;
    if (funcType->hasDefaultParams) {
        return funcType->equalsDefaultParams(funcCall);
    }
    if (funcType->isVariadic) {
        return funcType->equalsVariadic(funcCall);
    }
    return funcType->equals(funcCall);
}

bool SemaAnalyser::isFuncCallEqual(const LgsFuncType* funcType, LgsFuncCall* funcCall) {
    if (isFuncCall(funcType, funcCall)) {
        funcCall->func = new LgsFuncImpl(funcType);
        funcCall->type = funcType->rt;
        return true;
    }
    errHandler.handleError(E10015, &funcCall->location, {funcCall->name, funcCall->getAsStr(), funcType->getAsStr()});
    return false;
}

bool SemaAnalyser::isFuncCallEqual(LgsFunc* func, LgsFuncCall* funcCall) const {
    if (isFuncCall(&func->funcType, funcCall)) {
        funcCall->func = func;
        funcCall->type = func->funcType.rt;
        return true;
    }
    return false;
}

void SemaAnalyser::checkDuplicateFuncs(const vector<LgsFuncImpl*>& overloads) {
    for (size_t i = 0; i < overloads.size(); ++i) {
        const auto overload1 = overloads[i];
        const auto funcType1 = &overload1->funcType;
        for (size_t j = i + 1; j < overloads.size(); ++j) {
            const auto overload2 = overloads[j];
            const auto funcType2 = &overload2->funcType;
            if (funcType1->equals(funcType2)) {
                return errHandler.handleError(E10033, &overload1->location, {funcType1->getAsStr()});
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

LgsType* SemaAnalyser::resolveType(LgsType* type) {
    if (const auto arr = type->asArray()) {
        return resolveArrayType(arr);
    }

    if (!type->isUnknown()) return type;
    auto typeName = type->prettyName();
    const auto nullable = type->isNullable;
    if (globals.symbols.find(typeName) == globals.symbols.end()) {
        errHandler.handleError(E10006, &type->location, {typeName});
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

LgsType* SemaAnalyser::resolveArrayType(LgsArray* array) {
    if (array->baseType->isUnknown()) {
        array->baseType = resolveType(array->baseType);
    }
    auto iterIsConst = true;
    for (const auto sizeExpr : array->dimsExprs) {
        visitExpr(sizeExpr);
        if (!sizeExpr || !sizeExpr->type->equals(&LGS_INT)) {
            iterIsConst = false;
        }
    }
    array->isStatic = iterIsConst;
    return array;
}

void SemaAnalyser::resolveObjMemberTypes(LgsObject* const& obj) {
    for (const auto& [_, field] : obj->fields) {
        field->type = resolveType(field->type);
        field->parent = obj;
    }
    for (const auto& overload : obj->getAllMethods()) {
        resolveFuncTypes(&overload->funcType);
    }
    for (int i = 0; i < obj->implements.size(); ++i) {
        obj->implements[i] = resolveType(obj->implements[i]);
    }
    resolveObjectImplements(obj);
}

void SemaAnalyser::resolveFuncTypes(LgsFuncType* signature) {
    signature->rt = resolveType(signature->rt);
    for (int i = 0; i < signature->params.size(); ++i) {
        signature->params[i]->type = resolveType(signature->params[i]->type);
    }
}

void SemaAnalyser::resolveObjectImplements(LgsObject* obj) {
    for (int i = 0; i < obj->implements.size(); ++i) {
        const auto implement = obj->implements[i];
        if (!implement) continue;
        const auto interface = implement->asInterface();
        if (!interface) {
            errHandler.handleError(E10025, &implement->location, {implement->prettyName()});
            continue;
        }

        vector<LgsFunc*> missingFuncs;
        for (const auto& [name, interfaceOverloads] : interface->methods) {
            const auto& objOverloads = obj->getMethodOverloads(name);
            for (const auto interfaceOverload : interfaceOverloads) {
                auto found = false;
                for (const auto objOverload : objOverloads) {
                    if (!objOverload->funcType.equals(&interfaceOverload->funcType)) continue;
                    objOverload->implements = interfaceOverload;
                    found = true;
                    break;
                }
                if (found) break;
                missingFuncs.emplace_back(interfaceOverload);
            }
        }

        if (!missingFuncs.empty()) {
            errHandler.handleError(E10016, &obj->location, {obj->name, interface->interfaceName, getOverloadsAsStr(missingFuncs)});
        }
    }
}


string SemaAnalyser::getOverloadsAsStr(const vector<LgsMethodImpl*>& overloads) const {
    stringstream str;
    for (const auto& overload : overloads) {
        str << "\n\t     - " << overload->funcType.getAsStr();
    }
    return str.str();
}

string SemaAnalyser::getOverloadsAsStr(const vector<LgsFunc*>& overloads) const {
    stringstream str;
    for (const auto& overload : overloads) {
        str << "\n\t     - " << overload->funcType.getAsStr();
    }
    return str.str();
}
