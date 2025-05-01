#include "analysis/AntlrConverter.h"

#include "LgsAppFile.h"
#include "LgsEnvFile.h"
#include "LgsGlobals.h"
#include "LgsInterfaceFile.h"
#include "exprs/LgsCast.h"
#include "exprs/LgsNull.h"
#include "exprs/binary/LgsBinaryExpr.h"
#include "exprs/binary/LgsOperator.h"
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/unary/constants/LgsCharConst.h"
#include "exprs/unary/constants/LgsConstExpr.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsSelection.h"
#include <exprs/unary/LgsArray.h>
#include <exprs/unary/LgsArrayIndex.h>
#include <exprs/unary/LgsFuncCall.h>
#include <exprs/unary/LgsVariable.h>
#include "funcs/LgsParam.h"
#include "stmts/LgsField.h"
#include "stmts/LgsReturn.h"
#include "types/LgsBool.h"
#include "types/LgsFloat.h"
#include "exprs/unary/constants/LgsTypeConst.h"
#include "stmts/LgsBreakStmt.h"
#include "stmts/LgsContinue.h"
#include "types/LgsEnum.h"
#include "exprs/unary/LgsEnumField.h"
#include "stmts/LgsPatternMatch.h"

#include <loops/LgsForeachLoop.h>
#include <loops/LgsRangeLoop.h>
#include <types/LgsStr.h>
#include <types/LgsVoid.h>
#include <types/LgsArrayType.h>

LgsFile* AntlerConverter::getLogosFile(LogosParser::LogosFileContext* ctx, const path& filePath) {
    LgsFile* logosFile = nullptr;
    if (const auto mainFileCtx = ctx->mainFile()) {
        logosFile = getMainFile(mainFileCtx, filePath);
    }
    if (const auto objFileCtx = ctx->objectFile()) {
        logosFile = getObjectFile(objFileCtx, filePath);
    }
    if (const auto interfaceFileCtx = ctx->interfaceFile()) {
        logosFile = getInterfaceFile(interfaceFileCtx, filePath);
    }
    logosFile->absPath = filePath;
    return logosFile;
}

LgsMainFile* AntlerConverter::getMainFile(LogosParser::MainFileContext* ctx, const string& filePath) {
    const auto funcImplementations = ctx->funcImplementation();
    const auto mainFile = new LgsMainFile(filePath);

    for (const auto& lgsEnum : ctx->enumDeclaration()) {
        mainFile->enums.emplace_back(getEnum(lgsEnum));
    }

    for (const auto& object : ctx->object()) {
        auto lgsObject = getObject(object->objectBody(), object->TYPE()->getText(), filePath, !!object->SINGLETON());
        mainFile->objects.emplace_back(lgsObject);
    }

    for (const auto& interface : ctx->interface()) {
        auto lgsInterface = getInterface(interface->interfaceBody(), interface->TYPE()->getText(), filePath);
        mainFile->interfaces.emplace_back(lgsInterface);
    }

    for (const auto& func : funcImplementations) {
        auto funcName = func->funcSignature()->VARIABLE()->getText();
        if (funcName == LOGOS_MAIN_FUNC) {
            const auto mainFunc = new LgsFuncImpl(LOGOS_MAIN_FUNC, new LgsInt());
            mainFile->mainFunc = mainFunc;
            const auto statementsBlock = func->funcBody()->statementsBlock();
            mainFunc->stmtBlock = getStmtBlock(statementsBlock);
        } else {
            auto logosFunc = getFuncImpl(func);
            mainFile->funcs.emplace_back(logosFunc);
        }
    }
    return mainFile;
}

LgsEnvFile* AntlerConverter::getEnvFile(LogosParser::LogosEnvFileContext* ctx, const path& filePath) {
    vector<LgsVarDec*> varDecs;
    for (const auto& explicitVarDec : ctx->explicitVarDec()) {
        varDecs.emplace_back(getExplicitVarDec(explicitVarDec));
    }
    for (const auto& implicitVarDec : ctx->implicitVarDec()) {
        varDecs.emplace_back(getImplicitVarDec(implicitVarDec));
    }
    return new LgsEnvFile(filePath, varDecs);
}

