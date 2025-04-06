#include "SemaAnalyser.h"
#include "LgsErrors.h"
#include "LgsGlobals.h"
#include "LgsInterfaceFile.h"
#include "exprs/LgsCast.h"
#include "exprs/LgsNull.h"
#include "stmts/LgsField.h"
#include "stmts/LgsReturn.h"
#include "types/LgsArrayType.h"
#include "types/LgsBool.h"

#include "exprs/unary/LgsArray.h"
#include "exprs/unary/LgsArrayIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/binary/LgsBinaryExpr.h"
#include "exprs/unary/constants/LgsTypeConst.h"
#include "stmts/LgsBreakStmt.h"
#include "stmts/LgsEnum.h"
#include "stmts/LgsPatternMatching.h"
#include <loops/LgsForeachLoop.h>
#include <loops/LgsLoop.h>
#include <loops/LgsRangeLoop.h>
#include <stmts/LgsAssignment.h>
#include <stmts/LgsIfStmt.h>

void SemaAnalyser::analyse() {
    if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
        visitMainFile(mainFile);
    } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
        visitObjectFile(objFile);
    } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
        visitInterfaceFile(interfaceFile);
    }
}

void SemaAnalyser::visitMainFile(const LgsMainFile* mainFile) {
    for (const auto& obj : mainFile->objects) {
        visitObject(obj);
    }
    for (const auto& lgsEnum : mainFile->enums) {
        visitEnum(lgsEnum);
    }
    for (const auto& func : mainFile->funcs) {
        visitFuncImpl(func);
    }
    visitFuncImpl(mainFile->mainFunc);
}

void SemaAnalyser::visitObjectFile(const LgsObjectFile* objectFile) {
    visitObject(objectFile->obj);
}

void SemaAnalyser::visitInterfaceFile(const LgsInterfaceFile* interfaceFile) {
    visitInterface(interfaceFile->interface);
}

void SemaAnalyser::visitObject(LgsObject* obj) {
    for (const auto& [_, field] : obj->fields) {
        visitField(field);
    }
    for (const auto& [_, method] : obj->methods) {
        for (const auto& overload : method) {
            visitMethodImpl(overload);
        }
    }
    checkObjectImplements(obj);
}

void SemaAnalyser::visitInterface(const LgsInterface* interface) {
    for (const auto& funcSignature : interface->funcSignatures) {
        for (const auto& param : funcSignature->params) {
            visitParam(param);
        }
    }
}

void SemaAnalyser::visitFuncImpl(LgsFuncImpl* func) {
    globals.addFunc(func);
    logosStack.enterScope(func);
    setFuncType(func);
    for (const auto& param : func->signature.params) {
        visitParam(param);
    }
    visitStmtBlock(func->stmtBlock);
    logosStack.exitScope();
}

void SemaAnalyser::visitMethodImpl(LgsMethodImpl* method) {
    logosStack.enterScope(method);
    setFuncType(method);
    for (const auto& param : method->signature.params) {
        visitParam(param);
    }
    visitStmtBlock(method->stmtBlock);
    logosStack.exitScope();
}

void SemaAnalyser::visitParam(LgsParam* param) {
    addLocalSymbol(param->name, LgsSymbol(param));
}

void SemaAnalyser::visitStmt(LgsStmt* stmt) {
    if (const auto varDec = dynamic_cast<LgsVarDec*>(stmt)) {
        visitVarDec(varDec);
    } else if (const auto ifStmt = dynamic_cast<LgsIfStmt*>(stmt)) {
        visitIfStmt(ifStmt);
    } else if (const auto patternMatching = dynamic_cast<LgsPatternMatching*>(stmt)) {
        visitPatternMatching(patternMatching);
    } else if (const auto loopStmt = dynamic_cast<LgsLoop*>(stmt)) {
        visitLoopStmt(loopStmt);
    } else if (const auto fieldDef = dynamic_cast<LgsAssignment*>(stmt)) {
        visitAssignment(fieldDef);
    } else if (const auto funcCall = dynamic_cast<LgsFuncCall*>(stmt)) {
        visitFuncCall(funcCall);
    } else if (const auto selection = dynamic_cast<LgsSelection*>(stmt)) {
        visitSelection(selection);
    } else if (const auto returnStmt = dynamic_cast<LgsReturn*>(stmt)) {
        visitReturnStmt(returnStmt);
    } else if (const auto enumDec = dynamic_cast<LgsEnum*>(stmt)) {
        visitEnum(enumDec);
    } else if (const auto breakStmt = dynamic_cast<LgsBreakStmt*>(stmt)) {
        visitBreakStmt(breakStmt);
    }
}

