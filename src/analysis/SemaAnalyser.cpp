#include "SemaAnalyser.h"
#include "LgsErrors.h"
#include "LgsGlobals.h"
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
#include "types/LgsEnum.h"
#include "exprs/unary/LgsEnumField.h"
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
        visitObject(objFile->obj);
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

void SemaAnalyser::visitObject(LgsObject* obj) {
    for (const auto& [_, field] : obj->fields) {
        visitField(field);
    }
    for (const auto& [_, method] : obj->methods) {
        for (const auto& overload : method) {
            visitMethodImpl(overload);
        }
    }
    visitObjectInterfaces(obj);
}

void SemaAnalyser::visitObjectInterfaces(LgsObject* obj) {
    for (int i = 0; i < obj->implements.size(); ++i) {
        obj->implements[i] = resolveType(obj->implements[i]);
        const auto implement = obj->implements[i];
        if (!implement) continue;

        const auto interface = dynamic_cast<LgsInterface*>(implement);
        if (!interface) {
            handleError(E10025, &implement->location, {implement->getName()});
            continue;
        }
        checkObjectImplements(obj, interface);
    }
}

void SemaAnalyser::visitFuncImpl(LgsFuncImpl* func) {
    logosStack.enterScope(func);
    setFuncType(func);
    for (auto& param : func->signature.params) {
        visitParam(&param);
    }
    visitStmtBlock(func->stmtBlock);
    logosStack.exitScope();
}