LgsObjectFile* AntlerConverter::getObjectFile(LogosParser::ObjectFileContext* ctx, const string& filePath) {
    const auto objName = ctx->objectDeclaration()->TYPE()->getText();
    const auto objFile = new LgsObjectFile(objName, filePath);
    objFile->obj = getObject(ctx->objectBody(), objName, filePath, !!ctx->objectDeclaration()->SINGLETON());
    return objFile;
}

LgsFile* AntlerConverter::getInterfaceFile(LogosParser::InterfaceFileContext* ctx, const path& filePath) {
    const auto interfaceName = ctx->interfaceDeclaration()->TYPE()->getText();
    const auto interfaceFile = new LgsInterfaceFile(interfaceName, filePath);
    interfaceFile->interface = getInterface(ctx->interfaceBody(), interfaceName, interfaceName);
    return interfaceFile;
}

LgsAppFile* AntlerConverter::getAppFile(LogosParser::LogosAppFileContext* ctx, const path& filePath) {
    vector<LgsVarDec*> varDecs;
    for (const auto& explicitVarDec : ctx->explicitVarDec()) {
        varDecs.emplace_back(getExplicitVarDec(explicitVarDec));
    }
    for (const auto& implicitVarDec : ctx->implicitVarDec()) {
        varDecs.emplace_back(getImplicitVarDec(implicitVarDec));
    }
    const auto appFile = new LgsAppFile(filePath, varDecs);
    const auto requireEnvs = ctx->requireEnvVars();
    if (!requireEnvs) return appFile;

    vector<RequireEnvVar> requireEnvVars;
    for (int i = 0; i < requireEnvs->type().size(); ++i) {
        const auto name = requireEnvs->VARIABLE()[i]->getText();
        const auto type = getType(requireEnvs->type()[i]);
        const RequireEnvVar requireEnvVar{.name = name, .type = type};
        requireEnvVars.emplace_back(requireEnvVar);
    }
    appFile->requireEnvVars = requireEnvVars;
    return appFile;
}

LgsObject* AntlerConverter::getObject(LogosParser::ObjectBodyContext* ctx, const string& objName, const string& filePath, const bool isSingleton) {
    const auto obj = new LgsObject(objName, filePath);
    obj->setLocation(ctx->start);
    obj->isSingleton = isSingleton;
    for (const auto& field : ctx->field()) {
        const auto lgsField = getField(field);
        obj->fields[lgsField->name] = lgsField;
    }
    for (const auto& func : ctx->methodImplementation()) {
        auto funcName = func->funcSignature()->VARIABLE()->getText();
        const auto method = getMethodImpl(func, obj);
        obj->addMethod(method);
    }
    if (ctx->objectImplements()) {
        for (const auto& type : ctx->objectImplements()->TYPE()) {
            auto implementType = getTypeFromText(type->getText(), ctx);
            obj->implements.emplace_back(implementType);
        }
    }
    if (!globals.addSymbol(obj->name, LgsSymbol(obj))) {
        handleError(E10031, &obj->location, {obj->name});
    }
    return obj;
}

LgsInterface* AntlerConverter::getInterface(LogosParser::InterfaceBodyContext* ctx, const string& interfaceName, const string& filePath) {
    const auto interface = new LgsInterface(interfaceName);
    interface->setLocation(ctx->start);
    for (const auto& funcSignature : ctx->funcSignature()) {
        const auto self = LgsParam(LOGOS_SELF, interface);
        vector params = {self};
        setParams(funcSignature, params);
        const auto type = getFuncType(funcSignature);
        const auto method = new LgsMethodImpl(funcSignature->VARIABLE()->getText(), type, interfaceName, params);
        method->signature.path = filePath;
        interface->addMethod(method);
    }
    globals.addSymbol(interface->name, LgsSymbol(interface));
    return interface;
}