void SemaAnalyser::visitStmtBlock(const LgsStmtBlock* stmtBlock) {
    if (!stmtBlock) return;
    for (const auto& stmt : stmtBlock->stmts) {
        visitStmt(stmt);
    }
}

void SemaAnalyser::visitField(const LgsField* field) {
    if (!checkExprType(field->expr, field->userType)) return;
}

void SemaAnalyser::visitAssignment(const LgsAssignment* assignment) {
    if (const auto selection = dynamic_cast<LgsSelection*>(assignment->lvalue)) {
        visitSelection(selection);
    }
    visitExpr(assignment->rvalue);
    if (!checkExprType(assignment->rvalue, assignment->lvalue->type)) return;
}

void SemaAnalyser::visitVarDec(LgsVarDec* varDec) {
    const auto userType = varDec->userType;
    const auto expr = varDec->expr;
    if (!expr) {
        varDec->type = userType;
        varDec->expr = varDec->type->getZeroValue();
    } else if (dynamic_cast<LgsNull*>(expr) && userType->nullable) {
        varDec->type = userType;
    } else {
        visitExpr(expr);
        if (!checkExprType(expr, userType)) return;
        varDec->type = expr->type;
    }
    addLocalSymbol(varDec->name, LgsSymbol(varDec));
}

void SemaAnalyser::visitIfStmt(const LgsIfStmt* ifStmt) {
    visitExpr(ifStmt->ifCond);
    visitStmtBlock(ifStmt->ifStmtBlock);
    for (const auto& elseIfStmtBlock : ifStmt->elseIfStmtBlocks) {
        visitStmtBlock(elseIfStmtBlock);
    }
    visitStmtBlock(ifStmt->elseStmtBlock);
}

void SemaAnalyser::visitPatternMatching(const LgsPatternMatching* patternMatching) {
    const auto baseExpr = patternMatching->expr;
    if (!baseExpr) {
        visitBoolPatternMatching(patternMatching);
        return;
    }
    visitExpr(baseExpr);
    const auto baseExprType = baseExpr->type;
    for (const auto patternExpr : patternMatching->patterns) {
        visitExpr(patternExpr);
        if (!patternExpr->type->equals(baseExprType)) {
            handleError(E10014, &patternExpr->location, {patternExpr->type->getName(), baseExprType->getName()});
            return;
        }
    }
    for (const auto& patternsStmtBlock : patternMatching->patternsStmtBlocks) {
        visitStmtBlock(patternsStmtBlock);
    }
    visitStmtBlock(patternMatching->elseStmtBlock);
}

void SemaAnalyser::visitBoolPatternMatching(const LgsPatternMatching* patternMatching) {

}

void SemaAnalyser::visitLoopStmt(LgsLoop* loopStmt) {
    logosStack.enterScope();
    logosStack.currentLoop = loopStmt;
    if (const auto rangeLoop = dynamic_cast<LgsRangeLoop*>(loopStmt)) {
        visitRangeLoop(rangeLoop);
    } else if (const auto foreachLoop = dynamic_cast<LgsForeachLoop*>(loopStmt)) {
        visitForeachLoop(foreachLoop);
    }
    logosStack.currentLoop = nullptr;
    logosStack.exitScope();
}

void SemaAnalyser::visitRangeLoop(const LgsRangeLoop* rangeLoop) {
    // TODO check all loop vars
    const auto loopVar = rangeLoop->loopVars[0];
    addLocalSymbol(loopVar->name, LgsSymbol(loopVar));
    visitStmtBlock(rangeLoop->stmtBlock);
}

