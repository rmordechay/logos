#include "sema/AntlrConverter.h"

#include "binary/LogosBinaryExpr.h"
#include "binary/LogosOperator.h"
#include "unary/LogosMethodCall.h"
#include "unary/constants/LogosConstant.h"
#include "unary/constants/LogosStringConst.h"
#include "unary//LogosInstance.h"
#include "unary//LogosSelection.h"
#include <exprs/unary/LogosArray.h>
#include <exprs/unary/LogosArrayIndex.h>
#include <exprs/unary/LogosFuncCall.h>
#include <exprs/unary/LogosVariable.h>
#include "funcs/LogosParam.h"
#include "loops/LogosLoopVar.h"
#include "object/LogosField.h"
#include "stmts/LogosReturn.h"
#include "types/LogosBool.h"
#include "types/LogosFloat.h"
#include "unary/constants/LogosTypeConst.h"

#include <LogosDefinitions.h>
#include <LogosError.h>
#include <loops/LogosForeachLoop.h>
#include <loops/LogosRangeLoop.h>
#include <types/LogosString.h>
#include <types/LogosVoid.h>

LogosFile* AntlerConverter::getLogosFile(LogosParser::LogosFileContext* ctx, const path& filePath) {
    LogosFile* logosFile = nullptr;
    if (const auto mainFileCtx = ctx->mainFile()) {
        logosFile = getMainFile(mainFileCtx);
    }
    if (const auto objFileCtx = ctx->objectFile()) {
        logosFile = getObjectFile(objFileCtx);
    }
    logosFile->path = filePath;
    return logosFile;
}

LogosMainFile* AntlerConverter::getMainFile(LogosParser::MainFileContext* ctx) {
    const auto funcImplementations = ctx->funcImplementation();
    const auto mainFile = new LogosMainFile(filePath);
    for (const auto& func : funcImplementations) {
        auto funcName = func->funcSignature()->VARIABLE()->getText();
        if (funcName == LOGOS_MAIN_FUNCTION) {
            const auto mainFunc = new LogosFuncImpl(LOGOS_MAIN_FUNCTION, &LOGOS_INT);
            mainFile->mainFunc = mainFunc;
            const auto statementsBlock = func->funcBody()->statementsBlock();
            mainFunc->stmtBlock = getStmtBlock(statementsBlock);
        } else {
            auto logosFunc = getFunc(func);
            mainFile->funcs.emplace_back(logosFunc);
        }
    }
    return mainFile;
}

LogosObjectFile* AntlerConverter::getObjectFile(LogosParser::ObjectFileContext* ctx) {
    const auto objName = ctx->objectDeclaration()->type()->TYPE()->getText();
    const auto objFile = new LogosObjectFile(objName, filePath);
    objFile->obj = getObject(ctx);
    return objFile;
}

LogosObject* AntlerConverter::getObject(LogosParser::ObjectFileContext* ctx) {
    const auto objName = ctx->objectDeclaration()->type()->TYPE()->getText();
    const auto obj = new LogosObject(objName);
    for (int i = 0; i < ctx->explicitVarDec().size(); ++i) {
        const auto varDec = ctx->explicitVarDec()[i];
        const auto field = getField(varDec, objName, i);
        obj->fields[field->name] = field;
    }
    for (const auto& func : ctx->funcImplementation()) {
        auto funcName = func->funcSignature()->VARIABLE()->getText();
        const auto method = getMethod(func, obj);
        obj->methods[funcName] = method;
    }
    return obj;
}

LogosField* AntlerConverter::getField(LogosParser::ExplicitVarDecContext* varDec, const string& parentName, const size_t position) {
    const auto name = varDec->VARIABLE()->getText();
    const auto type = getType(varDec->type()->TYPE());
    const auto expr = getExpr(varDec->expr());
    return new LogosField(name, parentName, type, expr, position);
}

LogosFuncImpl* AntlerConverter::getFunc(LogosParser::FuncImplementationContext* ctx) {
    const auto funcSignature = ctx->funcSignature();
    const auto funcName = funcSignature->VARIABLE()->getText();
    LogosType* type;
    if (funcSignature->type()) {
        type = getType(funcSignature->type()->TYPE());
    } else {
        type = &LOGOS_VOID;
    }
    const auto funcImpl = new LogosFuncImpl(funcName, type);

    const auto params = funcSignature->paramList();
    if (params) {
        for (const auto& varDec : params->explicitVarDec()) {
            auto param = getParam(varDec);
            funcImpl->params.emplace_back(param);
        }
    }
    funcImpl->stmtBlock = getStmtBlock(ctx->funcBody()->statementsBlock());
    return funcImpl;
}