LgsFuncImpl* AntlerConverter::getFuncImpl(LogosParser::FuncImplementationContext* ctx) {
    const auto rt = getFuncType(ctx->funcSignature());
    const auto funcSignature = ctx->funcSignature();
    const auto name = funcSignature->VARIABLE()->getText();
    vector<LgsParam> params;
    setParams(funcSignature, params);
    const auto func = new LgsFuncImpl(name, rt, params);
    func->stmtBlock = getStmtBlock(ctx->funcBody()->statementsBlock());
    func->setLocation(ctx->start);
    globals.addFunc(func);
    return func;
}

LgsMethodImpl* AntlerConverter::getMethodImpl(LogosParser::MethodImplementationContext* ctx, LgsObject* obj) {
    const auto rt = getFuncType(ctx->funcSignature());
    const auto funcSignature = ctx->funcSignature();
    const auto name = funcSignature->VARIABLE()->getText();
    const auto self = LgsParam(LOGOS_SELF, obj, new LgsInstance(obj));
    vector params = {self};
    setParams(funcSignature, params);
    const auto method = new LgsMethodImpl(name, rt, obj->name, params);
    method->signature.path = obj->path;
    if (ctx->VISIBILITY()) {
        method->isPublic = true;
    }
    method->stmtBlock = getStmtBlock(ctx->funcBody()->statementsBlock());
    method->setLocation(ctx->start);
    return method;
}

void AntlerConverter::setParams(LogosParser::FuncSignatureContext* funcSignature, vector<LgsParam>& params) {
    if (!funcSignature->paramList()) return;
    for (const auto& param : funcSignature->paramList()->param()) {
        if (const auto varDec = param->explicitVarDec()) {
            const auto lgsParam = getParam(varDec);
            params.emplace_back(*lgsParam);
        } else if (const auto func = param->funcSignature()) {
            const auto lgsParam = getParamFunc(func);
            params.emplace_back(*lgsParam);
        }
    }
}

LgsField* AntlerConverter::getField(LogosParser::FieldContext* ctx) {
    const auto name = ctx->VARIABLE()->getText();
    const auto type = getType(ctx->type());
    const auto expr = getExpr(ctx->expr());
    const auto field = new LgsField(name, type, expr);
    if (ctx->VISIBILITY()) {
        field->isPublic = true;
    }
    if (ctx->CONST()) {
        field->isConst = true;
    }
    field->setLocation(ctx->start);
    return field;
}

LgsStmtBlock* AntlerConverter::getStmtBlock(LogosParser::StatementsBlockContext* ctx) {
    const auto stmtBlock = new LgsStmtBlock();
    if (!ctx) return stmtBlock;
    for (const auto& statement : ctx->statement()) {
        auto stmt = getStmt(statement);
        stmtBlock->stmts.emplace_back(stmt);
    }
    return stmtBlock;
}

LgsStmt* AntlerConverter::getStmt(LogosParser::StatementContext* ctx) {
    if (const auto fieldDef = ctx->assignment()) return getAssignment(fieldDef);
    if (const auto implicitVarDec = ctx->implicitVarDec()) return getImplicitVarDec(implicitVarDec);
    if (const auto explicitVarDec = ctx->explicitVarDec()) return getExplicitVarDec(explicitVarDec);
    if (const auto ifStmt = ctx->ifStatement()) return getIfStatement(ifStmt);
    if (const auto patternMatching = ctx->patternMatching()) return getPatternMatching(patternMatching);
    if (const auto loopStmt = ctx->loopStatement()) return getLoopStatement(loopStmt);
    if (const auto funcCall = ctx->funcCall()) return getFuncCall(funcCall);
    if (const auto selection = ctx->selection()) return getSelection(selection);
    if (const auto returnStmt = ctx->returnStatement()) return getReturnStmt(returnStmt);
    if (ctx->breakStmt()) return new LgsBreakStmt();
    if (ctx->CONTINUE()) return new LgsContinue();
    return nullptr;
}