void SemaAnalyser::visitForeachLoop(const LgsForeachLoop* foreachLoop) {
    const auto iterableExpr = foreachLoop->iterableExpr;
    visitUnaryExpr(iterableExpr);
    if (!foreachLoop->getExprAsIterable()) {
        handleError(E10002, &iterableExpr->location, {iterableExpr->getName()});
        return;
    }
    // TODO check all loop vars
    const auto loopVar = foreachLoop->loopVars[0];
    loopVar->type = dynamic_cast<LgsArrayType*>(iterableExpr->type)->underlyingType;
    addLocalSymbol(loopVar->name, LgsSymbol(loopVar));
    visitStmtBlock(foreachLoop->stmtBlock);
}

void SemaAnalyser::visitReturnStmt(const LgsReturn* returnStmt) {
    visitExpr(returnStmt->expr);
}

void SemaAnalyser::visitBreakStmt(LgsBreakStmt* breakStmt) {
}

void SemaAnalyser::visitEnum(LgsEnum* lgsEnum) {

}

void SemaAnalyser::visitExpr(LgsExpr* expr) {
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
        handleError(E10018, &castExpr->location, {fromValue->type->getName(), castExpr->toType->getName()});
    }
}

void SemaAnalyser::visitUnaryExpr(LgsUnaryExpr* unaryExpr) {
    if (const auto instance = dynamic_cast<LgsInstance*>(unaryExpr)) {
        visitInstance(instance);
    } else if (const auto funcCall = dynamic_cast<LgsFuncCall*>(unaryExpr)) {
        visitFuncCall(funcCall);
    } else if (const auto selection = dynamic_cast<LgsSelection*>(unaryExpr)) {
        visitSelection(selection);
    } else if (const auto array = dynamic_cast<LgsArray*>(unaryExpr)) {
        visitArray(array);
    } else if (const auto arrIndex = dynamic_cast<LgsArrayIndex*>(unaryExpr)) {
        visitArrayIndex(arrIndex);
    } else if (const auto variable = dynamic_cast<LgsVariable*>(unaryExpr)) {
        visitVariable(variable);
    }
}

void SemaAnalyser::visitBinaryExpr(LgsBinaryExpr* binaryExpr) {
    visitExpr(binaryExpr->left);
    visitExpr(binaryExpr->right);
    setBinaryExprType(binaryExpr);
}

void SemaAnalyser::visitArray(const LgsArray* array) {
    for (const auto& element : array->initialElements) {
        visitExpr(element);
    }
    if (const auto arrayType = dynamic_cast<LgsArrayType*>(array->type)) {
        arrayType->underlyingType = array->initialElements[0]->type;
    }
}

void SemaAnalyser::visitVariable(LgsVariable* variable) {
    setVariableType(variable);
}

void SemaAnalyser::visitSelection(LgsSelection* selection) {
    const auto exprs = selection->exprs;
    visitFirstSelection(exprs[0]);
    if (!successful) return;
    visitInnerSelections(selection);
    if (!successful) return;
    setExprType(selection, selection->lastExpr()->type);
}

void SemaAnalyser::visitFirstSelection(LgsExpr* firstExpr) {
    if (const auto variable = dynamic_cast<LgsVariable*>(firstExpr)) {
        visitVariable(variable);
    } else if (const auto funcCall = dynamic_cast<LgsFuncCall*>(firstExpr)) {
        visitFuncCall(funcCall);
    } else if (const auto typeConst = dynamic_cast<LgsTypeConst*>(firstExpr)) {
        typeConst->type = resolveType(typeConst->type);
    } else {
        assert(false && "first selection case not implemented");
    }
}

