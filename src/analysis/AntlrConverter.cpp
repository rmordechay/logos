#include "analysis/AntlrConverter.h"

#include "LgsGlobals.h"
#include "exprs/LgsNull.h"
#include "exprs/binary/LgsBinaryExpr.h"
#include "exprs/binary/LgsOperator.h"
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/unary/constants/LgsCharConst.h"
#include "exprs/unary/constants/LgsConst.h"
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
#include "stmts/LgsEnum.h"
#include "stmts/LgsPatternMatching.h"

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
    logosFile->absPath = filePath;
    return logosFile;
}

LgsMainFile* AntlerConverter::getMainFile(LogosParser::MainFileContext* ctx, const string& filePath) {
    const auto funcImplementations = ctx->funcImplementation();
    const auto mainFile = new LgsMainFile(filePath);
    if (ctx->enumDeclaration()) {
        auto lgsEnum = getEnum(ctx->enumDeclaration());
        mainFile->enums.emplace_back(lgsEnum);
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

LgsObjectFile* AntlerConverter::getObjectFile(LogosParser::ObjectFileContext* ctx, const string& filePath) {
    const auto objName = ctx->objectDeclaration()->TYPE()->getText();
    const auto objFile = new LgsObjectFile(objName, filePath);
    objFile->obj = getObject(ctx);
    return objFile;
}

LgsFuncImpl* AntlerConverter::getFuncImpl(LogosParser::FuncImplementationContext* ctx) {
    const auto rt = getFuncType(ctx);
    const auto signature = ctx->funcSignature();
    const auto name = signature->VARIABLE()->getText();
    vector<LgsParam*> params;
    if (signature->paramList()) {
        for (const auto& varDec : signature->paramList()->explicitVarDec()) {
            auto param = getParam(varDec);
            params.emplace_back(param);
        }
    }
    const auto func = new LgsFuncImpl(name, rt, params);
    func->stmtBlock = getStmtBlock(ctx->funcBody()->statementsBlock());
    func->setLocation(ctx->start);
    return func;
}

LgsObject* AntlerConverter::getObject(LogosParser::ObjectFileContext* ctx) {
    const auto objName = ctx->objectDeclaration()->TYPE()->getText();
    const auto obj = new LgsObject(objName);
    for (int i = 0; i < ctx->explicitVarDec().size(); ++i) {
        const auto varDec = ctx->explicitVarDec()[i];
        const auto field = getField(varDec, i, obj->name);
        obj->fields[field->name] = field;
    }
    for (const auto& func : ctx->funcImplementation()) {
        auto funcName = func->funcSignature()->VARIABLE()->getText();
        const auto method = getMethodImpl(func, obj);
        obj->methods[funcName] = method;
    }
    globals.symbols[obj->name] = LgsSymbol(OBJECT, obj);
    return obj;
}

LgsMethodImpl* AntlerConverter::getMethodImpl(LogosParser::FuncImplementationContext* ctx, const LgsObject* obj) {
    const auto rt = getFuncType(ctx);
    const auto signature = ctx->funcSignature();
    const auto name = signature->VARIABLE()->getText();

    const auto method = new LgsMethodImpl(name, rt, obj->name);
    method->stmtBlock = getStmtBlock(ctx->funcBody()->statementsBlock());
    method->setLocation(ctx->start);

    const auto params = signature->paramList();
    if (!params) return method;

    for (const auto& varDec : params->explicitVarDec()) {
        auto param = getParam(varDec);
        method->params.emplace_back(param);
    }
    return method;
}

LgsField* AntlerConverter::getField(LogosParser::ExplicitVarDecContext* varDec, const size_t position, const string& parentName) {
    const auto name = varDec->VARIABLE()->getText();
    const auto type = getType(varDec->type());
    const auto expr = getExpr(varDec->expr());
    return new LgsField(name, parentName, type, position, expr);
}

LgsStmtBlock* AntlerConverter::getStmtBlock(LogosParser::StatementsBlockContext* ctx) {
    vector<LgsStmt*> stmts;
    for (const auto& statement : ctx->statement()) {
        auto stmt = getStmt(statement);
        stmts.emplace_back(stmt);
    }
    return new LgsStmtBlock(stmts);
}

LgsStmt* AntlerConverter::getStmt(LogosParser::StatementContext* ctx) {
    if (const auto fieldDef = ctx->assignment()) {
        return getAssignment(fieldDef);
    }
    if (const auto implicitVarDec = ctx->implicitVarDec()) {
        return getImplicitVarDec(implicitVarDec);
    }
    if (const auto explicitVarDec = ctx->explicitVarDec()) {
        return getExplicitVarDec(explicitVarDec);
    }
    if (const auto funcCall = ctx->funcCall()) {
        return getFuncCall(funcCall);
    }
    if (const auto ifStmt = ctx->ifStatement()) {
        return getIfStatement(ifStmt);
    }
    if (const auto patternMatching = ctx->patternMatching()) {
        return getPatternMatching(patternMatching);
    }
    if (const auto loopStmt = ctx->loopStatement()) {
        return getLoopStatement(loopStmt);
    }
    if (const auto enumDec = ctx->enumDeclaration()) {
        return getEnum(enumDec);
    }
    if (const auto returnStmt = ctx->returnStatement()) {
        return new LgsReturn(getExpr(returnStmt->expr()));
    }
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
    const auto logosExpr = getExpr(ctx->expr());
    const auto logosVarDec = new LgsVarDec(variableName, nullptr, logosExpr);
    logosVarDec->setLocation(ctx->start);
    return logosVarDec;
}

LgsVarDec* AntlerConverter::getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto userType = getType(ctx->type());
    const auto expr = getExpr(ctx->expr());
    const auto varDec = new LgsVarDec(variableName, userType, expr);
    varDec->setLocation(ctx->start);
    return varDec;
}

LgsParam* AntlerConverter::getParam(LogosParser::ExplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto userType = getType(ctx->type());
    const auto expr = getExpr(ctx->expr());
    const auto param = new LgsParam(variableName, userType, expr);
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
    const auto patternMatching = new LgsPatternMatching(getExpr(ctx->expr()));
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
        const auto loopVar = new LgsVarDec(loopVarName, new LgsInt());
        loopStmt = new LgsRangeLoop({loopVar}, getExpr(range->start), getExpr(range->end), stmts);
    } else {
        assert(false && "No loop statements found");
    }

    loopStmt->setLocation(ctx->start);
    return loopStmt;
}