LgsAssignment* AntlerConverter::getAssignment(LogosParser::AssignmentContext* ctx) {
    const auto assignment = new LgsAssignment();
    assignment->rvalue = getExpr(ctx->expr());

    if (const auto variable = ctx->VARIABLE()) {
        assignment->lvalue = getVariable(variable->getText(), ctx);
    } else if (const auto arrayIndex = ctx->arrayIndex()) {
        assignment->lvalue = getArrayIndex(arrayIndex);
    } else if (const auto selection = ctx->selection()) {
        assignment->lvalue = getSelection(selection);
    }

    assignment->setLocation(ctx->start);
    return assignment;
}

LgsVarDec* AntlerConverter::getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto expr = getExpr(ctx->expr(), !!ctx->QUEST_MARK());
    const auto varDec = new LgsVarDec(variableName, expr->type, expr);
    varDec->setLocation(ctx->start);
    return varDec;
}

LgsVarDec* AntlerConverter::getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto expr = getExpr(ctx->expr());
    const auto varDec = new LgsVarDec(variableName, expr);
    varDec->type = getType(ctx->type());
    varDec->setLocation(ctx->start);
    return varDec;
}

LgsStmt* AntlerConverter::getReturnStmt(LogosParser::ReturnStatementContext* ctx) {
    const auto rs = new LgsReturn(getExpr(ctx->expr()));
    rs->setLocation(ctx->start);
    return rs;
}

LgsParam* AntlerConverter::getParam(LogosParser::ExplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto type = getType(ctx->type());
    const auto expr = getExpr(ctx->expr());
    const auto param = new LgsParam(variableName, type, expr);
    param->setLocation(ctx->start);
    return param;
}

LgsParam* AntlerConverter::getParamFunc(LogosParser::FuncSignatureContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto type = getType(ctx->type());
    vector<LgsParam> params;
    setParams(ctx, params);
    const auto func = new LgsFuncImpl(variableName, type, params);
    func->signature.isCallback = true;
    const auto param = new LgsParam(func);
    param->setLocation(ctx->start);
    return param;
}

LgsIfStmt* AntlerConverter::getIfStatement(LogosParser::IfStatementContext* ctx) {
    const auto expr = getExpr(ctx->expr());
    const auto stmts = getStmtBlock(ctx->statementsBlock());
    const auto ifStmt = new LgsIfStmt(expr, stmts);
    for (const auto &elseIfStmt : ctx->elseIfStatement()) {
        auto elseIfExpr = getExpr(elseIfStmt->expr());
        auto elseIfStmtBlock = getStmtBlock(elseIfStmt->statementsBlock());
        ifStmt->elseIfConds.emplace_back(elseIfExpr);
        ifStmt->elseIfStmtBlocks.emplace_back(elseIfStmtBlock);
    }
    if (const auto &elseStmt = ctx->elseStatement()) {
        ifStmt->elseStmtBlock = getStmtBlock(elseStmt->statementsBlock());
    }
    ifStmt->setLocation(ctx->start);
    return ifStmt;
}

LgsStmt* AntlerConverter::getPatternMatching(LogosParser::PatternMatchingContext* ctx) {
    const auto patternMatching = new LgsPatternMatch(getExpr(ctx->expr()));
    for (const auto& pattern : ctx->pattern()) {
        const auto expr = getExpr(pattern->expr());
        const auto stmtBlock = getStmtBlock(pattern->statementsBlock());
        patternMatching->patterns.emplace_back(expr);
        patternMatching->patternsStmtBlocks.emplace_back(stmtBlock);
    }
    patternMatching->elseStmtBlock = getStmtBlock(ctx->statementsBlock());
    return patternMatching;
}

LgsLoop* AntlerConverter::getLoopStatement(LogosParser::LoopStatementContext* ctx) {
    const auto stmts = getStmtBlock(ctx->statementsBlock());
    LgsLoop* loopStmt = nullptr;
    const auto loopVarName = ctx->VARIABLE()[0]->getText();
    if (const auto iterable = ctx->iterableExpr) {
        const auto loopVar = new LgsVarDec(loopVarName);
        loopStmt = new LgsForeachLoop({loopVar}, getUnaryExpr(iterable), stmts);
    } else if (const auto range = ctx->iterableRange) {
        const auto startExpr = getExpr(range->start);
        const auto loopVar = new LgsVarDec(loopVarName, startExpr);
        loopVar->type = startExpr->type;
        loopStmt = new LgsRangeLoop({loopVar}, startExpr, getExpr(range->end), stmts);
    } else {
        assert(false && "No loop statements found");
    }

    loopStmt->setLocation(ctx->start);
    return loopStmt;
}

