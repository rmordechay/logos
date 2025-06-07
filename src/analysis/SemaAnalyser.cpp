#include "analysis/SemaAnalyser.h"

#include "data/LgsDefinitions.h"
#include "data/LgsErrors.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsObjectFile.h"
#include "logos/LgsProject.h"
#include "utils/ThreadPool.h"
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
#include "exprs/LgsBinaryExpr.h"
#include "exprs/LgsOperator.h"
#include "exprs/unary/constants/LgsTypeConst.h"
#include "stmts/LgsBreakStmt.h"
#include "types/LgsEnum.h"
#include "exprs/unary/LgsEnumField.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "files/LgsMainFile.h"
#include "logos/LgsConfig.h"
#include "stmts/LgsContinueStmt.h"
#include "stmts/LgsPatternMatch.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsArray.h"
#include <loops/LgsForeachLoop.h>
#include <loops/LgsForLoop.h>
#include <loops/LgsRangeLoop.h>
#include <stmts/LgsAssignment.h>
#include <stmts/LgsIfStmt.h>

void SemaAnalyser::analyseFiles(LogosProject& project) {
    ThreadPool threadPool;
    threadPool.start();
    for (const auto file : project.files) {
        threadPool.runTask([file, &project] {
            SemaAnalyser semaAnalyser(file);
            semaAnalyser.start();
            lock_guard lock(mtx);
            project.errors.insert(project.errors.end(), semaAnalyser.errHandler.errors.begin(), semaAnalyser.errHandler.errors.end());
        });
    }
    threadPool.wait();
    reprocessFuncs(project);
}

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
    }
}

void SemaAnalyser::visitInterface(LgsInterface* interface) const {}

void SemaAnalyser::visitFunc(LgsFunc* func) {
    stack.enterFunc(func);
    func->filePath = file->absPath;
    for (const auto param : func->funcType.params) {
        visitParam(param);
    }
    visitStmtBlock(func->stmtBlock);
    stack.exitFunc();
}

void SemaAnalyser::visitParam(LgsParam* param) {
    if (param->expr) {
        visitExpr(param->expr);
        validateExprType(param->expr, param->type);
    } else if (param->isVariadic) {
        // assert(false);
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
    }
}

void SemaAnalyser::visitField(const LgsField* field) {
    visitExpr(field->expr);
    validateExprType(field->expr, field->type);
}

void SemaAnalyser::visitVarDec(LgsVarDec* varDec) {
    if (varDec->type && varDec->expr) {
        varDec->type = resolveType(varDec->type);
        visitExpr(varDec->expr);
    } else if (varDec->type) {
        varDec->type = resolveType(varDec->type);
        varDec->expr = varDec->type->getZeroValue();
    } else if (varDec->expr) {
        visitExpr(varDec->expr);
        varDec->type = varDec->expr->type;
    } else {
        assert(false);
    }
    validateExprType(varDec->expr, varDec->type);
    addLocalSymbol(varDec->name, LgsSymbol(varDec));
}

void SemaAnalyser::visitAssignment(const LgsAssignment* assignment) {
    const auto rightExpr = assignment->rValue;
    const auto leftExpr = assignment->lValue;
    visitExpr(leftExpr);
    visitExpr(rightExpr);
    validateExprType(rightExpr, leftExpr->type);
}

void SemaAnalyser::visitIfStmt(LgsIfStmt* ifStmt) {
    stack.enterScope(IF_SCOPE, ifStmt);
    visitExpr(ifStmt->ifCond);
    visitStmtBlock(ifStmt->ifStmtBlock);
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
    }
    stack.exitScope(LOOP_SCOPE);
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
        // If type is not defined an error was already thrown
        if (iterExpr->type) {
            errHandler.handleError(E10002, &iterExpr->location, {iterExpr->prettyName()});
        }
        return;
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
    const auto currentFunc = stack.currentFunc;
    auto& funcType = currentFunc->funcType;
    if (returnStmt->expr) {
        returnStmt->expr->isReturnExpr = true;
        currentFunc->returnExprs.push_back(returnStmt->expr);
        visitExpr(returnStmt->expr);
    }
    const auto rt = funcType.rt;
    if (rt->isVoid && returnStmt->expr) {
        errHandler.handleError(E10027, &returnStmt->location, {returnStmt->expr->type->prettyName()});
    } else if (!returnStmt->expr) {
        errHandler.handleError(E10026, &returnStmt->location, {funcType.name, rt->prettyName()});
    } else if (returnStmt->expr->type && !rt->equals(returnStmt->expr->type)) {
        errHandler.handleError(E10004, &returnStmt->location, {funcType.name, rt->prettyName(), returnStmt->expr->type->prettyName()});
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
    if (!castExpr->cast()) {
        errHandler.handleError(E10018, &castExpr->location, {fromValue->type->prettyName(), castExpr->toType->prettyName()});
    }
}