LgsEnum* AntlerConverter::getEnum(LogosParser::EnumDeclarationContext* ctx) {
    const auto lgsEnum = new LgsEnum();
    for (size_t i = 0; i < ctx->enumField().size(); ++i) {
        const auto enumField = ctx->enumField()[i];
        const auto enumName = enumField->CONST()->getText();
        auto enumText = enumField->STRING()->getText();
        LgsStr::cleanStr(enumText);
        EnumField field(i, enumName, enumText);
        field.setLocation(ctx->start);
        lgsEnum->fields.emplace_back(field);
    }
    lgsEnum->setLocation(ctx->start);
    return lgsEnum;
}

LgsExpr* AntlerConverter::getExpr(LogosParser::ExprContext* ctx) {
    if (!ctx) return nullptr;
    if (const auto unary = ctx->unaryExpr()) {
        return getUnaryExpr(unary);
    }
    return getBinaryExpr(ctx);
}

LgsUnaryExpr* AntlerConverter::getUnaryExpr(LogosParser::UnaryExprContext* ctx) {
    if (const auto variable = ctx->VARIABLE()) return getVariable(variable->getText(), ctx);
    if (const auto funcCall = ctx->funcCall()) return getFuncCall(funcCall);
    if (const auto constructor = ctx->constructor()) return getInstance(constructor);
    if (const auto constant = ctx->constant()) return getConstant(constant);
    if (const auto array = ctx->array()) return getArray(array);
    if (const auto arrayIndex = ctx->arrayIndex()) return getArrayIndex(arrayIndex);
    if (const auto selection = ctx->selection()) return getSelection(selection);
    if (ctx->NULL_()) return new LgsNull();
    return nullptr;
}

LgsExpr* AntlerConverter::getBinaryExpr(LogosParser::ExprContext* ctx) {
    const auto l = getExpr(ctx->left);
    const auto r = getExpr(ctx->right);
    const auto logosBinaryExpr = new LgsBinaryExpr(l->type, l, r, mapOperator(ctx));
    logosBinaryExpr->setLocation(ctx->start);
    return logosBinaryExpr;
}

LgsUnaryExpr* AntlerConverter::getArray(LogosParser::ArrayContext* ctx) {
    const auto array = new LgsArray();
    for (const auto& expr : ctx->expr()) {
        array->elements.emplace_back(getExpr(expr));
    }
    array->type = new LgsArrayType();
    array->setLocation(ctx->start);
    return array;
}

