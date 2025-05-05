#include "SemaAnalyser.h"
#include "LgsErrors.h"
#include "LgsGlobals.h"
#include "LgsInterfaceFile.h"
#include "LgsObjectFile.h"
#include "ThreadPool.h"
#include "exprs/LgsCast.h"
#include "exprs/LgsNull.h"
#include "stmts/LgsField.h"
#include "stmts/LgsReturn.h"
#include "types/LgsBool.h"
#include "exprs/unary/LgsDArray.h"
#include "exprs/unary/LgsArrayIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/binary/LgsBinaryExpr.h"
#include "exprs/unary/constants/LgsTypeConst.h"
#include "stmts/LgsBreakStmt.h"
#include "types/LgsEnum.h"
#include "exprs/unary/LgsEnumField.h"
#include "exprs/unary/LgsSArray.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsContinueStmt.h"
#include "stmts/LgsPatternMatch.h"
#include "types/LgsArray.h"
#include "types/LgsVoid.h"

#include <loops/LgsForeachLoop.h>
#include <loops/LgsLoop.h>
#include <loops/LgsRangeLoop.h>
#include <stmts/LgsAssignment.h>
#include <stmts/LgsIfStmt.h>

void SemaAnalyser::analyseFiles(const vector<LgsFile*>& files, vector<LgsError>& errors) {
    ThreadPool threadPool;
    threadPool.start();
    for (const auto& file : files) {
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
    visitObjectImplements(obj);
}

void SemaAnalyser::visitInterface(LgsInterface* interface) {

}

void SemaAnalyser::visitFunc(LgsFunc* func) {
    func->path = file->absPath;
    lgsStack.enterScope(func);
    visitFuncType(func->getFuncType());
    visitStmtBlock(func->stmtBlock);
    lgsStack.exitScope();
    validateFuncControlFlow(func);
}

void SemaAnalyser::visitFuncType(LgsFuncType* funcType) {
    for (auto& param : funcType->params) {
        visitParam(&param);
    }
}

void SemaAnalyser::visitParam(LgsParam* param) {
    addLocalSymbol(param->name, LgsSymbol(param));
    visitExpr(param->expr);
    checkExprType(param->expr, param->type);
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
    } else if (const auto arrIndex = dynamic_cast<LgsArrayIndex*>(lExpr)) {
        visitArrayIndex(arrIndex);
    } else {
        assert(false);
    }
    checkExprType(lExpr, rExpr->type);
}

