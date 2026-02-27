#include "analysis/LgsSema.h"

#include <__ostream/basic_ostream.h>
#include <_ctype.h>
#include <assert.h>
#include <unordered_set>
#include <atomic>
#include <filesystem>
#include <map>
#include <optional>
#include <ostream>
#include <sstream>
#include <utility>

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
#include "exprs/LgsPostfixExpr.h"
#include "exprs/LgsPrefixExpr.h"
#include "exprs/LgsTernaryExpr.h"
#include "exprs/LgsVectorExpr.h"
#include "exprs/constants/LgsStrConst.h"
#include "files/LgsMainFile.h"
#include "files/LgsTestFile.h"
#include "funcs/LgsMainFunc.h"
#include "logos/LgsApp.h"
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
#include "types/primitives/LgsDouble.h"
#include "types/iterables/LgsVariadic.h"
#include "exprs/LgsModuleExpr.h"
#include "LgsBinaryTokens.h"
#include "LgsDefinitions.h"
#include "LgsSymbol.h"
#include "LgsSymbolTable.h"
#include "LgsTokens.h"
#include "LgsType.h"
#include "LgsValue.h"
#include "Lgs_Types.h"
#include "exprs/LgsExpr.h"
#include "exprs/constants/LgsIntConst.h"
#include "files/LgsFile.h"
#include "funcs/LgsFunc.h"
#include "funcs/LgsParam.h"
#include "logos/LgsAppConfigs.h"
#include "stmts/LgsStmt.h"
#include "stmts/LgsStmtsBlock.h"
#include "types/LgsFuncType.h"
#include "types/LgsNullable.h"
#include "types/LgsObject.h"
#include "types/iterables/LgsIterable.h"
#include "types/iterables/LgsMap.h"
#include "types/iterables/LgsMatrix.h"
#include "types/iterables/LgsSArray.h"
#include "types/iterables/LgsStr.h"
#include "types/iterables/LgsVec.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsSize.h"

using std::to_string;

static std::string getMissingImplementsStr(const std::vector<LgsField*>& fields, const std::vector<LgsFunc*>& methods);

std::atomic<size_t> objsIDGenerator{0};
std::atomic<size_t> funcsIDGenerator{0};

void LgsSema::analyse() {
    if (const auto mainFile = file->asMainFile()) {
        visitMainFile(mainFile);
    } else if (const auto objFile = file->asObjectFile()) {
        visitObject(objFile->obj);
    } else if (const auto interfaceFile = file->asInterfaceFile()) {
        visitInterface(interfaceFile->interface);
    } else if (const auto testFile = file->asTestFile()) {
        visitTestFile(testFile);
    } else {
        assert(0);
    }
}

void LgsSema::visitMainFile(LgsMainFile* mainFile) {
    for (const auto varDec : mainFile->varDecs) {
        if (!varDec->isMutable) {
            addError(E10100, varDec->location, {varDec->name});
        }
        visitExpr(varDec->expr);
    }
    for (const auto obj : mainFile->objects) {
        visitObject(obj);
    }
    for (const auto enum_ : mainFile->enums) {
        visitEnum(enum_);
    }
    for (const auto interface : mainFile->interfaces) {
        visitInterface(interface);
    }
    for (const auto ioPair : mainFile->ioPairs) {
        visitIOPair(ioPair, nullptr);
    }
    for (const auto& [funcName, func] : mainFile->funcs) {
        if (funcName == LGS_MAIN_FUNC) {
            visitMainFunc(dynamic_cast<LgsMainFunc*>(func));
        } else {
            visitFunc(func);
        }
    }

    // Check main() func
    if (mainFile->funcs.contains(LGS_MAIN_FUNC)) {
        if (appConfigs.isLibrary) {
            errHandler.addError(E10087, {});
        }
    } else if (!appConfigs.isLibrary) {
        errHandler.addError(E10000, {});
    }
}

void LgsSema::visitTestFile(const LgsTestFile* testFile) {
    for (const auto& func : testFile->funcs) {
        visitFunc(func);
    }
    for (const auto& test : testFile->tests) {
        visitFunc(test);
    }
}

bool LgsSema::isTypeRecursive(const LgsType* type) {
    std::unordered_set<std::string> visited;
    if (type->isRecursive(visited)) {
        addError(E10048, type->location);
        return true;
    }
    return false;
}

void LgsSema::visitObject(LgsObject* obj) {
    obj->id = ++objsIDGenerator;
    currentObj = obj;
    validateTypeName(obj->name, obj->location);
    if (isTypeRecursive(obj)) return;
    validateObjDuplicates(obj);
    if (obj->hasTypeParams()) return;
    for (const auto field : obj->fields) {
        visitField(field);
    }
    for (const auto& [_, method] : obj->methods) {
        visitFunc(method);
    }
    for (const auto ioPair : obj->ioPairs) {
        visitIOPair(ioPair, obj);
    }
    visitObjImplements(obj, obj->implements);
    addRTType(obj);
    currentObj = nullptr;
}

void LgsSema::visitInterface(LgsInterface* interface) {
    validateTypeName(interface->name, interface->location);
    for (const auto& [_, method] : interface->methods) {
        visitFunc(method);
    }
}

void LgsSema::visitEnum(LgsEnum* enum_) {
    validateTypeName(enum_->name, enum_->location);
    size_t exprsCount = 0;
    LgsType* baseType = nullptr;
    for (const auto field : enum_->fields) {
        if (!field->expr) continue;
        if (field->expr->isMutable) {
            addError(E10077, field->expr->location);
            continue;
        }
        if (!baseType) {
            baseType = field->expr->type;
        } else if (!validateExprType(field->expr, baseType)) {
            addError(E10075, field->location);
            break;
        }
        field->type->asEnum()->exprType = baseType;
        exprsCount++;
    }
    enum_->exprType = baseType;
    if (exprsCount != 0 && exprsCount != enum_->fields.size()) {
        addError(E10118, enum_->location);
    }
}

void LgsSema::visitField(LgsField* field) {
    if (field->expr) {
        castExprImplicitly(field->expr, field->type);
        visitExpr(field->expr);
        validateExprType(field->expr, field->type);
    }
    if (field->type->asFuncType() || (field->expr && field->expr->asFunc())) {
        addError(E10013, field->location, {field->name});
    }
    if (field->type->isVoid()) addError(E10093, field->location);
    addRTType(field->type);
    addGenericType(field->type);
}

void LgsSema::visitFuncHeader(LgsFuncType* ft) {
    auto defaultParamStart = false;
    for (auto& param : ft->params) {
        visitParam(&param);
        if (defaultParamStart && !param.expr) {
            addError(E10028, param.location);
            break;
        }
        defaultParamStart = !!param.expr;
    }
    addRTType(ft->rt);
}