void SemaAnalyser::visitInnerSelections(const LgsSelection* selection) {
    const auto exprs = selection->exprs;
    for (int i = 0; i < exprs.size() - 1; ++i) {
        const auto currentExpr = exprs[i];
        const auto nextExpr = exprs[i + 1];
        auto nextExprName = nextExpr->getName();
        if (const auto var = dynamic_cast<LgsVariable*>(nextExpr)) {
            setSelectionFieldType(currentExpr, var);
        } else if (const auto methodCall = dynamic_cast<LgsFuncCall*>(nextExpr)) {
            methodCall->parentName = currentExpr->type->getName();
            visitMethodCall(methodCall, currentExpr->type);
        }
    }
}

void SemaAnalyser::visitInstance(LgsInstance* instance) {
    const auto symbol = getSymbol(instance->type->getName(), instance);
    if (!symbol) return;
    instance->obj = symbol->object;
    instance->type = instance->obj;
    for (const auto& [name, field] : instance->obj->fields) {
        instance->fields[name] = new LgsField(*field);
    }
}

void SemaAnalyser::visitArrayIndex(LgsArrayIndex* arrayIndex) {
    visitUnaryExpr(arrayIndex->expr);
    visitExpr(arrayIndex->index);
    const auto arrType = dynamic_cast<LgsArrayType*>(arrayIndex->expr->type);
    if (arrType) {
        setExprType(arrayIndex, arrType->underlyingType);
    } else {
        setExprType(arrayIndex, arrayIndex->expr->type);
    }
    // TODO add if iterable check
    // if (!arrType) {
    //     handleError(E10002, &arrayIndex->location, {arrayIndex->getName()});
    //     return;
    // }
}

void SemaAnalyser::visitFuncCall(LgsFuncCall* funcCall) {
    vector<string> argTypeNames;
    for (const auto& arg : funcCall->args) {
        visitExpr(arg);
        if (!arg->type) return;
        argTypeNames.emplace_back(arg->type->getName());
    }
    funcCall->composedName = LgsFuncSignature::getComposedName(funcCall->name, funcCall->parentName, argTypeNames);
    if (!resolveFuncCall(funcCall)) return;
    setExprType(funcCall, funcCall->func->signature.type);
}

void SemaAnalyser::visitMethodCall(LgsFuncCall* methodCall, const LgsType* parent) {
    vector<string> argTypeNames;
    for (const auto& arg : methodCall->args) {
        visitExpr(arg);
        argTypeNames.emplace_back(arg->type->getName());
    }
    methodCall->composedName = LgsFuncSignature::getComposedName(methodCall->name, methodCall->parentName, argTypeNames);
    setMethod(parent, methodCall);
}


void SemaAnalyser::setVariableType(LgsVariable* variable) {
    const auto symbol = getSymbol(variable->name, variable);
    if (!symbol) return;
    switch (symbol->type) {
    case VAR_DEC:
        setExprType(variable, symbol->varDec->type);
        break;
    case PARAM:
        setExprType(variable, symbol->param->type);
        break;
    default:
        assert(false && "setVariableType not implemented");
    }
}

LgsType* SemaAnalyser::resolveType(LgsType* type) {
    if (!dynamic_cast<LgsUnknownType*>(type)) return type;
    const auto name = type->getName();
    const auto nullable = type->nullable;
    const auto symbol = logosStack.getSymbol(name);
    if (!symbol) {
        handleError(E10006, &type->location, {name});
        return nullptr;
    }
    delete type;
    if (symbol->type == OBJECT) {
        symbol->object->nullable = nullable;
        return symbol->object;
    }
    if (symbol->type == INTERFACE) {
        symbol->interface->nullable = nullable;
        return symbol->interface;
    }
    return nullptr;
}

void SemaAnalyser::setFuncType(LgsFunc* func) {
    func->signature.type = resolveType(func->signature.type);
}

void SemaAnalyser::setExprType(LgsExpr* expr, LgsType* type) {
    expr->type = resolveType(type);
}

void SemaAnalyser::setSelectionFieldType(LgsUnaryExpr* parent, LgsVariable* fieldVariable) {
    const auto field = parent->type->getField(fieldVariable->name);
    if (!field) {
        handleError(E10005, &fieldVariable->location, {fieldVariable->getName(), parent->type->getName()});
        return;
    }
    field->parentExpr = parent;
    setExprType(fieldVariable, field->type);
}