LogosMethodImpl* AntlerConverter::getMethod(LogosParser::FuncImplementationContext* ctx, LogosObject* obj) {
    const auto funcSignature = ctx->funcSignature();
    const auto funcName = funcSignature->VARIABLE()->getText();
    const auto type = getType(funcSignature->type()->TYPE());
    const auto method = new LogosMethodImpl(funcName, type, obj);

    const auto params = funcSignature->paramList();
    if (params) {
        for (const auto& varDec : params->explicitVarDec()) {
            auto param = getParam(varDec);
            method->params.emplace_back(param);
        }
    }

    method->stmtBlock = getStmtBlock(ctx->funcBody()->statementsBlock());
    return method;
}

LogosStmtBlock* AntlerConverter::getStmtBlock(LogosParser::StatementsBlockContext* ctx) {
    vector<LogosStmt*> stmts;
    for (const auto& statement : ctx->statement()) {
        auto stmt = getStmt(statement);
        stmts.emplace_back(stmt);
    }
    return new LogosStmtBlock(stmts);
}

LogosStmt* AntlerConverter::getStmt(LogosParser::StatementContext* ctx) {
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
    if (const auto loopStmt = ctx->loopStatement()) {
        return getLoopStatement(loopStmt);
    }
    if (const auto returnStmt = ctx->returnStatement()) {
        return new LogosReturn(getExpr(returnStmt->expr()));
    }
    return nullptr;
}


LogosAssignment* AntlerConverter::getAssignment(LogosParser::AssignmentContext* ctx) {
    const auto assignment = new LogosAssignment();
    assignment->rvalue = getExpr(ctx->expr());

    if (const auto variable = ctx->VARIABLE()) {
        assignment->lvalue = getVariable(variable->getText(), ctx);
    } else if (const auto arrayIndex = ctx->arrayIndex()) {
        assignment->lvalue = getArrayIndex(arrayIndex);
    } else if (const auto selection = ctx->selection()) {
        assignment->lvalue = getSelection(selection);
    }

    assignment->setPosition(ctx->start);
    return assignment;
}

LogosVarDec* AntlerConverter::getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto logosExpr = getExpr(ctx->expr());
    const auto logosVarDec = new LogosVarDec(variableName, nullptr, logosExpr);
    logosVarDec->setPosition(ctx->start);
    return logosVarDec;
}

LogosVarDec* AntlerConverter::getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto expr = getExpr(ctx->expr());
    const auto userType = getType(ctx->type()->TYPE());
    const auto varDec = new LogosVarDec(variableName, userType, expr);
    varDec->setPosition(ctx->start);
    return varDec;
}

LogosParam* AntlerConverter::getParam(LogosParser::ExplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto expr = getExpr(ctx->expr());
    const auto userType = getType(ctx->type()->TYPE());
    const auto param = new LogosParam(variableName, userType, expr);
    param->setPosition(ctx->start);
    return param;
}

LogosIf* AntlerConverter::getIfStatement(LogosParser::IfStatementContext* ctx) {
    const auto expr = getExpr(ctx->expr());
    const auto stmts = getStmtBlock(ctx->statementsBlock());
    const auto ifStmt = new LogosIf(expr, stmts);
    for (const auto &elseIfStmt : ctx->elseIfStatement()) {
        auto elseIfExpr = getExpr(elseIfStmt->expr());
        auto elseIfStmtBlock = getStmtBlock(elseIfStmt->statementsBlock());
        ifStmt->elseIfConds.emplace_back(elseIfExpr);
        ifStmt->elseIfStmtBlocks.emplace_back(elseIfStmtBlock);
    }
    if (const auto &elseStmt = ctx->elseStatement()) {
        ifStmt->elseStmtBlock = getStmtBlock(elseStmt->statementsBlock());
    }
    ifStmt->setPosition(ctx->start);
    return ifStmt;
}