LgsEnum* AntlerConverter::getEnum(LogosParser::EnumDeclarationContext* ctx) {
    const auto lgsEnum = new LgsEnum(ctx->TYPE()->getText());
    lgsEnum->setLocation(ctx->start);
    unordered_set<string> seenNames;
    for (size_t i = 0; i < ctx->enumField().size(); ++i) {
        const auto enumField = ctx->enumField()[i];
        const auto enumName = enumField->CONST_NAME()->getText();
        if (!seenNames.insert(enumName).second) {
            handleError(E10011, &lgsEnum->location, {enumName, to_string(lgsEnum->location.lineNumber)});
            break;
        }
        string enumText = "";
        if (enumField->STRING()) {
            enumText = enumField->STRING()->getText();
            LgsStr::cleanStr(enumText);
        }
        const auto field = new LgsEnumField(lgsEnum, enumName, enumText);
        field->type = lgsEnum;
        field->setLocation(ctx->start);
        lgsEnum->fields[enumName] = field;
    }
    globals.addEnum(lgsEnum);
    return lgsEnum;
}

LgsExpr* AntlerConverter::getExpr(LogosParser::ExprContext* ctx, const bool isNullable) {
    if (!ctx) return nullptr;
    LgsExpr* expr = nullptr;
    if (ctx->cast) {
        expr = getCast(ctx);
    } else if (ctx->LPAREN() && ctx->RPAREN()) {
        expr = getExpr(ctx->left);
    }  else if (const auto unary = ctx->unaryExpr()) {
        expr = getUnaryExpr(unary);
    } else if (ctx->right){
        expr = getBinaryExpr(ctx);
    }
    if (isNullable) {
        expr->type->nullable = true;
    }
    return expr;
}

LgsExpr* AntlerConverter::getCast(LogosParser::ExprContext* ctx) {
    LgsExpr* castFromValue;
    if (const auto unary = ctx->unaryExpr()) {
        castFromValue = getUnaryExpr(unary);
    } else {
        castFromValue = getBinaryExpr(ctx);
    }
    LgsType* castToType = getType(ctx->cast);
    return new LgsCast(castToType, castFromValue);
}

LgsUnaryExpr* AntlerConverter::getUnaryExpr(LogosParser::UnaryExprContext* ctx) {
    if (const auto variable = ctx->VARIABLE()) return getVariable(variable->getText(), ctx);
    if (const auto constExpr = ctx->CONST_NAME()) return getConst(constExpr->getText(), ctx);
    if (const auto funcCall = ctx->funcCall()) return getFuncCall(funcCall);
    if (const auto vector = ctx->vector()) return getVector(vector);
    if (const auto constructor = ctx->constructor()) return getInstance(constructor);
    if (const auto constant = ctx->constant()) return getConstant(constant);
    if (const auto array = ctx->array()) return getArray(array);
    if (const auto arrayIndex = ctx->arrayIndex()) return getArrayIndex(arrayIndex);
    if (const auto selection = ctx->selection()) return getSelection(selection);
    if (ctx->NULL_()) return new LgsNull();
    assert(false);
}

LgsExpr* AntlerConverter::getBinaryExpr(LogosParser::ExprContext* ctx) {
    const auto l = getExpr(ctx->left);
    const auto r = getExpr(ctx->right);
    const auto logosBinaryExpr = new LgsBinaryExpr(l->type, l, r, mapOperator(ctx));
    logosBinaryExpr->setLocation(ctx->start);
    return logosBinaryExpr;
}

LgsUnaryExpr* AntlerConverter::getArray(LogosParser::ArrayContext* ctx) {
    vector<LgsExpr*> initialElements;
    for (const auto& expr : ctx->expr()) {
        initialElements.emplace_back(getExpr(expr));
    }
    const auto array = new LgsArray(new LgsArrayType(), initialElements);
    array->setLocation(ctx->start);
    return array;
}