void SemaAnalyser::visitVarDec(LgsVarDec* varDec) {
    if (varDec->expr) {
        visitExpr(varDec->expr);
        varDec->expr->type = resolveType(varDec->expr->type, &errHandler);
        varDec->type = varDec->expr->type;
        if (!checkExprType(varDec->expr, varDec->type)) return;
    } else {
        varDec->type = resolveType(varDec->type, &errHandler);
        varDec->expr = varDec->type->getZeroValue();
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
            return errHandler.handleError(E10014, &patternExpr->location, {patternExpr->type->getName(), baseExprType->getName()});
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
    const auto iterableExpr = foreachLoop->expr;
    visitUnaryExpr(iterableExpr);
    const auto iterable = iterableExpr->type->asIterable();
    if (!iterable) {
        return errHandler.handleError(E10002, &iterableExpr->location, {iterableExpr->getName()});
    }
    // TODO check all loop vars
    for (const auto varDec : foreachLoop->loopVars) {
        varDec->type = iterable->underlyingType;
        addLocalSymbol(varDec->name, LgsSymbol(varDec));
    }
    visitStmtBlock(foreachLoop->stmtBlock);
}

void SemaAnalyser::visitReturnStmt(const LgsReturn* returnStmt) {
    auto funcSignature = lgsStack.currentFunc->getFuncType();
    const auto rt = funcSignature->type;
    if (returnStmt->expr) {
        returnStmt->expr->isReturnValue = true;
        visitExpr(returnStmt->expr);
    }
    if (rt->isVoid()) {
        if (returnStmt->expr) {
            const auto exprType = returnStmt->expr->type;
            if (!exprType->isVoid()) {
                errHandler.handleError(E10027, &returnStmt->location, {funcSignature->name, rt->getName(), exprType->getName()});
                return;
            }
        }
    } else if (!returnStmt->expr) {
        return errHandler.handleError(E10026, &returnStmt->location, {funcSignature->name, rt->getName()});
    } else if (!rt->equals(returnStmt->expr->type)) {
        return errHandler.handleError(E10027, &returnStmt->location, {funcSignature->name, rt->getName(), returnStmt->expr->type->getName()});
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
        errHandler.handleError(E10018, &castExpr->location, {fromValue->type->getName(), castExpr->toType->getName()});
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
    } else if (const auto arrIndex = unaryExpr->asArrayIndex()) {
        visitArrayIndex(arrIndex);
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
    array->arrType.underlyingType = array->initialElements[0]->type;
}

void SemaAnalyser::visitSArray(LgsSArray* array) {
    for (const auto& element : array->initialElements) {
        visitExpr(element);
    }
    array->arrType.underlyingType = array->initialElements[0]->type;
    array->arrType.sizes.emplace_back(array->initialElements.size());
}

void SemaAnalyser::visitHashMap(LgsHashMap* hashMap) {
    assert(false);
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
        setExprType(variable, symbol->func[0]->getFuncType()->type);
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
    } else if (const auto arrIndex = dynamic_cast<LgsArrayIndex*>(firstExpr)) {
        visitArrayIndex(arrIndex);
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
        return errHandler.handleError(E10005, &childField->location, {childField->getName(), parentType->getName()});
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
        argTypeNames.emplace_back(arg->type->getName());
    }

    const auto funcCallName = funcCall->name;
    const auto symbol = lgsStack.getSymbol(funcCallName);
    if (!symbol) return errHandler.handleError(E10006, &funcCall->location, {funcCallName});
    resolveFuncCall(funcCall, symbol);
}

void SemaAnalyser::visitMethodCall(LgsFuncCall* methodCall, const LgsType* parentType) {
    vector<string> argTypeNames;
    for (const auto& arg : methodCall->args) {
        visitExpr(arg);
        argTypeNames.emplace_back(arg->type->getName());
    }
    auto name = methodCall->name;
    const auto overloads = parentType->getMethodsOverloads(name);
    if (overloads.empty()) {
        return errHandler.handleError(E10013, &methodCall->location, {name});
    }
    if (!resolveMethodCall(overloads, methodCall, parentType->getName())) return;
    checkMethodVisibility(methodCall);
}

void SemaAnalyser::visitInstance(LgsInstance* instance) {
    instance->type = resolveType(instance->type, &errHandler);
    if (!instance->type) return;
    const auto symbol = getSymbol(instance->type->getName(), instance);
    if (!symbol) return;
    if (symbol->type != OBJECT) {
        return errHandler.handleError(E10022, &instance->location, {instance->type->getName()});
    }
    if (symbol->object->isSingleton) {
        return errHandler.handleError(E10032, &instance->location, {instance->type->getName()});
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

void SemaAnalyser::visitArrayIndex(LgsArrayIndex* arrIndex) {
    const auto baseExpr = arrIndex->baseExpr;
    visitUnaryExpr(baseExpr);
    const auto baseExprType = baseExpr->type;
    if (baseExprType->isIterable()) {
        const bool arrDimsValid = checkArrDimensions(arrIndex);
        if (!arrDimsValid) return;
        const bool indexBoundariesValid = checkIndexBoundaries(arrIndex);
        if (!indexBoundariesValid) return;
        setArrayIndexType(arrIndex);
    } else {
        return errHandler.handleError(E10002, &arrIndex->location, {baseExpr->getName()});
    }
}

void SemaAnalyser::visitObjectImplements(LgsObject* obj) {
    for (int i = 0; i < obj->implements.size(); ++i) {
        const auto implement = obj->implements[i];
        if (!implement) continue;
        const auto interface = implement->asInterface();
        if (!interface) {
            errHandler.handleError(E10025, &implement->location, {implement->getName()});
            continue;
        }

        vector<LgsFunc*> missingFuncs;
        for (const auto& [name, interfaceOverloads] : interface->methods) {
            const auto objOverloads = obj->getMethodsOverloads(name);
            auto found = false;
            for (const auto& interfaceOverload : interfaceOverloads) {
                for (const auto& objOverload : objOverloads) {
                    if (objOverload->getFuncType()->equals(interfaceOverload->getFuncType())) {
                        objOverload->implements = interfaceOverload;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    missingFuncs.emplace_back(interfaceOverload);
                }
            }
        }
        if (!missingFuncs.empty()) {
            errHandler.handleError(E10016, &obj->location, {obj->name, interface->name, getOverloadsAsStr(missingFuncs)});
        }
    }
}

void SemaAnalyser::setExprType(LgsExpr* expr, LgsType* type) {
    expr->type = resolveType(type, &errHandler);
}

bool SemaAnalyser::setSelectionFieldType(const LgsUnaryExpr* parent, LgsVariable* fieldVariable) {
    const auto type = parent->type;
    const auto field = type ? type->getField(fieldVariable->name) : nullptr;
    if (!type || !field) {
        errHandler.handleError(E10005, &fieldVariable->location, {fieldVariable->getName(), type->getName()});
        return false;
    }
    if (!field->isPublic) {}
    setExprType(fieldVariable, field->type);
    return true;
}

void SemaAnalyser::setArrayIndexType(LgsArrayIndex* arrIndex) const {
    assert(arrIndex->baseExpr->type);
    const auto iterable = arrIndex->baseExpr->type->asIterable();
    const auto sizeDefinition = iterable->getDims();
    const auto sizeCall = arrIndex->indices.size();
    assert(sizeDefinition >= sizeCall);
    const auto diff = sizeDefinition - sizeCall;
    if (diff == 0) {
        arrIndex->type = iterable->underlyingType;
    } else {
        const vector sizes(iterable->sizes.begin() + diff, iterable->sizes.end());
        assert(false);
        return;
    }
    assert(arrIndex->type);
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
    if (expr->isNull()) {
        // null must have a type
        if (!type) {
            errHandler.handleError(E10024, &expr->location);
            return false;
        }
        // type must be nullable
        if (!type->nullable) {
            errHandler.handleError(E10023, &type->location, {type->getName(), type->getName()});
            return false;
        }
        expr->type = type;
        return true;
    }
    if (type && expr->type && !expr->type->equals(type)) {
        errHandler.handleError(E10001, &expr->location, {type->getName(), expr->type->getName()});
        return false;
    }
    return true;
}

bool SemaAnalyser::checkIndexBoundaries(LgsArrayIndex* arrIndex) {
    vector<size_t> boundaries;
    if (const auto var = arrIndex->baseExpr->asVariable()) {
        const auto ref = var->ref;
        if (ref->type == VAR_DEC) {
            const auto iterable = ref->varDec->type->asIterable();
            boundaries = iterable->sizes;
        }
    }
    assert(!boundaries.empty());
    bool valid = false;
    for (int i = 0; i < arrIndex->indices.size(); ++i) {
        const auto upperBound = boundaries[i];
        const auto index = arrIndex->indices[i];
        visitExpr(index->from);
        if (index->to) {
            visitExpr(index->to);
            valid = checkSliceBoundaries(arrIndex, index, i, upperBound);
        } else {
            valid = checkSingleIndexBoundaries(arrIndex, index->from, upperBound);
        }
        if (!valid) break;
    }
    return valid;
}

bool SemaAnalyser::checkSingleIndexBoundaries(LgsArrayIndex* arrIndex, LgsExpr* index, const size_t upperBound) {
    if (!index->type->asInt()) {
        errHandler.handleError(E10036, &arrIndex->location, {arrIndex->getNameWithTypes()});
        return false;
    }
    bool outOfBounds = false;
    if (const auto indexInt = index->asIntConst()) {
        outOfBounds = indexInt->value >= upperBound;
    }
    if (outOfBounds) {
        errHandler.handleError(E10003, &arrIndex->location, {arrIndex->code});
        return false;
    }
    return true;
}

bool SemaAnalyser::checkSliceBoundaries(LgsArrayIndex* arrIndex, const LgsIndex* index, const size_t dimension, const size_t upperBound) {
    bool valid = checkSingleIndexBoundaries(arrIndex, index->from, upperBound);
    if (!valid) return false;
    valid = checkSingleIndexBoundaries(arrIndex, index->to, upperBound);
    if (!valid) return false;
    const auto fromIntConst = index->from->asIntConst()->value;
    const auto toIntConst = index->to->asIntConst()->value;
    if (fromIntConst >= toIntConst) {
        errHandler.handleError(E10037, &arrIndex->location, {arrIndex->code});
        return false;
    }
    return true;
}

bool SemaAnalyser::checkArrDimensions(const LgsArrayIndex* arrIndex) {
    int maxIndexLevel = -1;
    if (const auto var = arrIndex->baseExpr->asVariable()) {
        const auto ref = var->ref;
        if (ref->type == VAR_DEC) {
            const auto expr = ref->varDec->expr;
            const auto iterable = expr->type->asIterable();
            maxIndexLevel = iterable->sizes.size();
        }
    }
    assert(maxIndexLevel >= 0);
    if (arrIndex->indices.size() > maxIndexLevel) {
        errHandler.handleError(E10035, &arrIndex->location, {arrIndex->code, to_string(maxIndexLevel)});
        return false;
    }
    return true;
}

bool SemaAnalyser::resolveFuncCall(LgsFuncCall* funcCall, const LgsSymbol* symbol) {
    if (symbol->type == PARAM) {
        const auto funcType = dynamic_cast<LgsFuncType*>(symbol->param->type);
        if (isFuncCallEqual(funcType, funcCall)) {
            funcCall->funcType = funcType;
            funcCall->type = funcType->type;
            funcCall->ref = symbol->clone();
            return true;
        }
    }
    if (symbol->type == FUNC && !resolveFuncCall(symbol->func, funcCall)) {
        return true;
    }
    assert(funcCall->funcType);
    return false;
}

LgsFunc* SemaAnalyser::resolveFuncCall(const vector<LgsFunc*>& overloads, LgsFuncCall* funcCall) {
    for (const auto overload : overloads) {
        const auto funcType = overload->getFuncType();
        if (isFuncCallEqual(funcType, funcCall)) {
            funcCall->func = overload;
            funcCall->funcType = funcType;
            funcCall->type = funcType->type;
            return overload;
        }
    }
    errHandler.handleError(E10015, &funcCall->location, {funcCall->name, funcCall->getSignatureText(), getOverloadsAsStr(overloads)});
    return nullptr;
}

LgsFunc* SemaAnalyser::resolveMethodCall(const vector<LgsMethodImpl*>& overloads, LgsFuncCall* methodCall, const string& parentName) {
    for (const auto overload : overloads) {
        const auto funcType = overload->getFuncType();
        if (isFuncCallEqual(funcType, methodCall)) {
            methodCall->func = overload;
            methodCall->funcType = funcType;
            methodCall->type = funcType->type;
            return overload;
        }
    }
    errHandler.handleError(E10034, &methodCall->location, {parentName, methodCall->name, methodCall->getSignatureText(), getOverloadsAsStr(overloads)});
    return nullptr;
}

bool SemaAnalyser::resolveFuncCallWithDefaultParams(const LgsFuncType* funcType, const LgsFuncCall* funcCall) const {
    const auto params = funcType->params;
    const auto argsSize = funcCall->args.size();
    for (size_t i = funcCall->isMethodCall; i < params.size(); ++i) {
        const auto param = params[i];
        if (i >= argsSize) continue;
        const auto arg = funcCall->args[i];
        if (!param.type->equals(arg->type)) return false;
    }
    return true;
}

bool SemaAnalyser::isFuncCallEqual(const LgsFuncType* funcType, const LgsFuncCall* funcCall) const {
    if (!funcType) return false;
    if (funcType->hasDefaultParams) {
        return resolveFuncCallWithDefaultParams(funcType, funcCall);
    }
    return funcType->equals(funcCall);
}

void SemaAnalyser::checkDuplicateFuncs(const vector<LgsFuncImpl*>& overloads) {
    for (size_t i = 0; i < overloads.size(); ++i) {
        const auto overload1 = overloads[i];
        for (size_t j = i + 1; j < overloads.size(); ++j) {
            const auto overload2 = overloads[j];
            const auto funcType1 = overload1->getFuncType();
            const auto funcType2 = overload2->getFuncType();
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
    const auto method = dynamic_cast<LgsMethodImpl*>(methodCall->func);
    assert(method);
    if (!method->isPublic && file->absPath != method->path) {
        errHandler.handleError(E10031, &method->location, {method->getFuncType()->name, method->parentName});
    }
}

void SemaAnalyser::validateFuncControlFlow(LgsFunc* func) {
    const auto funcType = func->getFuncType();
    if (dynamic_cast<LgsVoid*>(funcType->type)) return;
    const auto stmtBlock = func->stmtBlock;
    const bool isFlowCorrect = funcType->name != LOGOS_MAIN_FUNC && !stmtBlock->hasReturn;
    if (isFlowCorrect) {
        errHandler.handleError(E10004, &func->location, {funcType->name, funcType->type->getName()});
    }
}

string SemaAnalyser::getOverloadsAsStr(const vector<LgsMethodImpl*>& overloads) const {
    stringstream str;
    for (const auto& overload : overloads) {
        str << "\n\t     - " << overload->getFuncType()->getAsStr();
    }
    return str.str();
}

string SemaAnalyser::getOverloadsAsStr(const vector<LgsFunc*>& overloads) const {
    stringstream str;
    for (const auto& overload : overloads) {
        str << "\n\t     - " << overload->getFuncType()->getAsStr();
    }
    return str.str();
}

LgsSymbol* SemaAnalyser::getSymbol(const string& name, const LgsValue* value) {
    const auto symbol = lgsStack.getSymbol(name);
    if (!symbol) errHandler.handleError(E10006, &value->location, {name});
    return symbol;
}

void SemaAnalyser::addLocalSymbol(const string&name, const LgsSymbol& symbol) {
    if (lgsStack.getSymbol(name)) {
        const auto location = symbol.getLocation();
        return errHandler.handleError(E10011, location, {name, to_string(location->lineNumber)});
    }
    lgsStack.addLocalSymbol(name, symbol);
}

LgsType* SemaAnalyser::resolveType(LgsType* type, LgsErrorHandler* errorHandler) {
    assert(type);
    if (const auto iterable = type->asIterable()) {
        if (dynamic_cast<LgsUnknownType*>(iterable->underlyingType)) {
            iterable->underlyingType = resolveType(iterable->underlyingType, errorHandler);
        }
        return type;
    }

    if (!dynamic_cast<LgsUnknownType*>(type)) return type;
    auto typeName = type->getName();
    const auto nullable = type->nullable;
    if (globals.symbols.find(typeName) == globals.symbols.end()) {
        errorHandler->handleError(E10006, &type->location, {typeName});
        return nullptr;
    }

    const auto symbol = &globals.symbols[typeName];
    delete type;
    LgsType* newType = nullptr;
    if (symbol->type == OBJECT) {
        symbol->object->nullable = nullable;
        newType = symbol->object;
    }
    if (symbol->type == INTERFACE) {
        symbol->interface->nullable = nullable;
        newType = symbol->interface;
    }
    if (symbol->type == ENUM) {
        symbol->lgsEnum->nullable = nullable;
        newType = symbol->lgsEnum;
    }
    if (symbol->type == ENUM_FIELD) {
        symbol->enumField->parent->nullable = nullable;
        newType = symbol->enumField->parent;
    }
    assert(newType);
    return newType;
}

void SemaAnalyser::resolveGlobalTypes(const vector<LgsFile*>& files, LgsErrorHandler* errHandler) {
    for (const auto& file : files) {
        if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
            for (const auto& object : mainFile->objects) {
                resolveObjMemberTypes(object, errHandler);
            }
            for (const auto& func : mainFile->getAllFuncs()) {
                resolveFuncTypes(func->getFuncType(), errHandler);
            }
        } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
            resolveObjMemberTypes(objFile->obj, errHandler);
        } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
            auto overloads = interfaceFile->interface->getAllMethods();
            for (const auto& overload : overloads) {
                resolveFuncTypes(overload->getFuncType(), errHandler);
            }
        }
    }
}

void SemaAnalyser::resolveObjMemberTypes(LgsObject* const& obj, LgsErrorHandler* errHandler) {
    for (const auto& [_, field] : obj->fields) {
        field->type = resolveType(field->type, errHandler);
        field->parent = obj;
    }
    for (const auto& overload : obj->getAllMethods()) {
        resolveFuncTypes(overload->getFuncType(), errHandler);
    }
    for (int i = 0; i < obj->implements.size(); ++i) {
        obj->implements[i] = resolveType(obj->implements[i], errHandler);
    }
}

void SemaAnalyser::resolveFuncTypes(LgsFuncType* signature, LgsErrorHandler* errHandler) {
    signature->type = resolveType(signature->type, errHandler);
    for (int i = 0; i < signature->params.size(); ++i) {
        const auto lgsParam = signature->params[i];
        signature->params[i].type = resolveType(signature->params[i].type, errHandler);
    }
}