void SemaAnalyser::setMethod(const LgsType* parent, LgsFuncCall* methodCall) {
    const auto method = parent->getMethod(methodCall);
    if (!method) {
        handleError(E10005, &methodCall->location, {methodCall->getName(), parent->getName()});
        return;
    }
    methodCall->func = method;
    setExprType(methodCall, methodCall->func->signature.type);
}

void SemaAnalyser::setBinaryExprType(LgsBinaryExpr* binaryExpr) {
    switch (binaryExpr->op) {
    case ADD:
    case SUB:
    case MUL:
    case DIV: {
        const auto lType = binaryExpr->left->type;
        const auto rType = binaryExpr->right->type;
        if (!lType || !rType) return;
        setExprType(binaryExpr, lType->inferBinaryType(rType));
        break;
    }
    case NE:
    case EQ:
    case LT:
    case GT:
    case GE:
    case LE: {
        setExprType(binaryExpr, new LgsBool());
        return;
    }
    case NOOP:
        break;
    }
}

bool SemaAnalyser::checkExprType(const LgsExpr* expr, LgsType* userType) {
    if (expr && userType) {
        if (expr->type && !expr->type->equals(userType)) {
            handleError(E10001, &expr->location, {userType->getName(), expr->type->getName()});
            return false;
        }
    }
    return true;
}

void SemaAnalyser::checkObjectImplements(LgsObject* obj) {
    for (int i = 0; i < obj->implements.size(); ++i) {
        const auto interface = dynamic_cast<LgsInterface*>(resolveType(obj->implements[i]));
        if (!interface) return;
        obj->implements[i] = interface;
        for (const auto& funcSignature : interface->funcSignatures) {
            if (!obj->getMethod(funcSignature)) {
                // handleError(E10016, &obj->location, {obj->name, interface->name});
            }
        }
    }
}

void SemaAnalyser::handleError(const LgsError& lgsErr, const Location* location, const vector<string>& args) {
    setUnsuccessful();
    const auto errMsg = formatErrorMsg(lgsErr.msg, args);
    errors.emplace_back(LgsError{.errCode = lgsErr.errCode, .msg = errMsg});

    const auto lineNumber = to_string(location->lineNumber);
    const auto pos = to_string(location->posInLine);
    const auto path = "\tat " + file->absPath + ":" + lineNumber + ":" + pos;

    cout << errMsg << '\n' << path << '\n';
}

LgsSymbol* SemaAnalyser::getSymbol(const string& name, const LgsValue* value) {
    const auto symbol = logosStack.getSymbol(name);
    if (!symbol) {
        handleError(E10006, &value->location, {name});
    }
    return symbol;
}

bool SemaAnalyser::resolveFuncCall(LgsFuncCall* funcCall) {
    const auto overloads = logosStack.getFuncOverloads(funcCall->name);
    if (overloads.empty()) {
        handleError(E10006, &funcCall->location, {funcCall->name});
        return false;
    }
    const auto func = logosStack.getFunc(overloads, funcCall->composedName);
    if (!func) {
        handleError(E10015, &funcCall->location, {funcCall->getArgsTypeStr(), funcCall->name});
        return false;
    }
    funcCall->func = func;
    return true;
}

void SemaAnalyser::addLocalSymbol(const string&name, const LgsSymbol& symbol) {
    if (const auto s = logosStack.getSymbol(name)) {
        const auto symbolPosition = getSymbolLocation(s);
        handleError(E10011, &symbol.varDec->location, {name, to_string(symbolPosition->lineNumber)});
        return;
    }
    logosStack.addLocalSymbol(name, symbol);
}

Location* SemaAnalyser::getSymbolLocation(const LgsSymbol* symbol) const {
    switch (symbol->type) {
    case VAR_DEC:
        return &symbol->varDec->location;
    case PARAM:
        return &symbol->param->location;
    case FUNC:
        return &symbol->func->location;
    default:
        return nullptr;
    }
}