LgsVariable* AntlerConverter::getVariable(const string& varName, const antlr4::ParserRuleContext* ctx) const {
    const auto variable = new LgsVariable(varName);
    variable->setLocation(ctx->start);
    return variable;
}

LgsUnaryExpr* AntlerConverter::getConst(const string& constName, const antlr4::ParserRuleContext* ctx) const {
    const auto constVariable = new LgsConst(constName);
    constVariable->setLocation(ctx->start);
    return constVariable;
}

LgsFuncCall* AntlerConverter::getFuncCall(LogosParser::FuncCallContext* ctx) {
    const auto name = ctx->VARIABLE()->getText();
    vector<LgsExpr*> args;
    if (ctx->funcArgList()) {
        for (const auto& arg : ctx->funcArgList()->funcArg()) {
            auto argExpr = getExpr(arg->expr());
            args.emplace_back(argExpr);
        }
    }
    const auto funcCall = new LgsFuncCall(name, args);
    funcCall->setLocation(ctx->start);
    return funcCall;
}

LgsUnaryExpr* AntlerConverter::getVector(LogosParser::VectorContext* vector) {
    if (vector->VEC2()) {

    } else if (vector->VEC3()) {

    } else if (vector->VEC4()) {

    }
    assert(false);
}

LgsSelection* AntlerConverter::getSelection(LogosParser::SelectionContext* ctx) {
    const auto exprs = getSelectionInnerExprs(ctx);
    const auto selection = new LgsSelection(exprs);
    selection->setLocation(ctx->start);
    return selection;
}

LgsUnaryExpr* AntlerConverter::getFirstSelection(LogosParser::SelectionContext* ctx) {
    const auto firstExpr = ctx->firstSelectionElement();
    if (const auto variable = firstExpr->VARIABLE()) {
        return getVariable(variable->getText(), ctx);
    }
    if (const auto selfInstance = firstExpr->SELF_INSTANCE()) {
        return getVariable(selfInstance->getText(), ctx);
    }
    if (const auto funcCall = firstExpr->funcCall()) {
        return getFuncCall(funcCall);
    }
    if (const auto arrayIndex = firstExpr->arrayIndex()) {
        return getArrayIndex(arrayIndex);
    }
    if (const auto type = firstExpr->TYPE()) {
        return getTypeConstant(type, ctx);
    }
    if (const auto selfClass = firstExpr->SELF_CLASS()) {
        return getTypeConstant(selfClass, ctx);
    }
    return nullptr;
}

vector<LgsUnaryExpr*> AntlerConverter::getSelectionInnerExprs(LogosParser::SelectionContext* ctx) {
    vector exprs = {getFirstSelection(ctx)};
    const auto innerSelections = ctx->innerSelectionElement();
    exprs.reserve(innerSelections.size());
    for (int i = 0; i < innerSelections.size(); ++i) {
        const auto& currentExpr = innerSelections[i];
        if (const auto field = currentExpr->VARIABLE()) {
            const auto logosField = getVariable(field->getText(), currentExpr);
            exprs.emplace_back(logosField);
        } else if (const auto funcCall = currentExpr->funcCall()) {
            const auto logosMethodCall = getFuncCall(funcCall);
            // First inner expr takes firstExpr as parent
            const auto prevExpr = i == 0 ? exprs[0] : exprs[i - 1];
            logosMethodCall->args.insert(logosMethodCall->args.begin(), prevExpr);
            exprs.emplace_back(logosMethodCall);
        } else if (const auto arrayIndex = currentExpr->arrayIndex()) {
            const auto logosArrayIndex = getArrayIndex(arrayIndex);
            exprs.emplace_back(logosArrayIndex);
        }
    }
    return exprs;
}