void SemaAnalyser::visitUnaryExpr(LgsUnaryExpr* unaryExpr) {
    if (const auto instance = unaryExpr->asInstance()) {
        visitInstance(instance);
    } else if (const auto funcCall = unaryExpr->asFuncCall()) {
        visitFuncCall(funcCall);
    } else if (const auto func = unaryExpr->asFunc()) {
        visitFunc(func);
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
    const auto& initialElements = array->initialElements;
    for (const auto element : initialElements) {
        visitExpr(element);
    }
    array->arrType.inferArrayType(initialElements);
}

void SemaAnalyser::visitHashMap(LgsHashMap* hashMap) const {
    hashMap->mapType.setBaseType(hashMap->initialElements);
}

void SemaAnalyser::visitStrConst(LgsStrConst* strConst) const {
    const auto size = new LgsIntConst(strConst->value.size());
    strConst->strType.sizeExpr = size;
}

void SemaAnalyser::visitVariable(LgsVariable* variable) {
    const auto symbol = getSymbol(variable->name, variable);
    if (!symbol) return;
    variable->ref = symbol->clone();
    switch (symbol->type) {
    case VAR_DEC:
        symbol->varDec->refs.push_back(variable);
        if (symbol->varDec->expr) {
            symbol->varDec->expr->isReturnExpr = variable->isReturnExpr;
        }
        variable->setType(variable->ref->varDec->type);
        break;
    case PARAM:
        symbol->param->refs.push_back(variable);
        variable->setType(symbol->param->type);
        break;
    case ENUM:
        variable->setType(symbol->lgsEnum);
        break;
    case ENUM_FIELD:
        variable->setType(symbol->enumField->type);
        break;
    case FUNC:
        variable->setType(&symbol->func->funcType);
        break;
    default:
        assert(false);
    }
    assert(variable->ref);
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
    } else if (const auto strConst = firstExpr->asStrConst()) {
        visitStrConst(strConst);
    } else if (const auto typeConst = firstExpr->asTypeConst()) {
        typeConst->type = resolveType(typeConst->type);
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
        return errHandler.handleError(E10005, &childField->location, {childField->getName(), parentType->prettyName()});
    }
    childField->setType(field->type);
    childField->ref = new LgsSymbol(field->clone());
    if (!field->isPublic && file->absPath != field->parent->path) {
        errHandler.handleError(E10030, &childField->location, {childField->getName(), field->parent->name});
    }
}

void SemaAnalyser::visitInstance(LgsInstance* instance) {
    const auto symbol = getSymbol(instance->name, instance);
    if (!symbol) return;
    if (symbol->type != OBJECT) {
        return errHandler.handleError(E10022, &instance->location, {instance->name});
    }
    if (symbol->object->isSingleton) {
        return errHandler.handleError(E10032, &instance->location, {instance->name});
    }

    if (!instance->obj) {
        instance->obj = symbol->object->clone();
        instance->type = instance->obj;
    }

    for (const auto [_, field] : instance->obj->fields) {
        if (field->isConst && !field->expr) {
            errHandler.handleError(E10029, &field->location, {field->name});
            continue;
        }
    }

    for (const auto& arg : instance->args) {
        visitExpr(arg->expr);
        const auto lgsField = instance->obj->getField(arg->name);
        if (!lgsField) {
            errHandler.handleError(E10005, &arg->location, {arg->name, instance->obj->name});
            continue;
        }
        lgsField->expr = arg->expr;
    }

    assert(instance->obj);
}