LogosLoop* AntlerConverter::getLoopStatement(LogosParser::LoopStatementContext* ctx) {
    LogosLoop* loopStmt = nullptr;
    const auto stmts = getStmtBlock(ctx->statementsBlock());
    if (const auto iterableExpr = ctx->iterableExpr) {
        const auto variable = new LogosVariable(ctx->exprList()->expr()[0]->getText());
        const auto loopVar = new LogosLoopVar(variable->name);
        loopVar->element = new LogosArrayIndex(variable, {LOGOS_INT.getZeroValue()});
        loopStmt = new LogosForeachLoop(loopVar, getExpr(iterableExpr), stmts);
    } else if (const auto range = ctx->iterableRange) {
        const auto loopVarName = ctx->VARIABLE()->getText();
        const auto loopVar = new LogosLoopVar(loopVarName, &LOGOS_INT);
        loopStmt = new LogosRangeLoop(loopVar, getExpr(range->start), getExpr(range->end), stmts);
    } else {
        assert(false && "No loop statements found");
    }
    loopStmt->setPosition(ctx->start);
    return loopStmt;
}

LogosExpr* AntlerConverter::getExpr(LogosParser::ExprContext* ctx) {
    if (!ctx) return nullptr;
    if (const auto unary = ctx->unaryExpr()) {
        return getUnaryExpr(unary);
    }
    return getBinaryExpr(ctx);
}

LogosUnaryExpr* AntlerConverter::getUnaryExpr(LogosParser::UnaryExprContext* ctx) {
    if (const auto variable = ctx->VARIABLE()) {
        return getVariable(variable->getText(), ctx);
    }

    if (const auto constant = ctx->constant()) {
        return getConstant(constant);
    }

    if (const auto selection = ctx->selection()) {
        return getSelection(selection);
    }

    if (const auto constructor = ctx->constructor()) {
        return getInstance(constructor);
    }

    if (const auto funcCall = ctx->funcCall()) {
        return getFuncCall(funcCall);
    }

    if (const auto array = ctx->array()) {
        return getArray(array);
    }

    if (const auto arrayIndex = ctx->arrayIndex()) {
        return getArrayIndex(arrayIndex);
    }

    return nullptr;
}

LogosExpr* AntlerConverter::getBinaryExpr(LogosParser::ExprContext* ctx) {
    const auto l = getExpr(ctx->left);
    const auto r = getExpr(ctx->right);
    const auto logosBinaryExpr = new LogosBinaryExpr(l->type, l, r, mapOperator(ctx));
    logosBinaryExpr->setPosition(ctx->start);
    return logosBinaryExpr;
}

LogosUnaryExpr* AntlerConverter::getArray(LogosParser::ArrayContext* ctx) {
    const auto array = new LogosArray();
    for (const auto& expr : ctx->expr()) {
        array->elements.emplace_back(getExpr(expr));
    }
    array->setPosition(ctx->start);
    return array;
}

LogosVariable* AntlerConverter::getVariable(const string& varName, const ParserRuleContext* ctx) {
    const auto logosVariable = new LogosVariable(varName);
    logosVariable->setPosition(ctx->start);
    return logosVariable;
}

LogosFuncCall* AntlerConverter::getFuncCall(LogosParser::FuncCallContext* ctx) {
    const auto name = ctx->VARIABLE()->getText();
    const auto funcCallExpr = new LogosFuncCall(name);
    const auto funcArgList = ctx->funcArgList();
    if (funcArgList) {
        const auto args = funcArgList->funcArg();
        for (const auto& arg : args) {
            auto argExpr = getExpr(arg->expr());
            funcCallExpr->args.emplace_back(argExpr);
        }
    }
    funcCallExpr->setPosition(ctx->start);
    return funcCallExpr;
}

LogosMethodCall* AntlerConverter::getMethodCall(LogosParser::FuncCallContext* ctx) {
    const auto name = ctx->VARIABLE()->getText();
    const auto funcCallExpr = new LogosMethodCall(name);
    funcCallExpr->setPosition(ctx->start);
    const auto funcArgList = ctx->funcArgList();
    if (funcArgList) {
        const auto args = funcArgList->funcArg();
        for (const auto& arg : args) {
            auto argExpr = getExpr(arg->expr());
            funcCallExpr->args.emplace_back(argExpr);
        }
    }
    return funcCallExpr;
}