LgsInstance* AntlerConverter::getInstance(LogosParser::ConstructorContext* ctx) {
    const auto type = getTypeFromText(ctx->TYPE()->getText(), ctx);
    type->setLocation(ctx->start);
    const auto instance = new LgsInstance(type);
    instance->setLocation(ctx->start);
    const auto args = ctx->constructorArgList();
    if (!args) return instance;
    for (const auto& arg : args->constructorArg()) {
        const auto argExpr = getExpr(arg->expr());
        auto varDec = new LgsVarDec(arg->VARIABLE()->getText(), argExpr);
        varDec->setLocation(arg->start);
        instance->args.emplace_back(varDec);
    }
    return instance;
}

LgsArrayIndex* AntlerConverter::getArrayIndex(LogosParser::ArrayIndexContext* ctx) {
    LgsUnaryExpr* baseExpr;
    if (const auto variable = ctx->VARIABLE()) {
        baseExpr = getVariable(variable->getText(), ctx);
    } else if (const auto funcCall = ctx->funcCall()) {
        baseExpr = getFuncCall(funcCall);
    } else {
        assert(false && "not implemented");
    }

    auto arrayIndex = new LgsArrayIndex(baseExpr, getExpr(ctx->expr()[0]));
    arrayIndex->setLocation(ctx->start);
    for (int i = 0; i < ctx->expr().size(); ++i) {
        const auto expr = ctx->expr()[i];
        arrayIndex = new LgsArrayIndex(arrayIndex, getExpr(expr));
        arrayIndex->setLocation(expr->start);
    }

    return arrayIndex;
}

LgsConstExpr* AntlerConverter::getConstant(LogosParser::ConstantContext* ctx) const {
    LgsConstExpr* constant = nullptr;
    if (const auto intToken = ctx->INTEGER()) {
        const auto value = stoi(intToken->getText());
        constant = new LgsIntConst(value);
    } else if (const auto floatToken = ctx->FLOAT()) {
        const auto value = stof(floatToken->getText());
        constant = new LgsFloatConst(value);
    } else if (const auto boolToken = ctx->BOOL()) {
        const auto value = boolToken->getText() == "true";
        constant = new LgsBoolConst(value);
    } else if (const auto stringToken = ctx->STRING()) {
        auto value = stringToken->getText();
        LgsStr::cleanStr(value);
        if (value.size() == 1) {
            constant = new LgsCharConst(value[0]);
        } else {
            constant = new LgsStrConst(value);
        }
    }
    constant->setLocation(ctx->start);
    return constant;
}

LgsTypeConst* AntlerConverter::getTypeConstant(antlr4::tree::TerminalNode* type, const LogosParser::SelectionContext* ctx) const {
    const auto typeConst = new LgsTypeConst(getTypeFromText(type->getText(), ctx));
    typeConst->setLocation(ctx->start);
    return typeConst;
}

LgsType* AntlerConverter::getType(LogosParser::TypeContext* ctx) const {
    if (!ctx) return nullptr;
    const auto typeText = ctx->TYPE()->getText();
    LgsType* result = nullptr;
    if (ctx->LBRACK().size() > 0) {
        result = new LgsArrayType(getTypeFromText(typeText, ctx));
        result->setLocation(ctx->start);
    } else {
        result = getTypeFromText(typeText, ctx);
        if (ctx->QUEST_MARK()) {
            result->nullable = true;
        }
    }
    return result;
}

LgsType* AntlerConverter::getTypeFromText(const string& typeText, const antlr4::ParserRuleContext* ctx) const {
    LgsType* type = nullptr;
    if (typeText == LgsInt::name) {
        type = new LgsInt();
    } else if (typeText == LgsFloat::name) {
        type = new LgsFloat();
    } else if (typeText == LgsBool::name) {
        type = new LgsBool();
    } else if (typeText == LgsStr::name) {
        type = new LgsStr();
    } else if (typeText == LgsVoid::name) {
        type = new LgsVoid();
    } else {
        type = new LgsUnknownType(typeText);
    }
    type->setLocation(ctx->start);
    return type;
}

LgsType* AntlerConverter::getFuncType(LogosParser::FuncSignatureContext* ctx) const {
    LgsType* result = nullptr;
    if (ctx->type()) {
        result = getType(ctx->type());
    } else {
        result = new LgsVoid();
    }
    result->setLocation(ctx->start);
    return result;
}