LgsVariable* AntlerConverter::getVariable(const string& varName, const ParserRuleContext* ctx) {
    const auto variable = new LgsVariable(varName);
    variable->setLocation(ctx->start);
    return variable;
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

LgsSelection* AntlerConverter::getSelection(LogosParser::SelectionContext* ctx) {
    vector exprs = {getFirstSelection(ctx)};
    const auto innerExprs = getSelectionInnerExprs(ctx);
    exprs.insert(exprs.end(), innerExprs.begin(), innerExprs.end());
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
    const auto innerSelections = ctx->innerSelectionElement();
    vector<LgsUnaryExpr*> exprs;
    exprs.reserve(innerSelections.size());
    for (int i = 0; i < innerSelections.size(); ++i) {
        const auto& expr = innerSelections[i];
        if (const auto field = expr->VARIABLE()) {
            const auto logosField = getVariable(field->getText(), expr);
            exprs.emplace_back(logosField);
        } else if (const auto funcCall = expr->funcCall()) {
            const auto logosFuncCall = getFuncCall(funcCall);
            exprs.emplace_back(logosFuncCall);
        } else if (const auto arrayIndex = expr->arrayIndex()) {
            const auto logosArrayIndex = getArrayIndex(arrayIndex);
            exprs.emplace_back(logosArrayIndex);
        }
    }
    return exprs;
}

LgsInstance* AntlerConverter::getInstance(LogosParser::ConstructorContext* ctx) {
    const auto name = ctx->TYPE()->getText();
    const auto instance = new LgsInstance(name);
    const auto args = ctx->funcArgList();
    if (!args) {
        return instance;
    }

    for (const auto& arg : args->funcArg()) {
        auto argExpr = getExpr(arg->expr());
        instance->args.emplace_back(argExpr);
    }
    instance->setLocation(ctx->start);
    return instance;
}

LgsArrayIndex* AntlerConverter::getArrayIndex(LogosParser::ArrayIndexContext* ctx) {
    LgsUnaryExpr* baseExpr;
    if (const auto variable = ctx->VARIABLE()) {
        baseExpr = getVariable(variable->getText(), ctx);
    } else {
        baseExpr = getFuncCall(ctx->funcCall());
    }

    vector<LgsExpr*> indexExprs;
    for (const auto& expr : ctx->expr()) {
        indexExprs.emplace_back(getExpr(expr));
    }

    const auto arrayIndex = new LgsArrayIndex(baseExpr, indexExprs);
    arrayIndex->setLocation(ctx->start);
    return arrayIndex;
}

LgsConst* AntlerConverter::getConstant(LogosParser::ConstantContext* ctx) {
    LgsConst* constant = nullptr;
    if (const auto intToken = ctx->INTEGER()) {
        const auto value = stoi(intToken->getText());
        constant = new LgsIntConst(value);
    }
    if (const auto floatToken = ctx->FLOAT()) {
        const auto value = stof(floatToken->getText());
        constant = new LgsFloatConst(value);
    }
    if (const auto boolToken = ctx->BOOL()) {
        const auto value = boolToken->getText() == "true";
        constant = new LgsBoolConst(value);
    }
    if (const auto stringToken = ctx->STRING()) {
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

LgsTypeConst* AntlerConverter::getTypeConstant(tree::TerminalNode* type, const LogosParser::SelectionContext* ctx) {
    const auto typeConst = new LgsTypeConst(getTypeFromText(type->getText()));
    typeConst->setLocation(ctx->start);
    return typeConst;
}

LgsType* AntlerConverter::getType(LogosParser::TypeContext* ctx) {
    if (!ctx) return nullptr;
    const auto typeText = ctx->TYPE()->getText();
    LgsType* result = nullptr;
    if (ctx->LBRACK().size() > 0) {
        result = new LgsArrayType(getTypeFromText(typeText));
    } else {
        result = getTypeFromText(typeText);
        if (ctx->QUEST_MARK()) {
            result->nullable = true;
        }
    }
    return result;
}

LgsType* AntlerConverter::getTypeFromText(const string& typeText) {
    if (typeText == LgsInt::name) return new LgsInt();
    if (typeText == LgsFloat::name) return new LgsFloat();
    if (typeText == LgsBool::name) return new LgsBool();
    if (typeText == LgsStr::name) return new LgsStr();
    return new LgsUnknownType(typeText);
}

LgsType* AntlerConverter::getFuncType(LogosParser::FuncImplementationContext* ctx) {
    const auto signature = ctx->funcSignature();
    if (signature->type()) {
        return getType(signature->type());
    }
    return new LgsVoid();
}