void SemaAnalyser::visitMethodImpl(LgsMethodImpl* method) {
    logosStack.enterScope(method);
    setFuncType(method);
    for (auto& param : method->signature.params) {
        visitParam(&param);
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
    } else if (const auto assignment = dynamic_cast<LgsAssignment*>(stmt)) {
        visitAssignment(assignment);
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

void SemaAnalyser::visitField(LgsField* field) {
    field->userType = resolveType(field->userType);
    if (field->expr) {
        if (!validateUserType(field->expr, field->userType)) return;
        field->type = field->expr->type;
    } else {
        field->type = field->userType;
        field->expr = field->type->getZeroValue();
    }
}

void SemaAnalyser::visitAssignment(const LgsAssignment* assignment) {
    const auto rExpr = assignment->rvalue;
    const auto lExpr = assignment->lvalue;
    if (const auto selection = dynamic_cast<LgsSelection*>(lExpr)) {
        visitSelection(selection);
    }
    validateUserType(lExpr, rExpr->type);
}

void SemaAnalyser::visitVarDec(LgsVarDec* varDec) {
    varDec->userType = resolveType(varDec->userType);
    if (varDec->expr) {
        if (!validateUserType(varDec->expr, varDec->userType)) return;
        varDec->type = varDec->expr->type;
    } else {
        varDec->type = varDec->userType;
        varDec->expr = varDec->type->getZeroValue();
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
        return visitBoolPatternMatching(patternMatching);
    }
    visitExpr(baseExpr);
    const auto baseExprType = baseExpr->type;
    for (const auto patternExpr : patternMatching->patterns) {
        visitExpr(patternExpr);
        if (!patternExpr->type) continue;
        if (!patternExpr->type->equals(baseExprType)) {
            return handleError(E10014, &patternExpr->location, {patternExpr->type->getName(), baseExprType->getName()});
        }
    }
    for (const auto& patternsStmtBlock : patternMatching->patternsStmtBlocks) {
        visitStmtBlock(patternsStmtBlock);
    }
    visitStmtBlock(patternMatching->elseStmtBlock);
}

void SemaAnalyser::visitBoolPatternMatching(const LgsPatternMatching* patternMatching) const {

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
        return handleError(E10002, &iterableExpr->location, {iterableExpr->getName()});
    }
    // TODO check all loop vars
    const auto loopVar = foreachLoop->loopVars[0];
    loopVar->type = dynamic_cast<LgsArrayType*>(iterableExpr->type)->underlyingType;
    addLocalSymbol(loopVar->name, LgsSymbol(loopVar));
    visitStmtBlock(foreachLoop->stmtBlock);
}

void SemaAnalyser::visitReturnStmt(const LgsReturn* returnStmt) {
    const auto currentFunc = logosStack.currentFunc;
    const auto rt = currentFunc->signature.type;
    if (rt->getName() == LgsVoid::name && returnStmt->expr) {
        return handleError(E10026, &returnStmt->expr->location);
    }
    visitExpr(returnStmt->expr);
}

void SemaAnalyser::visitBreakStmt(LgsBreakStmt* breakStmt) const {
}

void SemaAnalyser::visitEnum(const LgsEnum* lgsEnum) const {

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
    const auto symbol = getSymbol(variable->name, variable);
    if (!symbol) return;
    switch (symbol->type) {
    case VAR_DEC:
        setExprType(variable, symbol->varDec->type);
        break;
    case PARAM:
        setExprType(variable, symbol->param->type);
        break;
    case ENUM:
        setExprType(variable, symbol->lgsEnum);
        break;
    case ENUM_FIELD:
        setExprType(variable, symbol->enumField->type);
        break;
    default:
        assert(false);
    }
    variable->ref = *symbol;
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
    instance->type = resolveType(instance->type);
    const auto symbol = getSymbol(instance->type->getName(), instance);
    if (!symbol) return;
    if (symbol->type != OBJECT) {
        return handleError(E10022, &instance->location, {instance->type->getName()});
    }
    instance->obj = symbol->object;
    instance->type = instance->obj;
    for (const auto& field : instance->type->fields) {
        instance->fields[field.first] = new LgsField(*field.second);
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

void SemaAnalyser::setFuncType(LgsFunc* func) {
    func->signature.type = resolveType(func->signature.type);
}

void SemaAnalyser::setExprType(LgsExpr* expr, LgsType* type) {
    expr->type = resolveType(type);
}

void SemaAnalyser::setSelectionFieldType(LgsUnaryExpr* parent, LgsVariable* fieldVariable) {
    const auto field = parent->type->getField(fieldVariable->name);
    if (!field) {
        return handleError(E10005, &fieldVariable->location, {fieldVariable->getName(), parent->type->getName()});
    }
    field->parentExpr = parent;
    setExprType(fieldVariable, field->type);
}

void SemaAnalyser::setMethod(const LgsType* parent, LgsFuncCall* methodCall) {
    const auto method = parent->findMethod(methodCall);
    if (!method) {
        return handleError(E10005, &methodCall->location, {methodCall->getName(), parent->getName()});
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

bool SemaAnalyser::validateUserType(LgsExpr* expr, LgsType* userType) {
    visitExpr(expr);
    if (expr->isNull()) {
        // null must have a type
        if (!userType) {
            handleError(E10024, &expr->location);
            return false;
        }
        // userType must be nullable
        if (!userType->nullable) {
            handleError(E10023, &userType->location, {userType->getName(), userType->getName()});
            return false;
        }
        expr->type = userType;
        return true;
    }
    if (userType) {
        // User and expr type don't match
        if (!expr->type->equals(userType)) {
            handleError(E10001, &expr->location, {expr->type->getName(), userType->getName()});
            return false;
        }
    }
    return true;
}

void SemaAnalyser::checkObjectImplements(LgsObject* obj, LgsInterface* const interface) {
    vector<LgsFuncSignature*> missingFuncs;
    for (const auto& signature : interface->funcSignatures) {
        const auto overloads = obj->getMethodsOverloads(signature->name);
        auto found = false;
        for (const auto& overload : overloads) {
            if (overload->equals(signature)) {
                found = true;
                break;
            }
        }
        if (!found) {
            missingFuncs.emplace_back(signature);
        }
    }
    if (!missingFuncs.empty()) {
        handleError(E10016, &obj->location, {obj->name, interface->name, getFuncSignaturesStr(missingFuncs)});
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
    auto name = funcCall->name;

    // Resolve parent func
    vector<LgsFunc*> overloads;
    const auto it = globals.funcs.find(name);
    if (it != globals.funcs.end()) {
        overloads = it->second;
    } else {
        handleError(E10006, &funcCall->location, {name});
        return false;
    }

    // Resolve overload
    LgsFunc* func = nullptr;
    for (const auto& overload : overloads) {
        if (overload->signature.name != funcCall->name) continue;
        auto overloadParams = overload->signature.params;
        if (funcCall->args.size() > overloadParams.size()) {
            handleError(E10027, &funcCall->location);
            return false;
        }

        // same size of params and args implies no use of default args
        if (overloadParams.size() == funcCall->args.size()) {
            if (overload->signature.IRName == funcCall->composedName) {
                func = overload;
            }
            break;
        }

        if (overloadParams.size() == 0) return true;

        auto pass = true;
        for (size_t i = 0; i < overloadParams.size(); ++i) {
            const auto overloadParam = overloadParams[i];
            auto thisTypeName = overloadParam.type->getName();
            if (overloadParam.expr) continue;
            auto otherTypeName = funcCall->args[i]->type->getName();
            if (thisTypeName != otherTypeName) {
                pass = false;
                break;
            }
        }

        if (pass) {
            func = overload;
        }
    }

    if (!func) {
        handleError(E10015, &funcCall->location, {funcCall->getArgsTypeStr(), name});
        return false;
    }
    funcCall->func = func;
    return true;
}

void SemaAnalyser::addLocalSymbol(const string&name, const LgsSymbol& symbol) {
    if (const auto s = logosStack.getSymbol(name)) {
        const auto symbolPosition = getSymbolLocation(s);
        return handleError(E10011, &symbol.varDec->location, {name, to_string(symbolPosition->lineNumber)});
    }
    logosStack.addLocalSymbol(name, symbol);
}

string SemaAnalyser::getFuncSignaturesStr(const vector<LgsFuncSignature*>& funcs) const {
    stringstream strStream;
    strStream << '\n';
    for (int i = 0; i < funcs.size(); ++i) {
        const auto missingFunc = funcs[i];
        strStream << "  - " << missingFunc->getPrintName();
        if (i != funcs.size() - 1) strStream << '\n';
    }
    return strStream.str();
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