void LgsSema::visitFunc(LgsFunc* func) {
    func->id = ++funcsIDGenerator;
    if (func->isLambda) {
        func->funcType->name = LGS_LAMBDA;
    }
    const auto ft = func->funcType;
    validateLocalName(ft->name, ft->location);
    if (func->type->hasTypeParams()) return;
    stack.enterScope(func);
    visitFuncHeader(ft);
    visitStmtsBlock(func->stmtsBlock);
    if (ft->isVariadic && ft->hasDefaults) {
        addError(E10043, func->location);
    }
    if (!validateControlFlow(func->stmtsBlock, func)) {
        addError(E10055, func->location, {func->asText()});
    }
    stack.exitScope();
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
        const auto sArray = new LgsSArray(new LgsStr(), LGS_INT.getZeroValue());
        firstParam.setType(sArray);
        firstParam.expr = new LgsArrayExpr(sArray);
    }
    visitStmtsBlock(mainFunc->stmtsBlock);
    stack.exitScope();
}

void LgsSema::visitLambda(LgsFunc* lambda) {
    typeResolver.resolveFuncType(lambda->funcType);
    if (lambda->type->hasTypeParams()) return;
    visitFunc(lambda);
    lambda->inferRetType();
}

void LgsSema::visitObjImplements(LgsObject* obj, const std::vector<LgsType*>& interfaces) {
    std::unordered_set<std::string> seenNames;
    std::unordered_set<std::string> interfacesNames;
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
            if (interfaceMethod->stmtsBlock) continue;
            const auto objMethod = obj->methods.find(name);
            if (objMethod != obj->methods.end()) {
                const auto& objFuncType = objMethod->second->funcType;
                if (objFuncType->equals(interfaceMethod->type)) {
                    auto objMethodName = objMethod->first;
                    if (!seenNames.insert(objMethodName).second) {
                        addError(E10064, objMethod->second->location, {objMethodName});
                    }
                    continue;
                }
            }
            missingMethods.emplace_back(interfaceMethod);
        }
        if (!missingMethods.empty() || !missingFields.empty()) {
            addError(E10016, obj->location, {obj->pname(), interface->name, getMissingImplementsStr(missingFields, missingMethods)});
        }
    }
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
    if (param->name != "") {
        addLocalSymbol(LgsSymbol(param));
    }
    if (param->type->isVoid()) addError(E10093, param->location);
    addRTType(param->type);
    addGenericType(param->type);
}

