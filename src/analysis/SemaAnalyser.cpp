#include "SemaAnalyser.h"
#include "LgsErrors.h"
#include "LgsGlobals.h"
#include "LgsObjectFile.h"
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
        visitFunc(func);
    }
    visitFunc(mainFile->mainFunc);
}

void SemaAnalyser::visitObject(LgsObject* obj) {
    for (const auto& [_, field] : obj->fields) {
        visitField(field);
    }
    for (const auto& [_, method] : obj->methods) {
        for (const auto& overload : method) {
            visitFunc(overload);
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

void SemaAnalyser::visitFunc(LgsFunc* func) {
    func->path = file->absPath;
    lgsStack.enterScope(func);
    setFuncType(func);
    for (auto& param : func->signature.params) {
        visitParam(&param);
    }
    visitStmtBlock(func->stmtBlock);
    lgsStack.exitScope();
    validateFuncControlFlow(func);
}

void SemaAnalyser::validateFuncControlFlow(const LgsFunc* func) {
    const auto stmtBlock = func->stmtBlock;
    // TODO finish logic
    if (func->signature.name != LOGOS_MAIN_FUNC && !stmtBlock->hasReturn) {
        handleError(E10004, &func->location, {func->signature.name, func->signature.type->getName()});
    }
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

void SemaAnalyser::visitStmtBlock(LgsStmtBlock* stmtBlock) {
    if (!stmtBlock) return;
    for (const auto& stmt : stmtBlock->stmts) {
        visitStmt(stmt);
    }
    if (dynamic_cast<LgsReturn*>(stmtBlock->lastStmt())) {
        stmtBlock->hasReturn = true;
    }
}

void SemaAnalyser::visitField(LgsField* field) {
    field->userType = resolveType(field->userType);
    if (field->expr) {
        if (!validateUserType(field->expr, field->userType)) return;
        field->type = field->expr->type;
    } else {
        field->type = field->userType;
    }
}

void SemaAnalyser::visitAssignment(const LgsAssignment* assignment) {
    const auto rExpr = assignment->rvalue;
    visitExpr(rExpr);
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

void SemaAnalyser::visitBoolPatternMatching(const LgsPatternMatching* patternMatching) const {}

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
    const auto currentFunc = lgsStack.currentFunc;
    const auto rt = currentFunc->signature.type;
    if (rt->getName() == LgsVoid::name && returnStmt->expr) {
        return handleError(E10026, &returnStmt->expr->location);
    }
    visitExpr(returnStmt->expr);
}

void SemaAnalyser::visitBreakStmt(LgsBreakStmt* breakStmt) const {}

void SemaAnalyser::visitEnum(const LgsEnum* lgsEnum) const {}

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
        variable->ref = symbol;
        break;
    default:
        assert(false);
    }
    variable->ref = symbol;
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
    instance->obj = new LgsObject(*symbol->object);
    instance->type = instance->obj;
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
    if (!resolveFuncCall(funcCall)) return ;
    setExprType(funcCall, funcCall->func->signature.type);
}

void SemaAnalyser::visitMethodCall(LgsFuncCall* methodCall, const LgsType* parent) {
    vector<string> argTypeNames;
    for (const auto& arg : methodCall->args) {
        visitExpr(arg);
        argTypeNames.emplace_back(arg->type->getName());
    }
    if (!resolveMethodCall(parent, methodCall)) return;
    setExprType(methodCall, methodCall->func->signature.type);
}

LgsType* SemaAnalyser::resolveType(LgsType* type) {
    if (!dynamic_cast<LgsUnknownType*>(type)) return type;
    const auto name = type->getName();
    const auto nullable = type->nullable;
    const auto symbol = lgsStack.getSymbol(name);
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

void SemaAnalyser::setSelectionFieldType(const LgsUnaryExpr* parent, LgsVariable* fieldVariable) {
    const auto field = parent->type->getField(fieldVariable->name);
    if (!field) {
        return handleError(E10005, &fieldVariable->location, {fieldVariable->getName(), parent->type->getName()});
    }
    fieldVariable->ref = new LgsSymbol(field);
    setExprType(fieldVariable, field->type);
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
            if (overload->signature.isEqual(signature)) {
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

LgsSymbol* SemaAnalyser::getSymbol(const string& name, const LgsValue* value) {
    const auto symbol = lgsStack.getSymbol(name);
    if (!symbol) {
        handleError(E10006, &value->location, {name});
    }
    return symbol;
}

bool SemaAnalyser::resolveFuncCall(LgsFuncCall* funcCall) {
    // Resolve parent func
    vector<LgsFunc*> overloads;
    auto funcCallName = funcCall->name;
    const auto it = globals.funcs.find(funcCallName);
    if (it != globals.funcs.end()) {
        overloads = it->second;
    } else {
        handleError(E10006, &funcCall->location, {funcCallName});
        return false;
    }
    return resolveFuncCall(overloads, funcCall);
}

bool SemaAnalyser::resolveMethodCall(const LgsType* type, LgsFuncCall* methodCall) {
    auto name = methodCall->name;
    const auto overloads = type->getMethodsOverloads(name);
    if (overloads.empty()) {
        handleError(E10013, &methodCall->location, {name});
        return false;
    }
    vector<LgsFunc*> castedOverloads;
    for (const auto& overload : overloads) {
        castedOverloads.emplace_back(overload);
    }
    return resolveFuncCall(castedOverloads, methodCall);
}

bool SemaAnalyser::resolveFuncCall(const vector<LgsFunc*>& overloads, LgsFuncCall* funcCall) {
    LgsFunc* func = nullptr;
    for (const auto& overload : overloads) {
        const auto overloadParams = overload->signature.params;
        if (funcCall->args.size() > overloadParams.size()) continue;
        // same size of params and args implies no use of default params
        if (overloadParams.size() == funcCall->args.size()) {
            if (overload->signature.isEqual(funcCall)) {
                func = overload;
                break;
            }
            continue;
        }

        auto found = true;
        for (size_t i = 0; i < overloadParams.size(); ++i) {
            const auto overloadParam = overloadParams[i];
            const auto paramType = overloadParam.type;
            if (overloadParam.expr) {
                if (overloadParams.size() > funcCall->args.size()) {
                    continue;
                }
                found = false;
                break;
            }
            const auto argType = funcCall->args[i]->type;
            if (!paramType->equals(argType)) {
                found = false;
                break;
            }
        }

        if (found) {
            func = overload;
        }
    }

    if (!func) {
        handleError(E10015, &funcCall->location, {funcCall->name, funcCall->name, funcCall->getArgsTypeStr()});
        return false;
    }

    funcCall->func = func;
    funcCall->type = func->signature.type;
    return true;
}

LgsFunc* SemaAnalyser::resolveFuncOverload(LgsFunc* overload, const LgsFuncCall* funcCall) {
    assert(overload->signature.name != funcCall->name);
    const auto overloadParams = overload->signature.params;
    // same size of params and args implies no use of default params
    if (overloadParams.size() == funcCall->args.size()) {
        if (overload->signature.isEqual(funcCall)) {
            return overload;
        }
        handleError(E10015, &funcCall->location, {funcCall->name, funcCall->name, funcCall->getArgsTypeStr()});
        return nullptr;
    }

    if (!checkDefaultParams(funcCall, overloadParams)) {
        return nullptr;
    }
    return overload;
}

bool SemaAnalyser::checkDefaultParams(const LgsFuncCall* funcCall, const vector<LgsParam>& overloadParams) const {
    for (size_t i = 0; i < overloadParams.size(); ++i) {
        const auto overloadParam = overloadParams[i];
        auto thisTypeName = overloadParam.type->getName();
        if (overloadParam.expr) continue;
        auto otherTypeName = funcCall->args[i]->type->getName();
        if (thisTypeName != otherTypeName) {
            return false;
        }
    }
    return true;
}

void SemaAnalyser::addLocalSymbol(const string&name, const LgsSymbol& symbol) {
    if (const auto alreadyExistSymbol = lgsStack.getSymbol(name)) {
        const auto location = getSymbolLocation(alreadyExistSymbol);
        return handleError(E10011, location, {name, to_string(location->lineNumber)});
    }
    lgsStack.addLocalSymbol(name, symbol);
}

string SemaAnalyser::getFuncSignaturesStr(const vector<LgsFuncSignature*>& funcs) const {
    stringstream strStream;
    strStream << endl;
    for (int i = 0; i < funcs.size(); ++i) {
        const auto missingFunc = funcs[i];
        strStream << "  - " << missingFunc->getPrintName();
        if (i != funcs.size() - 1) strStream << endl;
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