#include "SemaAnalyser.h"
#include "LgsErrors.h"
#include "LgsGlobals.h"
#include "LgsInterfaceFile.h"
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
#include "stmts/LgsPatternMatch.h"
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
    } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
        visitInterface(interfaceFile->interface);
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

void SemaAnalyser::visitInterface(LgsInterface* interface) {

}

void SemaAnalyser::visitObjectInterfaces(LgsObject* obj) {
    for (int i = 0; i < obj->implements.size(); ++i) {
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
    visitFuncSignature(&func->signature);
    visitStmtBlock(func->stmtBlock);
    lgsStack.exitScope();
    validateFuncControlFlow(func);
}

void SemaAnalyser::visitFuncSignature(LgsFuncSignature* funcSignature) {
    for (auto& param : funcSignature->params) {
        if (param.expr) {
            funcSignature->hasDefaultParams = true;
        }
        visitParam(&param);
    }
}

void SemaAnalyser::visitParam(LgsParam* param) {
    addLocalSymbol(param->name, LgsSymbol(param));
    validateExprType(param->expr, param->type);
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
    validateExprType(field->expr, field->type);
}

void SemaAnalyser::visitAssignment(const LgsAssignment* assignment) {
    const auto rExpr = assignment->rvalue;
    visitExpr(rExpr);
    const auto lExpr = assignment->lvalue;
    if (const auto selection = dynamic_cast<LgsSelection*>(lExpr)) {
        visitSelection(selection);
    }
    validateExprType(lExpr, rExpr->type);
}

void SemaAnalyser::visitVarDec(LgsVarDec* varDec) {
    if (varDec->expr) {
        visitExpr(varDec->expr);
        varDec->expr->type = resolveType(varDec->expr->type);
        varDec->type = varDec->expr->type;
        if (!validateExprType(varDec->expr, varDec->type)) return;
    } else {
        varDec->type = resolveType(varDec->type);
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
            return handleError(E10014, &patternExpr->location, {patternExpr->type->getName(), baseExprType->getName()});
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
    auto funcSignature = lgsStack.currentFunc->signature;
    const auto rt = funcSignature.type;
    if (returnStmt->expr) {
        returnStmt->expr->isReturnValue = true;
        visitExpr(returnStmt->expr);
    }
    if (rt->isVoid()) {
        if (returnStmt->expr) {
            const auto exprType = returnStmt->expr->type;
            if (!exprType->isVoid()) {
                return handleError(E10027, &returnStmt->location, {funcSignature.name, rt->getName(), exprType->getName()});
            }
        }
    } else if (!returnStmt->expr) {
        return handleError(E10026, &returnStmt->location, {funcSignature.name, rt->getName()});
    } else if (!rt->equals(returnStmt->expr->type)) {
        return handleError(E10027, &returnStmt->location, {funcSignature.name, rt->getName(), returnStmt->expr->type->getName()});
    }
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
    if (const auto instance = unaryExpr->asInstance()) {
        visitInstance(instance);
    } else if (const auto funcCall = unaryExpr->asFuncCall()) {
        visitFuncCall(funcCall);
    } else if (const auto selection = unaryExpr->asSelection()) {
        visitSelection(selection);
    } else if (const auto array = unaryExpr->asArray()) {
        visitArray(array);
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
        break;
    case FUNC:
        // TODO add func matching
        setExprType(variable, symbol->func[0]->signature.type);
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
        typeConst->type = resolveType(typeConst->type);
    } else {
        assert(false && "first selection case not implemented");
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
        return handleError(E10005, &childField->location, {childField->getName(), parentType->getName()});
    }
    setExprType(childField, field->type);
    childField->ref = new LgsSymbol(field->clone());
    if (!field->isPublic && file->absPath != field->parent->filePath) {
        handleError(E10030, &childField->location, {childField->getName(), field->parent->name});
    }
}

void SemaAnalyser::visitMethodCall(LgsFuncCall* methodCall, const LgsType* parentType) {
    methodCall->parentName = parentType->getName();
    vector<string> argTypeNames;
    for (const auto& arg : methodCall->args) {
        visitExpr(arg);
        argTypeNames.emplace_back(arg->type->getName());
    }
    auto name = methodCall->name;
    const auto overloads = parentType->getMethodsOverloads(name);
    if (overloads.empty()) {
        return handleError(E10013, &methodCall->location, {name});
    }
    vector<LgsFunc*> castedOverloads;
    for (const auto& overload : overloads) {
        castedOverloads.emplace_back(overload);
    }
    if (!resolveFuncCall(castedOverloads, methodCall)) return;
    setExprType(methodCall, methodCall->func->signature.type);
    const auto method = dynamic_cast<LgsMethodImpl*>(methodCall->func);
    if (!method->isPublic && file->absPath != method->filePath) {
        handleError(E10031, &method->location, {method->signature.name, method->signature.parentName});
    }
}

void SemaAnalyser::visitFuncCall(LgsFuncCall* funcCall) {
    vector<string> argTypeNames;
    for (const auto& arg : funcCall->args) {
        visitExpr(arg);
        if (!arg->type) return;
        argTypeNames.emplace_back(arg->type->getName());
    }
    auto funcCallName = funcCall->name;
    const auto symbol = lgsStack.getSymbol(funcCallName);
    if (!symbol) {
        return handleError(E10006, &funcCall->location, {funcCallName});
    }
    if (symbol->type == PARAM && !resolveFuncCall({symbol->param->callbackFunc}, funcCall)) return;
    if (symbol->type == FUNC && !resolveFuncCall(symbol->func, funcCall)) return;
    setExprType(funcCall, funcCall->func->signature.type);
    funcCall->ref = symbol->clone();
}

void SemaAnalyser::visitInstance(LgsInstance* instance) {
    instance->type = resolveType(instance->type);
    if (!instance->type) return;
    const auto symbol = getSymbol(instance->type->getName(), instance);
    if (!symbol) return;
    if (symbol->type != OBJECT) {
        return handleError(E10022, &instance->location, {instance->type->getName()});
    }
    if (symbol->object->isSingleton) {
        return handleError(E10032, &instance->location, {instance->type->getName()});
    }

    const auto obj = symbol->object->clone();
    for (const auto& arg : instance->args) {
        visitExpr(arg->expr);
        const auto lgsField = obj->getField(arg->name);
        if (!lgsField) {
            handleError(E10005, &arg->location, {arg->name, obj->name});
            continue;
        }
        lgsField->expr = arg->expr;
    }

    for (const auto [_, field] : obj->fields) {
        if (field->isConst && !field->expr) {
            handleError(E10029, &field->location, {field->name});
            continue;
        }
    }

    instance->obj = obj;
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

void SemaAnalyser::setExprType(LgsExpr* expr, LgsType* type) {
    assert(type);
    expr->type = resolveType(type);
    assert(expr->type);
}

bool SemaAnalyser::setSelectionFieldType(const LgsUnaryExpr* parent, LgsVariable* fieldVariable) {
    const auto type = parent->type;
    const auto field = type ? type->getField(fieldVariable->name) : nullptr;
    if (!type || !field) {
        const auto name = type ? type->getName() : "Unknown";
        handleError(E10005, &fieldVariable->location, {fieldVariable->getName(), name});
        return false;
    }
    if (!field->isPublic) {}
    setExprType(fieldVariable, field->type);
    return true;
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
    case AND:
    case OR:
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

bool SemaAnalyser::validateExprType(LgsExpr* expr, LgsType* type) {
    if (!expr) return true;
    visitExpr(expr);
    if (expr->isNull()) {
        // null must have a type
        if (!type) {
            handleError(E10024, &expr->location);
            return false;
        }
        // type must be nullable
        if (!type->nullable) {
            handleError(E10023, &type->location, {type->getName(), type->getName()});
            return false;
        }
        expr->type = type;
        return true;
    }
    if (type) {
        // types don't match
        if (!expr->type->equals(type)) {
            handleError(E10001, &expr->location, {type->getName(), expr->type->getName()});
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

bool SemaAnalyser::resolveFuncCall(const vector<LgsFunc*>& overloads, LgsFuncCall* funcCall) {
    LgsFunc* func = nullptr;
    for (const auto& overload : overloads) {
        if (overload->signature.params.size() < funcCall->args.size()) continue;
        if (overload->signature.hasDefaultParams) {
            func = resolveFuncCallWithDefaultParams(overload, funcCall);
        } else {
            func = resolveFuncCallWithoutDefaultParams(overload, funcCall);
        }
        if (func) break;
    }

    if (!func) {
        handleError(E10015, &funcCall->location, {funcCall->name, getOverloadsAsStr(overloads)});
        return false;
    }

    funcCall->func = func;
    funcCall->type = func->signature.type;
    return true;
}

LgsFunc* SemaAnalyser::resolveFuncCallWithoutDefaultParams(LgsFunc* func, const LgsFuncCall* funcCall) const {
    const auto params = func->signature.params;
    if (funcCall->args.size() > params.size()) return nullptr;
    if (params.size() == funcCall->args.size()) {
        if (func->signature.isEqual(funcCall)) {
            return func;
        }
    }
    return nullptr;
}

LgsFunc* SemaAnalyser::resolveFuncCallWithDefaultParams(LgsFunc* func, const LgsFuncCall* funcCall) const {
    const auto params = func->signature.params;
    const auto argsSize = funcCall->args.size();
    for (size_t i = 0; i < params.size(); ++i) {
        const auto param = params[i];
        if (i >= argsSize) continue;
        const auto arg = funcCall->args[i];
        if (!param.type->equals(arg->type)) return nullptr;
    }
    return func;
}

void SemaAnalyser::validateFuncControlFlow(const LgsFunc* func) {
    if (dynamic_cast<LgsVoid*>(func->signature.type)) return;
    const auto stmtBlock = func->stmtBlock;
    const bool isFlowCorrect = func->signature.name != LOGOS_MAIN_FUNC && !stmtBlock->hasReturn;
    if (isFlowCorrect) {
        handleError(E10004, &func->location, {func->signature.name, func->signature.type->getName()});
    }
}

LgsSymbol* SemaAnalyser::getSymbol(const string& name, const LgsValue* value) {
    const auto symbol = lgsStack.getSymbol(name);
    if (!symbol) handleError(E10006, &value->location, {name});
    return symbol;
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
        assert(false);
    default:
        return nullptr;
    }
}

string SemaAnalyser::getOverloadsAsStr(const vector<LgsFunc*>& overloads) const {
    stringstream str;
    for (const auto& overload : overloads) {
        str << "\n  - " << overload->signature.getPrintName();
    }
    return str.str();
}