void LgsSema::visitIOPair(LgsIOPair* ioPair, LgsObject* obj) {
    if (obj) {
        ioPair->openFunc = obj->getMethod(ioPair->openFuncName);
        ioPair->closeFunc = obj->getMethod(ioPair->closeFuncName);
    } else {
        ioPair->openFunc = getSymbol(ioPair->openFuncName)->func;
        ioPair->closeFunc = getSymbol(ioPair->closeFuncName)->func;
    }
    if (!ioPair->openFunc) {
        addError(E10084, ioPair->location, {ioPair->openFuncName});
    }
    if (!ioPair->closeFunc) {
        addError(E10084, ioPair->location, {ioPair->closeFuncName});
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

    // Check if it's lambda with one expr and replace with return stmt
    auto& firstStmt = stmtsBlock->stmts.front();
    const auto currentFunc = stack.currentFunc();
    const auto& ft = currentFunc->funcType;
    const auto firstStmtIsExpr = firstStmt.wrapperType == LgsStmtWrapper::WrapperType::Expr;
    if (currentFunc->isLambda && stmtsBlock->stmts.size() == 1 && firstStmtIsExpr) {
        visitExpr(firstStmt.expr);
        if (firstStmt.expr->type->isVoid()) return;
        ft->rt = firstStmt.expr->type;
        const auto returnStmt = new LgsReturn(firstStmt.expr);
        returnStmt->func = stack.currentFunc();
        firstStmt.stmt = returnStmt;
        firstStmt.wrapperType = LgsStmtWrapper::WrapperType::Stmt;
        currentFunc->returnStmts.push_back(returnStmt);
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
    const auto lastStmt = stmtsBlock->stmts.back();
    for (size_t i = 0; i < stmtsBlock->stmts.size() - 1; ++i) {
        if (stmtsBlock->stmts[i].isTerminator()) {
            return addError(E10059, lastStmt.stmt->location);
        }
    }
}

void LgsSema::visitVarDec(LgsVarDec* varDec) {
    validateLocalName(varDec->name, varDec->location);
    if (varDec->type) {
        if (const auto sArr = varDec->type->asSArray()) visitExpr(sArr->lengthExpr);
        typeResolver.resolveType(varDec->type);
        if (varDec->expr) {
            castExprImplicitly(varDec->expr, varDec->type);
            visitExpr(varDec->expr);
            validateExprType(varDec->expr, varDec->type);
            // TODO make merge types func
            if (varDec->type->asFuncType()) {
                varDec->setType(varDec->expr->type);
            } else {
                varDec->expr->setType(varDec->type);
            }
        } else {
            varDec->expr = varDec->type->getZeroValue();
            varDec->expr->location = varDec->location;
        }
    } else {
        visitExpr(varDec->expr);
        varDec->setType(varDec->expr->type);
        validateExprType(varDec->expr, varDec->type);
    }
    if (varDec->type->isVoid()) addError(E10093, varDec->location);
    else if (varDec->type->asFuncType() && varDec->isMutable) addError(E10034, varDec->location);
    addLocalSymbol(LgsSymbol(varDec));
    addRTType(varDec->type);
    addGenericType(varDec->type);
}

void LgsSema::visitAssignment(const LgsAssignment* assignment) {
    visitBinaryExpr(assignment->binaryExpr);
    const auto l = assignment->binaryExpr ? assignment->binaryExpr->left : assignment->left;
    auto r = assignment->binaryExpr ? assignment->binaryExpr->right : assignment->right;
    visitExpr(l);
    castExprImplicitly(r, l->type);
    visitExpr(r);
    if (l->asIterIndex()) {
        validateExprType(r, l->type);
    } else if (const auto lVar = l->asVariable()) {
        if (lVar->ref.symbolType != VAR_DEC || !lVar->ref.varDec->isMutable) {
            addError(E10051, l->location, {l->asText()});
        } else {
            validateExprType(r, l->type);
        }
    } else if (const auto selection = l->asSelection()) {
        if (selection->asMethodCall()) {
            addError(E10117, selection->location);
        } else {
            validateExprType(r, l->type);
        }
    } else {
        addError(E10051, l->location, {l->asText()});
    }
}

void LgsSema::visitIfStmt(LgsIfStmt* ifStmt) {
    if (ifStmt->ifBlock->isMacro) return visitMacroIf(ifStmt);
    stack.enterScope(ifStmt);
    const auto ifCond = ifStmt->ifCond;
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
    const auto ifCond = ifStmt->ifCond;
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
    if (!condType) return;

    // Allows local enum fields to not have a qualifier inside the block
    std::vector<LgsField*> fields;
    if (const auto enum_ = condType->asEnum()) {
        fields = enum_->asEnumField() ? getSymbol(enum_->name)->enum_->fields : enum_->fields;
        for (const auto& field : fields) {
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
        validateExprType(expr, condType);
        if (condType->asEnum()) {
            handledCases.insert(expr->asVariable()->name);
        }
        stack.exitScope();
    }

    if (switchStmt->elseBlock) {
        stack.enterScope(switchStmt);
        visitStmtsBlock(switchStmt->elseBlock);
        stack.exitScope();
    }
    stack.exitScope();
    if (!switchStmt->elseBlock && !condType->asEnum()) return;

    std::vector<std::string> missingCases;
    for (const auto& field : fields) {
        if (handledCases.contains(field->name)) continue;
        missingCases.push_back(field->name);
    }
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
    const auto startRange = rangeLoop->startRange;
    // endRange is already visited at replaceForLoops()
    const auto endRange = rangeLoop->endRange;
    assert(endRange);
    visitExpr(startRange);

    if (endRange->type && !endRange->type->isInt) {
        addError(E10082, endRange->location, {endRange->asText(), endRange->type->pname()});
    }

    if (startRange) {
        if (startRange->type && !startRange->type->isScalar()) {
            addError(E10082, startRange->location, {startRange->asText(), startRange->type->pname()});
        }
        if (!startRange->type->equals(endRange->type)) {
            addError(E10081, startRange->location, {startRange->asText(), endRange->asText()});
        }
    } else {
        rangeLoop->startRange = new LgsIntConst(&LGS_SIZE, 0);
    }

    if (!rangeLoop->loopVars.empty()) {
        // Range loop can have only one var
        const auto& firstVar = rangeLoop->loopVars.front();
        firstVar->setType(&LGS_SIZE);
        addLocalSymbol(LgsSymbol(firstVar));
    }
    visitStmtsBlock(rangeLoop->stmtsBlock);
}

void LgsSema::visitForeachLoop(LgsForeachLoop* foreachLoop) {
    const auto iterExpr = foreachLoop->iterExpr;
    visitExpr(iterExpr);
    const auto iterable = iterExpr->type->asIterable();
    if (!iterable) {
        if (!iterExpr->type) return;
        addError(E10002, iterExpr->location, {iterExpr->asText()});
        return;
    }

    const auto loopVarsLen = foreachLoop->loopVars.size();
    if (stack.getInnermostForeachLoop() == foreachLoop && loopVarsLen == 0) {
        auto varDec = new LgsVarDec("for.element", nullptr);
        varDec->type = iterable->baseType;
        foreachLoop->loopVars.emplace_back(varDec);
    }
    if (!iterable->baseType) return;
    const bool unpacked = iterable->unpackLoopVars(foreachLoop);
    if (!unpacked) {
        addError(E10041, iterExpr->location, {iterExpr->asText(), iterExpr->type->pname(), to_string(loopVarsLen)});
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

void LgsSema::visitWhileLoop(const LgsWhileLoop* whileLoop) {
    visitExpr(whileLoop->condExpr);
    const auto condType = whileLoop->condExpr->type;
    if (!condType->asBool()) {
        addError(E10066, whileLoop->location, {whileLoop->condExpr->asText(), condType->pname()});
    }
    visitStmtsBlock(whileLoop->stmtsBlock);
}

void LgsSema::visitReturnStmt(LgsReturn* returnStmt) {
    returnStmt->func = stack.currentFunc();
    const auto ft = returnStmt->func->funcType;
    auto retExpr = returnStmt->expr;
    if (retExpr) {
        castExprImplicitly(retExpr, ft->rt);
        visitExpr(retExpr);
        returnStmt->func->returnStmts.push_back(returnStmt);
        if (retExpr->type->isVoid()) addError(E10093, returnStmt->location);
    }
    for (auto frame : stack.frames) {
        if (frame.ioStmt) returnStmt->ioStmts.push_back(frame.ioStmt);
    }
    const auto rt = ft->rt;
    if (!rt) return;
    if (rt->isVoid() && retExpr && retExpr->type && !retExpr->type->isVoid()) {
        addError(E10027, returnStmt->location);
    } else if (!rt->isVoid() && !retExpr) {
        addError(E10026, returnStmt->location, {ft->name, rt->pname()});
    } else if (retExpr && retExpr->type && !rt->canCastTo(retExpr->type)) {
        addError(E10004, returnStmt->location, {ft->name, rt->pname(), retExpr->type->pname()});
    } else if (!rt->isVoid()) {
        validateExprType(retExpr, ft->rt);
    }
}

void LgsSema::visitContinueStmt(LgsContinue* continueStmt) {
    const auto currentLoop = stack.currentLoop();
    if (!currentLoop) {
        addError(E10038, continueStmt->location);
    }
    continueStmt->forLoop = currentLoop;
}

void LgsSema::visitBreakStmt(LgsBreak* breakStmt) {
    if (breakStmt->isBreakIf) {
        breakStmt->ifStmt = stack.getOutermostIfStmt();
        if (!breakStmt->ifStmt) {
            addError(E10071, breakStmt->location);
        }
        return;
    }
    breakStmt->forLoop = stack.currentLoop();
    if (!breakStmt->forLoop && breakStmt->tag == "") {
        addError(E10017, breakStmt->location);
    }
}

void LgsSema::visitCoroutine(const LgsCoroutine* coroutine) {
    assert(0);
}

void LgsSema::visitDeferStmt(const LgsDeferStmt* deferStmt) {
    visitExpr(deferStmt->expr);
}

void LgsSema::visitIOStmt(LgsIOStmt* ioStmt) {
    stack.enterScope(ioStmt);
    const auto openExpr = ioStmt->varDec->expr;
    visitExpr(openExpr);
    const auto funcCall = openExpr->asFuncCall() ? openExpr->asFuncCall() : openExpr->asSelection()->asMethodCall();
    if (currentObj) {
        for (const auto ioPair : currentObj->ioPairs) {
            if (!funcCall->equals(ioPair->openFunc->funcType)) continue;
            ioStmt->closeFunc = ioPair->closeFunc;
        }
    } else if (file->asMainFile()) {
        for (const auto ioPair : file->asMainFile()->ioPairs) {
            if (!funcCall->equals(ioPair->openFunc->funcType)) continue;
            ioStmt->closeFunc = ioPair->closeFunc;
        }
    }
    visitStmtsBlock(ioStmt->stmtsBlock);
    stack.exitScope();
}

void LgsSema::visitExpr(LgsExpr* expr) {
    if (!expr) return;
    if (const auto ternaryExpr = dynamic_cast<LgsTernaryExpr*>(expr)) {
        visitTernaryExpr(ternaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
    } else {
        if (const auto variable = expr->asVariable()) visitVariable(variable);
        else if (const auto lambda = expr->asFunc()) visitLambda(lambda);
        else if (const auto moduleExpr = expr->asModuleExpr()) visitModuleExpr(moduleExpr);
        else if (const auto instance = expr->asInstance()) visitInstance(instance);
        else if (const auto funcCall = expr->asFuncCall()) visitFuncCall(funcCall);
        else if (const auto strConst = expr->asStrConst()) visitStrConst(strConst);
        else if (const auto selection = expr->asSelection()) visitSelection(selection);
        else if (const auto metaSelection = expr->asMetaSelection()) visitMetaSelection(metaSelection);
        else if (const auto nullableExpr = expr->asNullableExpr()) visitNullableExpr(nullableExpr);
        else if (const auto arrayExpr = expr->asArrayExpr()) visitArrayExpr(arrayExpr);
        else if (const auto hashMap = expr->asHashMap()) visitHashMap(hashMap);
        else if (const auto iterIndex = expr->asIterIndex()) visitIterIndex(iterIndex);
        else if (const auto postfixExpr = expr->asPostfixExpr()) visitPostfixExpr(postfixExpr);
        else if (const auto prefixExpr = expr->asPrefixExpr()) visitPrefixExpr(prefixExpr);
        else if (const auto forVar = expr->asLoopMetaVar()) visitLoopMetaVar(forVar);
        else if (const auto vecExpr = expr->asVectorExpr()) visitVectorExpr(vecExpr);
        else if (const auto matrixExpr = expr->asMatrixExpr()) visitMatrixExpr(matrixExpr);
        else if (const auto castExpr = expr->asCast()) visitCast(castExpr);
        visitUnwrap(expr);
    }
    addRTType(expr->type);
}

void LgsSema::visitBinaryExpr(LgsBinaryExpr* binaryExpr) {
    if (!binaryExpr) return;
    const auto& l = binaryExpr->left;
    const auto& r = binaryExpr->right;
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
        return addError(E10076, binaryExpr->location, {binaryExpr->op.text, ltype->pname(), rtype->pname()});
    }
    binaryExpr->setType(type);
}

void LgsSema::visitTernaryExpr(LgsTernaryExpr* ternary) {
    const auto condExpr = ternary->condExpr;
    const auto thenExpr = ternary->thenExpr;
    const auto elseExpr = ternary->elseExpr;
    visitExpr(condExpr);
    if (!condExpr->type->asBool()) {
        addError(E10092, condExpr->location, {condExpr->type->pname()});
    }
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
    castExprImplicitly(cast->fromValue, cast->toType);
    if (!cast->value) {
        addError(E10018, cast->location, {cast->fromValue->asText(), cast->toType->pname()});
        return;
    }
    cast->setType(cast->value->type);
}

void LgsSema::visitNullableExpr(LgsNullableExpr* nullableExpr) {
    if (nullableExpr->isNull) return;
    const auto baseExpr = nullableExpr->baseExpr;
    visitExpr(baseExpr);
    if (baseExpr->type->asNullable()) return;
    nullableExpr->setType(new LgsNullable(baseExpr->type));
}

void LgsSema::visitArrayExpr(LgsArrayExpr* arrayExpr) {
    if (!arrayExpr->type && arrayExpr->elements.empty()) {
        return addError(E10095, arrayExpr->location);
    }
    if (!arrayExpr->iterable) arrayExpr->setType(new LgsDArray());
    const auto baseType = arrayExpr->iterable->baseType;
    for (auto element : arrayExpr->elements) {
        castExprImplicitly(element, baseType);
        visitExpr(element);
    }
    arrayExpr->iterable->baseType = inferType(arrayExpr->elements);
    if (!arrayExpr->iterable->baseType) {
        return addError(E10095, arrayExpr->location);
    }

    if (arrayExpr->type->asSArray()) {
        const auto sArr = arrayExpr->type->asSArray();
        const auto size = sArr->lengthExpr->getConstInt();
        if (!size.has_value()) {
            addError(E10114, arrayExpr->location);
        } else if (size.value() < static_cast<int64_t>(arrayExpr->elements.size())) {
            addError(E10105, arrayExpr->location, {to_string(*size)});
        } else {
            sArr->len = size.value();
        }
    }
}

void LgsSema::visitHashMap(LgsHashMap* hashMap) {
    for (const auto pair : hashMap->elements) {
        visitExpr(pair->key);
        visitExpr(pair->value);
    }
    if (!hashMap->type && hashMap->elements.empty()) {
        return addError(E10049, hashMap->location, {LgsMap::name});
    }
    if (!hashMap->type && !hashMap->elements.empty()) {
        const auto pair = hashMap->elements.front();
        hashMap->setType(new LgsMap(pair->key->type, pair->value->type));
    }
}

void LgsSema::visitVectorExpr(LgsVectorExpr* vectorExpr) {
    const auto vec = vectorExpr->vecType;
    LgsType* inferredType = nullptr;
    if (vectorExpr->elements.empty()) {
        vectorExpr->vecType->baseType = &LGS_FLOAT;
    } else {
        for (const auto arg : vectorExpr->elements) {
            visitExpr(arg);
            if (!arg->type) continue;
            if (arg->type->isScalar()) {
                inferredType = arg->type;
                vectorExpr->sumArgsDim++;
            } else if (const auto innerVec = arg->type->asVec()) {
                const auto nestedBaseType = innerVec->getNestedBaseType();
                inferredType = nestedBaseType;
                vectorExpr->sumArgsDim += innerVec->dimVec;
            } else {
                addError(E10073, vectorExpr->location);
                break;
            }
        }
        if (!inferredType) {
            addError(E10095, vectorExpr->location);
            return;
        }
        vectorExpr->vecType->baseType = inferredType;
        if (vectorExpr->sumArgsDim > vectorExpr->vecType->dimVec) {
            addError(E10069, vectorExpr->location, {vec->pname()});
        }
    }
}

void LgsSema::visitMatrixExpr(const LgsMatrixExpr* matrixExpr) {
    if (matrixExpr->rows.empty()) return;
    if (matrixExpr->rows.size() > matrixExpr->matType->rows) {
        addError(E10103, matrixExpr->location, {matrixExpr->matType->pname(), to_string(matrixExpr->rows.size())});
        return;
    }
    for (auto row : matrixExpr->rows) {
        const auto arr = row->type->asIterable();
        if (arr) {
            const auto len = arr->getConstLength();
            if (len.has_value() && len.value() > matrixExpr->matType->columns) {
                addError(E10104, matrixExpr->location, {matrixExpr->matType->pname(), to_string(len.value())});
            }
            return;
        }
        const auto baseType = matrixExpr->matType->baseType;
        castExprImplicitly(row, baseType);
        visitExpr(row);
        row->setType(new LgsSArray(baseType, matrixExpr->matType->columns));
    }
}

void LgsSema::visitVariable(LgsVariable* variable) {
    if (variable->name == LGS_SELF_CLASS) {
        variable->ref.symbolType = OBJECT;
        variable->ref.object = currentObj;
        variable->setType(currentObj);
        return;
    }
    const auto symbol = getSymbol(variable->name);
    if (!symbol) return addError(E10006, variable->location, {variable->name});
    variable->ref.symbolType = symbol->symbolType;
    switch (symbol->symbolType) {
    case VAR_DEC: {
        variable->ref.varDec = symbol->varDec;
        variable->isMutable = symbol->varDec->isMutable;
        variable->setType(symbol->varDec->type);
        break;
    }
    case PARAM: {
        variable->ref.param = symbol->param;
        variable->isMutable = false;
        variable->setType(symbol->param->type);
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
        variable->isMutable = false;
        variable->setType(symbol->func->funcType);
        break;
    }
    case OBJECT: {
        variable->ref.object = symbol->object;
        variable->isMutable = false;
        variable->setType(symbol->object);
        break;
    }
    case FIELD: {
        variable->ref.field = symbol->field;
        variable->setType(symbol->field->type);
        if (symbol->field->type->asEnum()) {
            variable->isMutable = false;
        }
        break;
    }
    case INTERFACE:
    case SUBTYPE:
    case UNKNOWN:
        assert(0);
    }
}

void LgsSema::visitSelection(LgsSelection* selection) {
    const auto exprs = selection->exprs;
    visitExpr(selection->exprs.front());
    visitInnerSelections(selection);
    selection->setType(selection->exprs.back()->type);
}

void LgsSema::visitInnerSelections(const LgsSelection* selection) {
    const auto& exprs = selection->exprs;
    for (size_t i = 0; i < exprs.size() - 1; ++i) {
        const auto parent = exprs[i];
        const auto& child = exprs[i + 1];
        if (const auto var = child->asVariable()) {
            visitFieldSelection(var, parent);
        } else if (const auto methodCall = child->asFuncCall()) {
            visitMethodCall(methodCall, parent);
        } else if (const auto iterIndex = child->asIterIndex()) {
            visitIterIndexSelection(iterIndex, parent->type);
        } else if (const auto metaSelection = child->asMetaSelection()) {
            visitMetaSelection(metaSelection, parent);
        } else if (const auto instance = child->asInstance()) {
            visitInstance(instance);
        } else {
            assert(0);
        }
        if (!child->type || child->type->isUnknown()) return;
        addRTType(child->type);
    }
}

void LgsSema::visitFieldSelection(LgsVariable* child, LgsExpr* parent) {
    if (!parent) return;
    if (const auto var = parent->asVariable()) {
        if (var->ref.symbolType == OBJECT) {
            addError(E10089, var->location);
            return;
        }
    }
    const auto parentType = parent->type;
    if (parentType->asVec() && !validateVecElements(child, parentType->asVec())) return;
    auto childName = child->name;
    if (const auto field = parentType->getField(childName)) {
        child->setType(field->type);
        child->isMutable = field->isMutable;
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

void LgsSema::visitMetaSelection(LgsMetaSelection* metaSelection, LgsExpr* parent) {
    const auto funcCall = metaSelection->baseExpr->asFuncCall();
    if (funcCall && parent) {
        visitMethodCall(funcCall, parent);
    } else {
        visitExpr(metaSelection->baseExpr);
    }

    const auto obj = metaSelection->baseExpr->type->asObject();
    if (!obj) {
        return addError(E10058, metaSelection->location);
    }

    // Meta fields
    if (const auto var = metaSelection->child->asVariable()) {
        if (!obj->metaFields.contains(var->name)) {
            addError(E10005, metaSelection->location, {var->name, obj->pname()});
            return;
        }
        var->ref.symbolType = FIELD;
        var->ref.field = obj->metaFields[var->name];
        var->setType(var->ref.field->type);
        metaSelection->setType(var->type);
        return;
    }

    // Meta funcs
    const auto methodCall = metaSelection->child->asFuncCall();
    if (!methodCall) return;
    if (!obj->getMetaFunc(methodCall->name)) {
        addError(E10005, metaSelection->location, {methodCall->asText(), obj->pname()});
        return;
    }
    const auto method = obj->metaFuncs[methodCall->name];
    if (!visitFuncArgs(methodCall, method->funcType)) return;
    if (methodCall->equals(method->funcType)) {
        methodCall->func = method;
        methodCall->setType(method->funcType->rt);
    } else {
        addError(E10015, methodCall->location, {methodCall->name, methodCall->asText(), method->asText()});
    }
    methodCall->args.insert(methodCall->args.begin(), LgsVarDec(LGS_SELF, metaSelection->baseExpr));
    metaSelection->setType(methodCall->type);
}

void LgsSema::visitFuncCall(LgsFuncCall* funcCall) {
    const auto symbol = getSymbol(funcCall->name);
    if (!symbol) return addError(E10006, funcCall->location, {funcCall->name});
    const auto ft = symbol->getType()->asFuncType();
    if (!ft) return addError(E10046, funcCall->location, {funcCall->name});

    if (!visitFuncArgs(funcCall, ft)) return;
    if (!funcCall->equals(ft)) {
        addError(E10015, funcCall->location, {funcCall->name, funcCall->asText(), ft->pname()});
        return;
    }
    if (symbol->symbolType != FUNC) {
        funcCall->ref = *symbol;
        funcCall->setType(ft->rt);
        return;
    }
    setFunc(funcCall, symbol->func);
}

void LgsSema::visitMethodCall(LgsFuncCall* methodCall, LgsExpr* parent) {
    auto name = methodCall->name;
    const auto method = parent->type->getMethod(name);
    if (!method) {
        return addError(E10005, methodCall->location, {name, parent->type->pname()});
    }
    if (method->funcType->hasSelf) {
        if (parent->asInstance() || parent->asVariable()->ref.symbolType == OBJECT) {
            if (!parent->type->asObject()->isSingleton) {
                return addError(E10083, methodCall->location, {method->funcType->name});
            }
        }
    }
    if (method->funcType->isMethod || method->funcType->isVirtual) {
        methodCall->args.insert(methodCall->args.begin(), LgsVarDec(LGS_SELF, parent));
    }
    if (!visitFuncArgs(methodCall, method->funcType)) return;
    if (!methodCall->equals(method->funcType)) {
        addError(E10015, methodCall->location, {name, methodCall->asText(), method->asText()});
        return;
    }
    if (!validateMethodVisibility(method, parent->type, methodCall->location)) return;
    setFunc(methodCall, method);
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
            visitArg(arg.name == "", arg, paramsByName[arg.name], funcCall->location);
        }
    } else {
        for (size_t i = ft->isMethod; i < ft->params.size(); ++i) {
            if (i >= funcCall->args.size()) break;
            auto& arg = funcCall->args[i];
            visitArg(arg.name != "", arg, &ft->params[i], funcCall->location);
        }
        if (ft->isVariadic) {
            const auto& param = ft->params.back();
            for (size_t i = ft->params.size(); i < funcCall->args.size(); ++i) {
                if (i >= funcCall->args.size()) break;
                auto& arg = funcCall->args[i];
                visitArg(arg.name != "", arg, &param, funcCall->location);
            }
        }
    }
    return true;
}

void LgsSema::visitArg(const bool isMixed, LgsVarDec& varDec, const LgsParam* param, const LgsLocation& location) {
    castExprImplicitly(varDec.expr, param->type);
    visitExpr(varDec.expr);
    if (isMixed) {
        addError(E10096, location);
    }
}

void LgsSema::visitModuleExpr(LgsModuleExpr* moduleExpr) {
    for (const auto importApp : importApps) {
        if (importApp->configs.name == moduleExpr->name) {
            moduleExpr->moduleGlobals = &importApp->globals;
            return;
        }
    }
    addError(E10006, moduleExpr->location, {moduleExpr->name});
}

void LgsSema::visitPrefixExpr(LgsPrefixExpr* prefixExpr) {
    const auto baseExpr = prefixExpr->expr;
    visitExpr(baseExpr);
    switch (prefixExpr->op) {
    case MINUS_PREFIX: {
        if (!baseExpr->type->isScalar()) {
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
        if (!baseExpr->type->isScalar()) {
            addError(E10090, prefixExpr->location, {"_/", baseExpr->type->pname()});
            return;
        }
        prefixExpr->setType(&LGS_DOUBLE);
        break;
    }
    }
}

void LgsSema::visitPostfixExpr(LgsPostfixExpr* postfixExpr) {
    const auto baseExpr = postfixExpr->baseExpr;
    visitExpr(baseExpr);
    const auto type = baseExpr->type;
    if (!type->isScalar()) {
        return addError(E10050, postfixExpr->location, {type->pname()});
    }
    if (baseExpr->asVariable() && !baseExpr->isMutable) {
        return addError(E10051, postfixExpr->location, {baseExpr->asText()});
    }
    postfixExpr->setType(type);
}

void LgsSema::visitStrConst(const LgsStrConst* strConst) {
    if (strConst->parts.empty()) return;
    for (const auto templatePart : strConst->parts) {
        visitExpr(templatePart);
    }
}

void LgsSema::visitInstance(LgsInstance* instance) {
    const auto objName = instance->name;
    const auto symbol = getSymbol(objName);
    if (!symbol) return addError(E10006, instance->location, {instance->name});
    if (!validateTypeName(instance->name, instance->location)) return;
    if (!symbol->getType()->asObject()) {
        return addError(E10022, instance->location, {objName});
    }

    if (symbol->symbolType == INTERFACE) {
        return visitInlineInterface(instance, symbol->interface);
    }
    if (symbol->symbolType == VAR_DEC) {
        const auto singleton = symbol->varDec->type->asObject();
        if (singleton && singleton->isSingleton) {
            return addError(E10032, instance->location, {objName});
        }
    }

    instance->setType(symbol->object->clone());
    const auto obj = instance->obj;
    if (obj->typeParams.empty() && !instance->typeArgs.empty()) {
        return addError(E10120, obj->location, {instance->name});
    }
    const auto typeArgsSize = instance->typeArgs.size();
    if (obj->typeParams.size() < typeArgsSize) {
        return addError(E10115, instance->location);
    }

    // Args
    std::unordered_set<std::string> visited;
    auto& replacements = obj->replacements;
    for (size_t i = 0; i < instance->args.size(); ++i) {
        auto arg = instance->args[i];
        const auto name = arg.name;
        if (visited.contains(name)) addError(E10054, arg.expr->location, {name});
        visited.insert(name);
        const auto field = obj->getField(name);
        if (!field) {
            addError(E10005, arg.expr->location, {name, objName});
            continue;
        }
        if (!validateFieldVisibility(field, obj, arg.expr->location)) continue;
        castExprImplicitly(arg.expr, field->type);
        visitExpr(arg.expr);
        validateExprType(arg.expr, field->type);
    }

    if (obj->hasTypeParams()) {
        // Init replacements
        auto allReplsAreSet = true;
        for (size_t i = 0; i < obj->typeParams.size(); ++i) {
            const auto typeParam = obj->typeParams[i];
            const auto value = i < typeArgsSize ? instance->typeArgs[i] : nullptr;
            replacements[typeParam->name] = value;
            allReplsAreSet = allReplsAreSet && value;
        }
        // Add replacements
        if (!allReplsAreSet) {
            for (auto arg : instance->args) {
                for (auto field : obj->fields) {
                    if (arg.name != field->name) continue;
                    addTypeReplacement(field->type, arg.expr->type, replacements);
                }
            }
        }
        for (auto field : obj->fields) {
            field->parentType = obj;
        }
        for (const auto& [_, method] : obj->methods) {
            replaceGenericFunc(method, replacements);
        }
        replaceGenerics(instance->type, replacements);
        for (const auto& [_, method] : obj->methods) {
            method->funcType->params[0].type = instance->obj;
        }
        visitObject(instance->obj);
    }

    for (const auto field : obj->fields) {
        if (visited.contains(field->name)) continue;
        field->expr = field->type->getZeroValue();
    }
}

void LgsSema::visitUnwrap(LgsExpr* expr) {
    if (!expr->type || !expr->hasUnwrap) return;
    if (!expr->type->asNullable()) {
        addError(E10113, expr->location, {expr->type->pname()});
        return;
    }
    const auto nullable = expr->type->asNullable();
    expr->setType(nullable->baseType);
}

void LgsSema::visitInlineInterface(LgsInstance* instance, LgsInterface* interface) {
    const auto obj = new LgsObject(instance->name + to_string(objsIDGenerator++));
    obj->implements.push_back(interface);
    auto isValid = true;
    for (auto& arg : instance->args) {
        const auto name = arg.name;
        if (const auto field = interface->getField(name)) {
            castExprImplicitly(arg.expr, field->type);
            visitExpr(arg.expr);
            isValid = isValid && validateExprType(arg.expr, field->type);
            if (!isValid) continue;
            const auto newField = new LgsField(*field);
            newField->expr = arg.expr;
            obj->fields.push_back(newField);
        } else if (const auto interfaceMethod = interface->getMethod(name)) {
            castExprImplicitly(arg.expr, interfaceMethod->type);
            visitExpr(arg.expr);
            isValid = isValid && validateExprType(arg.expr, interfaceMethod->type);
            if (!isValid) continue;
            const auto method = arg.expr->asFunc();
            method->funcType->isMethod = true;
            method->funcType->name = name;
            obj->methods[name] = method;
        } else {
            addError(E10005, arg.expr->location, {name, interface->name});
            isValid = false;
        }
    }
    if (!isValid) return;
    visitObjImplements(obj, obj->implements);
    instance->setType(obj);
}

void LgsSema::visitIterIndex(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    visitExpr(baseExpr);
    if (!baseExpr->type) return;
    const auto iterable = baseExpr->type->asIterable();
    if (!iterable || iterable->asVariadic()) {
        return addError(E10108, iterIndex->location, {baseExpr->asText()});
    }
    visitIndex(iterIndex);
}

void LgsSema::visitIndex(LgsIterIndex* iterIndex) {
    const auto exprFrom = iterIndex->index.from;
    const auto exprTo = iterIndex->index.to;
    visitExpr(exprFrom);
    visitExpr(exprTo);
    validateIndex(iterIndex);
    const auto baseType = iterIndex->baseExpr->type;
    const auto nullable = baseType->asNullable();
    const auto iterable = nullable ? nullable->baseType->asIterable() : baseType->asIterable();
    const auto type = exprTo ? iterable : iterable->getValueType();
    iterIndex->setType(type);
}

void LgsSema::visitLoopMetaVar(LgsMetaVar* metaVar) {
    metaVar->forLoop = stack.currentLoop();
    if (!metaVar->forLoop) {
        return addError(E10060, metaVar->location);
    }
    const auto name = metaVar->asText();
    if (metaVar->forLoop->asWhileLoop() || metaVar->forLoop->asWhileLoop()) {
        return addError(E10061, metaVar->location, {name});
    }
    if (metaVar->varType == FOR_ELEMENT) {
        const auto loopVar = stack.getInnermostForeachLoop()->loopVars.front();
        metaVar->setType(loopVar->type);
    }
    if (!metaVar->forLoop->metaVars.contains(metaVar->varType)) {
        metaVar->forLoop->metaVars[metaVar->varType] = metaVar;
    }
}

bool LgsSema::validateExprType(const LgsExpr* expr, LgsType* type) {
    if (!type || !expr->type || type->isUnknown() || expr->type->isUnknown()) return false;
    if (const auto nullable = type->asNullable()) {
        if (expr->isNull && !nullable->baseType) {
            addError(E10024, expr->location);
            return false;
        }
    }
    if (expr->isNull && !type->asNullable()) {
        addError(E10023, expr->location);
        return false;
    }
    if (expr->type == type) return true;
    if (!expr->type->canCastTo(type)) {
        addError(E10001, expr->location, {type->pname(), expr->type->pname()});
        return false;
    }
    return true;
}

bool LgsSema::validateTypeName(const std::string& name, const LgsLocation& location) {
    const auto symbol = getSymbol(name);
    if (symbol->isExternal) return true;
    if (symbol && symbol->isBuiltin) {
        addError(E10053, location, {name});
        return false;
    }
    if (islower(name[0])) {
        addError(E10033, location);
        return false;
    }
    return true;
}

bool LgsSema::validateLocalName(const std::string& name, const LgsLocation& location) {
    if (name == "") return true;
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

void LgsSema::validateIndex(const LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto exprFrom = iterIndex->index.from;
    const auto exprTo = iterIndex->index.to;
    const auto iterable = baseExpr->type->asIterable();
    const auto iterIndexType = iterable->getIndexType();

    // Left index
    if (!exprFrom->type->canCastTo(iterIndexType)) {
        return addError(E10036, iterIndex->location, {exprFrom->type->pname()});
    }
    const auto indexFrom = exprFrom->getConstInt();
    if (!indexFrom.has_value()) return;
    const auto iterableLength = iterable->getConstLength();
    if (iterableLength.has_value() && indexFrom.value() >= static_cast<int64_t>(iterableLength.value())) {
        return addError(E10003, iterIndex->location, {to_string(iterableLength.value())});
    }

    // Slice indices
    if (exprTo) {
        if (!baseExpr->type->isSliceable()) {
            return addError(E10042, iterIndex->location, {baseExpr->type->pname()});
        }
        if (!exprTo->type->canCastTo(iterIndexType)) {
            return addError(E10036, iterIndex->location, {exprTo->type->pname()});
        }
        const auto indexTo = exprTo->getConstInt();
        if (!indexTo.has_value()) return;
        if (indexFrom.value() > indexTo.value()) {
            return addError(E10037, iterIndex->location);
        }
    }
}

bool LgsSema::validateFieldVisibility(LgsField* field, LgsType* parent, const LgsLocation& location) {
    assert(parent);
    if (parent->asVec()) return true;
    if (parent->asObject() && parent->asObject()->isSingleton) return true;
    if (!field || field->isVirtual) return false;
    if (stack.currentFunc()->isTest) return true;
    assert(field->location.filepath != "");
    const auto hasAccess = field->isPublic || file->path == field->location.filepath;
    if (!hasAccess) {
        addError(E10030, location, {field->name, parent->pname()});
        return false;
    }
    return true;
}

bool LgsSema::validateMethodVisibility(const LgsFunc* method, LgsType* parent, const LgsLocation& location) {
    if (!method) return false;
    if (parent && parent->asObject() && parent->asObject()->isSingleton) return true;
    const auto hasAccess = method->funcType->isPublic || file->path == method->location.filepath || stack.currentFunc()->isTest;
    if (!hasAccess) {
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

void LgsSema::validateObjDuplicates(LgsObject* obj) {
    std::unordered_set<std::string> names;
    for (const auto* f : obj->fields) {
        if (!f) continue;
        const auto& name = f->name;
        if (!names.insert(name).second) {
            addError(E10056, obj->location, {obj->pname(), name});
            break;
        }
    }
    for (const auto& [name, func] : obj->methods) {
        if (!names.insert(name).second) {
            addError(E10056, obj->location, {obj->pname(), name});
            break;
        }
        for (const auto mtp : func->funcType->typeParams) {
            for (const auto otp : obj->typeParams) {
                if (mtp->name == otp->name) {
                    addError(E10011, mtp->location, {mtp->name});
                }
            }
        }
    }
}

bool LgsSema::validateControlFlow(const LgsStmtsBlock* stmtBlock, const LgsFunc* func) {
    if (!stmtBlock || func->funcType->rt->isVoid()) return true;
    if (stmtBlock->stmts.empty()) return false;
    const auto lastStmt = stmtBlock->stmts.back();
    constexpr auto objWrapper = LgsStmtWrapper::WrapperType::Object;
    constexpr auto stmtWrapper = LgsStmtWrapper::WrapperType::Stmt;
    constexpr auto exprWrapper = LgsStmtWrapper::WrapperType::Expr;
    const auto isStmt = lastStmt.wrapperType == stmtWrapper;
    if (isStmt && lastStmt.stmt->asReturn()) return true;
    if (lastStmt.wrapperType == objWrapper || lastStmt.wrapperType == exprWrapper) return false;
    if (const auto ifStmt = lastStmt.stmt->asIfStmt()) {
        if (!ifStmt->elseBlock) return false;
        auto isValid = validateControlFlow(ifStmt->ifBlock, func);
        for (const auto [_, elseIfStmt] : ifStmt->elseIfs) {
            isValid = isValid && validateControlFlow(elseIfStmt, func);
        }
        return isValid && validateControlFlow(ifStmt->elseBlock, func);
    }
    if (const auto switch_ = lastStmt.stmt->asSwitch()) {
        if (!switch_->elseBlock) return false;
        auto isValid = true;
        for (const auto [_, patternsStmtBlock] : switch_->patterns) {
            isValid = isValid && validateControlFlow(patternsStmtBlock, func);
        }
        return isValid && validateControlFlow(switch_->elseBlock, func);
    }
    return false;
}

void LgsSema::setFunc(LgsFuncCall* funcCall, LgsFunc* func) {
    if (func->funcType->typeParams.empty() && !funcCall->typeArgs.empty()) {
        return addError(E10119, func->location, {funcCall->name});
    }
    const auto typeArgsSize = funcCall->typeArgs.size();
    if (func->funcType->typeParams.size() < typeArgsSize) {
        return addError(E10115, funcCall->location);
    }
    if (func->funcType->typeParams.empty()) {
        funcCall->func = func;
        funcCall->setType(funcCall->func->funcType->rt);
        return;
    }

    // Generic call
    LgsFunc* newFunc = nullptr;
    const auto mangledName = funcCall->mangleName();
    if (file->symbolTable.genericFuncs.contains(mangledName)) {
        newFunc = file->symbolTable.genericFuncs[mangledName];
    } else {
        // Init replacements
        newFunc = func->clone();
        auto& replacements = newFunc->replacements;
        auto allReplsAreSet = true;
        for (size_t i = 0; i < newFunc->funcType->typeParams.size(); ++i) {
            const auto typeParam = newFunc->funcType->typeParams[i];
            const auto value = i < typeArgsSize ? funcCall->typeArgs[i] : nullptr;
            replacements[typeParam->name] = value;
            allReplsAreSet = allReplsAreSet && value;
        }
        newFunc->returnStmts.clear();
        newFunc->funcType->typeParams.clear();
        // Add replacements
        if (!allReplsAreSet) {
            for (size_t i = 0; i < funcCall->args.size(); ++i) {
                if (i >= newFunc->funcType->params.size()) break;
                const auto argExpr = funcCall->args[i].expr;
                const auto& param = newFunc->funcType->params[i];
                addTypeReplacement(param.type, argExpr->type, replacements);
            }
        }
        // Resolve the args if they still have generics. Mostly used in lambda.
        for (size_t i = 0; i < funcCall->args.size(); ++i) {
            if (i >= newFunc->funcType->params.size()) break;
            const auto arg = funcCall->args[i];
            const auto& param = newFunc->funcType->params[i];
            if (!arg.expr->type->hasTypeParams()) continue;
            if (const auto lambdaType = arg.expr->type->asFuncType()) {
                lambdaType->typeParams.clear();
            }
            replaceGenerics(arg.expr->type, replacements);
            visitExpr(arg.expr);
            addTypeReplacement(param.type, arg.expr->type, replacements);
        }
        // Replace the types and visit the actual function.
        replaceGenericFunc(newFunc, replacements);
        visitFunc(newFunc);
        file->symbolTable.genericFuncs.emplace(funcCall->mangleName(), newFunc);
    }
    funcCall->func = newFunc;
    funcCall->setType(funcCall->func->funcType->rt);
}

void LgsSema::addTypeReplacement(LgsType* genericType, LgsType* replacement, std::unordered_map<std::string, LgsType*>& replacements) {
    if (!replacement) return;
    if (!genericType->canCastTo(replacement)) {
        addError(E10116, genericType->location, {genericType->pname()});
        return;
    }
    if (const auto iter = replacement->asIterable()) {
        addTypeReplacement(genericType->asIterable()->baseType, iter->baseType, replacements);
    } else if (const auto ft = replacement->asFuncType()) {
        const auto genericFT = genericType->asFuncType();
        for (size_t i = 0; i < ft->params.size(); ++i) {
            addTypeReplacement(genericFT->params[i].type, ft->params[i].type, replacements);
        }
        addTypeReplacement(genericFT->rt, ft->rt, replacements);
    } else {
        const auto name = genericType->getName();
        if (replacements.contains(name) && replacements[name] == nullptr) {
            if (replacement->hasTypeParams()) return;
            replacements[name] = replacement;
        }
    }
}

void LgsSema::replaceGenericFunc(LgsFunc* newFunc, const std::unordered_map<std::string, LgsType*>& replacements) {
    replaceGenerics(newFunc->type, replacements);
    if (!newFunc->stmtsBlock) return;
    for (auto& stmt : newFunc->stmtsBlock->stmts) {
        switch (stmt.wrapperType) {
        case LgsStmtWrapper::WrapperType::Stmt:
            if (const auto varDec = stmt.stmt->asVarDec()) {
                replaceGenerics(varDec->type, replacements);
            }
            break;
        case LgsStmtWrapper::WrapperType::Expr:
            replaceGenerics(stmt.expr->type, replacements);
            break;
        case LgsStmtWrapper::WrapperType::Object: {
            auto type = dynamic_cast<LgsType*>(stmt.obj);
            replaceGenerics(type, replacements);
            stmt.obj = type->asObject();
            break;
        }
        }
    }
}

void LgsSema::replaceGenerics(LgsType*& type, const std::unordered_map<std::string, LgsType*>& replacements) {
    if (const auto iter = type->asIterable()) {
        replaceGenerics(iter->baseType, replacements);
    } else if (const auto ft = type->asFuncType()) {
        for (auto & param : ft->params) {
            if (param.name == LGS_SELF) continue;
            replaceGenerics(param.type, replacements);
        }
        replaceGenerics(ft->rt, replacements);
        ft->typeParams.clear();
    } else if (const auto obj = type->asObject()) {
        for (const auto field : type->fields) {
            replaceGenerics(field->type, replacements);
        }
        for (const auto [name, method] : type->methods) {
            replaceGenerics(method->type, replacements);
        }
        obj->typeParams.clear();
    } else if (type->asTypeParam()) {
        const auto repl = replacements.at(type->getName());
        if (repl) {
            type = repl;
        }
    } else if (type->isUnknown()) {
        const auto repl = replacements.at(type->getName());
        if (repl) {
            delete type;
            type = repl;
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

LgsSymbol* LgsSema::getSymbol(const std::string& name) {
    if (const auto globalSymbol = globals.getSymbol(name)) {
        return globalSymbol;
    }
    if (const auto fileSymbol = file->symbolTable.getSymbol(name)) {
        return fileSymbol;
    }
    if (stack.frames.size() > 0) {
        if (const auto symbol = stack.getSymbolTable().getSymbol(name)) {
            return symbol;
        }
    }
    for (const auto importApp : importApps) {
        if (const auto symbol = importApp->globals.getSymbol(name)) {
            return symbol;
        }
    }
    return nullptr;
}

void LgsSema::addLocalSymbol(const LgsSymbol& newSymbol) {
    auto symbolName = *newSymbol.name;
    const auto symbol = globals.getSymbol(symbolName);
    if (symbol && symbol->isBuiltin) {
        return addError(E10053, *newSymbol.location, {symbolName});
    }
    if (file->symbolTable.getSymbol(symbolName)) {
        return addError(E10011, *newSymbol.location, {symbolName});
    }
    if (globals.getSymbol(symbolName)) {
        return addError(E10011, *newSymbol.location, {symbolName});
    }
    stack.getSymbolTable().addSymbol(newSymbol, &errHandler, file->path);
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

void LgsSema::addError(const LgsBaseMsg& lgsErr, const LgsLocation& location, const std::vector<std::string>& args) {
    errHandler.addError(lgsErr, &location, file->path, args);
}

void LgsSema::addGenericType(LgsType* type) const {
    if (!type->asDArray() && !type->asMap() && !type->asObject()) return;
    if (type->hasTypeParams()) return;
    file->symbolTable.genericTypes.emplace(type->getName(), type);
}

void LgsSema::addRTType(LgsType* type) const {
    if (!type || !errHandler.successful || type->hasTypeParams()) return;
    if (type->rttKind == RTT_UNKNOWN || type->isVoid() || type->asEnumField()) return;
    file->symbolTable.rtTypes.emplace(type->getName(), type);
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