void SemaAnalyser::visitFuncCall(LgsFuncCall* funcCall) {
    for (const auto arg : funcCall->args) {
        visitExpr(arg);
    }
    const auto symbol = getSymbol(funcCall->name, funcCall);
    if (!symbol) return;

    if (symbol->type == FUNC) {
        const auto func = symbol->func;
        if (funcCall->equals(&func->funcType)) {
            funcCall->func = func;
            funcCall->type = func->funcType.rt;
        } else {
            errHandler.handleError(E10015, &funcCall->location, {funcCall->name, funcCall->prettyName(), func->prettyName()});
        }
        return;
    }

    LgsType* type;
    if (symbol->type == VAR_DEC) {
        type = symbol->varDec->type;
    } else if (symbol->type == PARAM) {
        type = symbol->param->type;
    } else {
        assert(false);
    }

    if (!type->isCallable) return errHandler.handleError(E10046, &funcCall->location, {funcCall->name});
    const auto funcType = type->asFuncType();
    visitAnonymousFunc(funcCall, funcType);
    funcCall->callback = symbol->clone();
}

void SemaAnalyser::visitMethodCall(LgsFuncCall* methodCall, const LgsType* parentType) {
    vector<string> argTypeNames;
    for (const auto& arg : methodCall->args) {
        visitExpr(arg);
        argTypeNames.emplace_back(arg->type->prettyName());
    }
    auto name = methodCall->name;
    const auto method = parentType->findMethod(name);
    if (!method) {
        return errHandler.handleError(E10013, &methodCall->location, {name, parentType->prettyName()});
    }
    if (methodCall->equals(&method->funcType)) {
        methodCall->func = method;
    } else {
        errHandler.handleError(E10034, &methodCall->location, {parentType->prettyName(), name, method->prettyName(), method->funcType.prettyName()});
    }
    checkMethodVisibility(methodCall);
}

void SemaAnalyser::visitAnonymousFunc(LgsFuncCall* funcCall, LgsFuncType* funcType) {
    for (const auto& arg : funcCall->args) {
        visitExpr(arg);
    }
    if (!funcCall->equals(funcType)) {
        errHandler.handleError(E10006, &funcCall->location, {funcCall->name});
        return;
    }
    funcCall->type = funcType->rt;
    funcCall->func = new LgsFunc("", funcType);
}

void SemaAnalyser::visitIterIndex(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    visitUnaryExpr(baseExpr);
    visitExpr(iterIndex->index->from);
    visitExpr(iterIndex->index->to);
    const auto iterable = baseExpr->type->asIterable();
    if (!iterable) {
        return errHandler.handleError(E10002, &iterIndex->location, {iterIndex->baseExpr->prettyName()});
    }
    if (const auto map = iterable->asMap()) {
        iterIndex->setType(map->kvType.value);
    } else {
        iterIndex->setType(iterable->baseType);
    }
    assert(iterIndex->type);
}

void SemaAnalyser::visitGroup(LgsGroup* group) const {
    for (const auto targetSymbol : group->targetSymbols) {
        for (const auto type : group->types) {
            const auto method = type->getMethod(targetSymbol->name);
            if (!method) continue;
            method->funcType.isVirtual = true;
            group->addMethod(method);
        }
    }
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
    default:
        break;
    }
    binaryExpr->setType(type);
}

void SemaAnalyser::validateExprType(const LgsExpr* expr, LgsType* type) {
    if (!expr) return;
    if (expr->isNull) {
        // null must have a type
        if (!type) {
            errHandler.handleError(E10024, &expr->location);
            return;
        }
        // type must be nullable
        if (!type->isNullable) {
            errHandler.handleError(E10023, &type->location, {type->prettyName(), type->prettyName()});
        }
        return;
    }
    if (type && expr->type &&  !expr->type->equals(type)) {
        return errHandler.handleError(E10001, &expr->location, {type->prettyName(), expr->type->prettyName()});
    }
}