LogosTypeConst* AntlerConverter::getTypeConstant(tree::TerminalNode* type, const LogosParser::SelectionContext* ctx) {
    const auto typeConst = new LogosTypeConst(getType(type));
    typeConst->setPosition(ctx->start);
    return typeConst;
}

LogosSelection* AntlerConverter::getSelection(LogosParser::SelectionContext* ctx) {
    const auto firstElement = ctx->firstSelectionElement();
    const auto firstExpr = getFirstSelection(ctx, firstElement);
    const auto innerSelections = getInnerSelections(ctx->innerSelectionElement());
    return new LogosSelection(firstExpr, innerSelections);
}

LogosUnaryExpr* AntlerConverter::getFirstSelection(const LogosParser::SelectionContext* ctx, LogosParser::FirstSelectionElementContext* firstExpr) {
    if (const auto variable = firstExpr->VARIABLE()) {
        return getVariable(variable->getText(), ctx);
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
    return nullptr;
}

vector<LogosUnaryExpr*> AntlerConverter::getInnerSelections(const vector<LogosParser::InnerSelectionElementContext*>& ctx) {
    vector<LogosUnaryExpr*> exprs;
    exprs.reserve(ctx.size());
    for (int i = 1; i < ctx.size(); ++i) {
        const auto& expr = ctx[i];
        if (const auto field = expr->VARIABLE()) {
            const auto logosField = getVariable(field->getText(), expr);
            exprs.emplace_back(logosField);
        } else if (const auto methodCall = expr->funcCall()) {
            const auto logosFuncCall = getMethodCall(methodCall);
            exprs.emplace_back(logosFuncCall);
        } else if (const auto arrayIndex = expr->arrayIndex()) {
            const auto logosArrayIndex = getArrayIndex(arrayIndex);
            exprs.emplace_back(logosArrayIndex);
        }
    }
    return exprs;
}

LogosInstance* AntlerConverter::getInstance(LogosParser::ConstructorContext* ctx) {
    const auto name = ctx->type()->TYPE()->getText();
    const auto instance = new LogosInstance(name);
    instance->setPosition(ctx->start);
    const auto args = ctx->funcArgList();
    if (!args) {
        return instance;
    }

    for (const auto& arg : args->funcArg()) {
        auto argExpr = getExpr(arg->expr());
        instance->args.emplace_back(argExpr);
    }
    return instance;
}

LogosArrayIndex* AntlerConverter::getArrayIndex(LogosParser::ArrayIndexContext* ctx) {
    LogosUnaryExpr* baseExpr;
    if (const auto variable = ctx->VARIABLE()) {
        baseExpr = getVariable(variable->getText(), ctx);
    } else {
        baseExpr = getFuncCall(ctx->funcCall());
    }

    vector<LogosExpr*> indexExprs;
    for (const auto& expr : ctx->expr()) {
        indexExprs.emplace_back(getExpr(expr));
    }

    return new LogosArrayIndex(baseExpr, indexExprs);
}


LogosUnaryExpr* AntlerConverter::getConstant(LogosParser::ConstantContext* ctx) {
    if (const auto intToken = ctx->INTEGER()) {
        const auto value = stoi(intToken->getText());
        return new LogosConstant(&LOGOS_INT, value);
    }
    if (const auto intToken = ctx->FLOAT()) {
        const auto value = stof(intToken->getText());
        return new LogosConstant(&LOGOS_FLOAT, value);
    }
    if (const auto intToken = ctx->BOOL()) {
        const auto value = intToken->getText() == "true";
        return new LogosConstant(&LOGOS_BOOL, value);
    }
    if (const auto stringToken = ctx->STRING()) {
        const auto value = stringToken->getText();
        return new LogosConstant(&LOGOS_STRING, new LogosStringConst(value));
    }
    return nullptr;
}

LogosType* AntlerConverter::getType(tree::TerminalNode* type) {
    if (!type) return &LOGOS_VOID;
    const auto typeText = type->getText();
    if (typeText == LOGOS_INT.getName()) return &LOGOS_INT;
    if (typeText == LOGOS_FLOAT.getName()) return &LOGOS_FLOAT;
    if (typeText == LOGOS_BOOL.getName()) return &LOGOS_BOOL;
    if (typeText == LOGOS_STRING.getName()) return &LOGOS_STRING;
    if (typeText == "") return &LOGOS_VOID;
    // TODO memory leak
    return new LogosObject(typeText);
}
