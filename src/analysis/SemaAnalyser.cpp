#include "SemaAnalyser.h"
#include "LgsErrors.h"
#include "LgsGlobals.h"
#include "LgsInterfaceFile.h"
#include "LgsObjectFile.h"
#include "exprs/LgsCast.h"
#include "exprs/LgsNull.h"
#include "stmts/LgsField.h"
#include "stmts/LgsReturn.h"
#include "types/LgsDArrType.h"
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
#include "exprs/unary/constants/LgsStrConst.h"
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
    func->signature.path = file->absPath;
    lgsStack.enterScope(func);
    visitFuncSignature(&func->signature);
    visitStmtBlock(func->stmtBlock);
    lgsStack.exitScope();
    validateFuncControlFlow(func);
}

void SemaAnalyser::visitFuncSignature(LgsFuncSignature* funcSignature) {
    for (auto& param : funcSignature->params) {
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
    if (const auto arrIndex = dynamic_cast<LgsArrayIndex*>(lExpr)) {
        visitArrayIndex(arrIndex);
    }
    validateExprType(lExpr, rExpr->type);
}

void SemaAnalyser::visitVarDec(LgsVarDec* varDec) {
    if (varDec->expr) {
        visitExpr(varDec->expr);
        varDec->expr->type = resolveType(varDec->expr->type, &errHandler);
        varDec->type = varDec->expr->type;
        if (!validateExprType(varDec->expr, varDec->type)) return;
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
    if (!iterableExpr->type->isIterable()) {
        return errHandler.handleError(E10002, &iterableExpr->location, {iterableExpr->getName()});
    }
    // TODO check all loop vars
    for (const auto var : foreachLoop->loopVars) {
        addLocalSymbol(var->name, LgsSymbol(var));
    }
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
                return errHandler.handleError(E10027, &returnStmt->location, {funcSignature.name, rt->getName(), exprType->getName()});
            }
        }
    } else if (!returnStmt->expr) {
        return errHandler.handleError(E10026, &returnStmt->location, {funcSignature.name, rt->getName()});
    } else if (!rt->equals(returnStmt->expr->type)) {
        return errHandler.handleError(E10027, &returnStmt->location, {funcSignature.name, rt->getName(), returnStmt->expr->type->getName()});
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

void SemaAnalyser::visitArray(const LgsDArray* array) {
    for (const auto& element : array->initialElements) {
        visitExpr(element);
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
        typeConst->type = resolveType(typeConst->type, &errHandler);
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
        return errHandler.handleError(E10005, &childField->location, {childField->getName(), parentType->getName()});
    }
    setExprType(childField, field->type);
    childField->ref = new LgsSymbol(field->clone());
    if (!field->isPublic && file->absPath != field->parent->path) {
        errHandler.handleError(E10030, &childField->location, {childField->getName(), field->parent->name});
    }
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
    vector<LgsFunc*> castedOverloads;
    for (const auto& overload : overloads) {
        castedOverloads.emplace_back(overload);
    }
    if (!resolveFuncCall(castedOverloads, methodCall, parentType->getName())) return;
    setExprType(methodCall, methodCall->func->signature.type);
    const auto method = dynamic_cast<LgsMethodImpl*>(methodCall->func);
    if (!method->isPublic && file->absPath != method->signature.path) {
        errHandler.handleError(E10031, &method->location, {method->signature.name, method->parentName});
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
        return errHandler.handleError(E10006, &funcCall->location, {funcCallName});
    }
    if (symbol->type == PARAM && !resolveFuncCall({symbol->param->callbackFunc}, funcCall)) return;
    if (symbol->type == FUNC && !resolveFuncCall(symbol->func, funcCall)) return;
    setExprType(funcCall, funcCall->func->signature.type);
    funcCall->ref = symbol->clone();
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

void SemaAnalyser::visitArrayIndex(LgsArrayIndex* arrayIndex) {
    visitUnaryExpr(arrayIndex->baseExpr);
    if (const auto iter = dynamic_cast<LgsIterable*>(arrayIndex->baseExpr->type)) {
        arrayIndex->type = iter->underlyingType;
    } else {
        arrayIndex->type = arrayIndex->baseExpr->type;
    }
}

void SemaAnalyser::visitObjectImplements(LgsObject* obj) {
    for (int i = 0; i < obj->implements.size(); ++i) {
        const auto implement = obj->implements[i];
        if (!implement) continue;
        const auto interface = dynamic_cast<LgsInterface*>(implement);
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
                    if (objOverload->equals(interfaceOverload)) {
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
        const auto name = type ? type->getName() : "Unknown";
        errHandler.handleError(E10005, &fieldVariable->location, {fieldVariable->getName(), name});
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

bool SemaAnalyser::validateExprType(LgsExpr* expr, LgsType* type) {
    if (!expr) return true;
    visitExpr(expr);
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
    if (type && !expr->type->equals(type)) {
        errHandler.handleError(E10001, &expr->location, {type->getName(), expr->type->getName()});
        return false;
    }
    return true;
}

bool SemaAnalyser::resolveFuncCall(const vector<LgsFunc*>& overloads, LgsFuncCall* funcCall, const string& parentName) {
    LgsFunc* func = nullptr;
    for (const auto overload : overloads) {
        if (overload->signature.hasDefaultParams) {
            func = resolveFuncCallWithDefaultParams(overload, funcCall);
        } else if (overload->equals(funcCall)) {
            func = overload;
        }
        if (func) break;
    }

    if (!func) {
        if (funcCall->isMethodCall) {
            errHandler.handleError(E10034, &funcCall->location, {parentName, funcCall->name, funcCall->getSignatureText(), getOverloadsAsStr(overloads)});
        } else {
            errHandler.handleError(E10015, &funcCall->location, {funcCall->name, funcCall->getSignatureText(), getOverloadsAsStr(overloads)});
        }
        return false;
    }

    funcCall->func = func;
    funcCall->type = func->signature.type;
    return true;
}

void SemaAnalyser::checkDuplicateFuncs(const vector<LgsFuncImpl*>& overloads) {
    for (size_t i = 0; i < overloads.size(); ++i) {
        const auto overload1 = overloads[i];
        for (size_t j = i + 1; j < overloads.size(); ++j) {
            const auto overload2 = overloads[j];
            if (overload1->signature.hasDefaultParams && overload2->signature.hasDefaultParams) {
                if (!overload1->equals(overload2)) {
                    return errHandler.handleError(E10033, &overload1->location, {overload1->signature.getAsStr()});
                }
            } else if (overload1->signature.hasDefaultParams) {
                assert(false);
            } else if (overload2->signature.hasDefaultParams) {
                assert(false);
            }
            if (overload1->equals(overload2)) {
                errHandler.handleError(E10033, &overload1->location, {overload1->signature.getAsStr()});
            }
        }
    }
}

LgsFunc* SemaAnalyser::resolveFuncCallWithDefaultParams(LgsFunc* func, const LgsFuncCall* funcCall) const {
    const auto params = func->signature.params;
    const auto argsSize = funcCall->args.size();
    for (size_t i = funcCall->isMethodCall; i < params.size(); ++i) {
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
        errHandler.handleError(E10004, &func->location, {func->signature.name, func->signature.type->getName()});
    }
}

string SemaAnalyser::getOverloadsAsStr(const vector<LgsFunc*>& overloads) const {
    stringstream str;
    for (const auto& overload : overloads) {
        str << "\n\t     - " << overload->signature.getAsStr();
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