void SemaAnalyser::checkMethodVisibility(const LgsFuncCall* methodCall) {
    const auto method = methodCall->func;
    if (!method) return;
    if (!method->funcType.isPublic && file->absPath != method->filePath) {
        errHandler.handleError(E10031, &method->location, {method->funcType.name, method->funcType.parentName});
    }
}

void SemaAnalyser::validateFuncControlFlow(const LgsFunc* func) {
    if (func->funcType.rt->isVoid) return;
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
        auto& symbols = stack.top().symbols;
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
    stack.addSymbol(name, symbol);
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
    switch (symbol->type) {
    case ENUM_FIELD:
        symbol->enumField->parent->isNullable = nullable;
        newType = symbol->enumField->parent;
        break;
    case FUNC:
        newType = &symbol->func->funcType;
        break;
    case OBJECT:
        symbol->object->isNullable = nullable;
        newType = symbol->object;
        break;
    case INTERFACE:
        symbol->interface->isNullable = nullable;
        newType = symbol->interface;
        break;
    case GROUP:
        symbol->group->isNullable = nullable;
        newType = symbol->group;
        break;
    case ENUM:
        symbol->lgsEnum->isNullable = nullable;
        newType = symbol->lgsEnum;
        break;
    case VAR_DEC:
    case PARAM:
    case FIELD:
    case UNKNOWN:
        break;
    }
    assert(newType);
    return newType;
}

LgsType* SemaAnalyser::resolveArrayType(LgsArray* array) {
    if (array->baseType->isUnknown()) {
        array->baseType = resolveType(array->baseType);
    }
    const auto sizeExpr = array->sizeExpr;
    visitExpr(sizeExpr);
    return array;
}

void SemaAnalyser::resolveObjMemberTypes(LgsObject* const& obj) {
    for (const auto& [_, field] : obj->fields) {
        field->type = resolveType(field->type);
        field->parent = obj;
    }
    for (const auto& [_, method] : obj->methods) {
        resolveFuncTypes(&method->funcType);
    }
    for (int i = 0; i < obj->implements.size(); ++i) {
        obj->implements[i] = resolveType(obj->implements[i]);
    }
    resolveObjectImplements(obj);
}

void SemaAnalyser::resolveFuncTypes(LgsFuncType* funcType) {
    for (int i = 0; i < funcType->params.size(); ++i) {
        funcType->params[i]->type = resolveType(funcType->params[i]->type);
    }
    funcType->rt = resolveType(funcType->rt);
    if (!funcType->rt->isVoid) {
        funcType->isRvBig = funcType->rt->getSizeBytes() > PARAM_SWAP_SIZE_THRESHOLD;
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
        for (const auto& [name, interfaceFunc] : interface->methods) {
            const auto objMethod = obj->findMethod(name);
            if (objMethod && objMethod->funcType.equals(&interfaceFunc->funcType)) {
                objMethod->implements = interfaceFunc;
                continue;
            }
            missingFuncs.emplace_back(interfaceFunc);
        }

        if (!missingFuncs.empty()) {
            errHandler.handleError(E10016, &obj->location, {obj->name, interface->interfaceName, getFuncsAsStr(missingFuncs)});
        }
    }
}

void SemaAnalyser::resolveGroupTypes(LgsGroup* group) {
    for (int i = 0; i < group->types.size(); ++i) {
        group->types[i] = resolveType(group->types[i]);
    }
}

string SemaAnalyser::getFuncsAsStr(const vector<LgsFunc*>& funcs) const {
    stringstream str;
    for (const auto& func : funcs) {
        str << "\n\t     - " << func->funcType.prettyName();
    }
    return str.str();
}

void SemaAnalyser::reprocessFuncs(const LogosProject& project) {
    for (const auto& file : project.files) {
        SemaAnalyser semaAnalyser(file);
        if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
            for (const auto& obj : mainFile->objects) {
                for (const auto& [_, method] : obj->methods) {
                    method->swapReturnIfNeeded();
                }
                for (const auto implement : obj->implements) {
                    assert(false);
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
            for (const auto implement : obj->implements) {
                assert(false);
            }
        } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
            for (const auto& [_, method] : interfaceFile->interface->methods) {
                method->swapReturnIfNeeded();
            }
        }
    }
}
