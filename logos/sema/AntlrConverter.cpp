#include "AntlrConverter.h"

#include "LogosDefinitions.h"
#include "exprs/LogosBinaryExpr.h"
#include "exprs/LogosConstant.h"
#include "exprs/LogosConstructor.h"
#include "exprs/LogosFuncCall.h"
#include "exprs/LogosSelection.h"
#include "files/LogosMainFile.h"
#include "files/LogosObjectFile.h"
#include "funcs/LogosUserFunc.h"
#include "object/LogosObject.h"
#include "stmts/LogosIfStmt.h"
#include "stmts/LogosReturnStmt.h"

#include <exprs/LogosVariableExpr.h>

LogosFile* AntlerConverter::getLogosFile(LogosParser::LogosFileContext* ctx, const filesystem::path& filePath) {
    LogosFile* logosFile = nullptr;
    if (const auto mainFileCtx = ctx->mainFile()) {
        logosFile = getMainFile(mainFileCtx);
    }
    if (const auto objFileCtx = ctx->objectFile()) {
        logosFile = getObjFile(objFileCtx);
    }
    logosFile->path = filePath;
    return logosFile;
}

LogosMainFile* AntlerConverter::getMainFile(LogosParser::MainFileContext* ctx) {
    const auto funcImplementations = ctx->funcImplementation();
    const auto mainFile = new LogosMainFile(filePath);

    for (const auto func : funcImplementations) {
        auto funcName = func->funcSignature()->VARIABLE()->getText();
        if (funcName == LOGOS_MAIN_FUNCTION) {
            const auto mainFunc = new LogosUserFunc(LOGOS_MAIN_FUNCTION, &LOGOS_INT);
            mainFile->mainFunc = mainFunc;

            const auto statements = func->funcBody()->statementsBlock()->statement();
            for (const auto statement : statements) {
                auto logosStmt = getStmt(statement);
                mainFunc->stmts.emplace_back(logosStmt);
            }
        } else {
            auto logosFunc = getFunc(func);
            mainFile->funcs.emplace_back(logosFunc);
        }
    }
    return mainFile;
}

LogosObject* AntlerConverter::getObject(LogosParser::ObjectFileContext* ctx) {
    const auto obj = new LogosObject();
    for (const auto varDec : ctx->explicitVarDec()) {
        auto funcName = varDec->VARIABLE()->getText();
        auto logosVarDec = getVarDec(varDec);
        obj->fields.emplace_back(logosVarDec);
    }
    for (const auto func : ctx->funcImplementation()) {
        auto funcName = func->funcSignature()->VARIABLE()->getText();
        auto logosFunc = getFunc(func);
        obj->funcs.emplace_back(logosFunc);
    }
    return obj;
}

LogosObjectFile* AntlerConverter::getObjFile(LogosParser::ObjectFileContext* ctx) {
    const auto objName = ctx->objectDeclaration()->TYPE()->getText();
    const auto objFile = new LogosObjectFile(objName, filePath);
    objFile->obj = getObject(ctx);
    return objFile;
}

LogosFunc *AntlerConverter::getFunc(LogosParser::FuncImplementationContext* ctx) {
    const auto funcSignature = ctx->funcSignature();
    const auto funcName = funcSignature->VARIABLE()->getText();
    const auto& type = getType(funcSignature->TYPE());
    const auto logosUserFunc = new LogosUserFunc(funcName, &type);

    const auto args = funcSignature->variableDefintionList();
    if (args) {
        const auto params = args->explicitVarDec();
        for (const auto param : params) {
            const auto& argType = getType(param->TYPE());
            const auto logosVarDec = new LogosVarDec(param->VARIABLE()->getText(), &argType);
            logosUserFunc->params.push_back(logosVarDec);
        }
    }
    logosUserFunc->stmts = getStmtList(ctx->funcBody()->statementsBlock());
    return logosUserFunc;
}

vector<LogosStmt*> AntlerConverter::getStmtList(LogosParser::StatementsBlockContext* ctx) {
    vector<LogosStmt*> stmts;
    for (const auto statement: ctx->statement()) {
        stmts.push_back(getStmt(statement));
    }
    return stmts;
}

LogosStmt* AntlerConverter::getStmt(LogosParser::StatementContext* ctx) {
    if (const auto implicitVarDec = ctx->implicitVarDec()) {
        return getVarDec(implicitVarDec);
    }
    if (const auto explicitVarDec = ctx->explicitVarDec()) {
        return getVarDec(explicitVarDec);
    }
    if (const auto funcCall = ctx->funcCall()) {
        return getFuncCallExpr(funcCall);
    }
    if (const auto ifStmt = ctx->ifStatement()) {
        return getIfStatement(ifStmt);
    }
    if (const auto returnStmt = ctx->returnStatement()) {
        return new LogosReturnStmt(getExpr(returnStmt->expr()));
    }
    return nullptr;
}

LogosVarDec* AntlerConverter::getVarDec(LogosParser::ImplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto logosExpr = getExpr(ctx->expr());
    const auto logosVarDec = new LogosVarDec(variableName, logosExpr);
    logosVarDec->setPosition(ctx->start, filePath);
    return logosVarDec;
}

LogosVarDec* AntlerConverter::getVarDec(LogosParser::ExplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto logosExpr = getExpr(ctx->expr());
    const auto logosVarDec = new LogosVarDec(variableName, logosExpr);
    logosVarDec->setPosition(ctx->start, filePath);
    return logosVarDec;
}

LogosIfStmt* AntlerConverter::getIfStatement(LogosParser::IfStatementContext* ctx) {
    const auto expr = getExpr(ctx->expr());
    const auto stmts = getStmtList(ctx->statementsBlock());
    const auto ifStmt = new LogosIfStmt(expr, stmts);
    ifStmt->setPosition(ctx->start, filePath);
    return ifStmt;
}

LogosExpr* AntlerConverter::getExpr(LogosParser::ExprContext* ctx) {
    if (!ctx) return nullptr;
    if (const auto unary = ctx->unaryExpr()) {
        return getUnaryExpr(unary);
    }
    if (const auto selection = ctx->selection()) {
        return resolveSelection(selection);
    }
    const auto l = getExpr(ctx->left);
    const auto r = getExpr(ctx->right);
    const auto logosBinaryExpr = new LogosBinaryExpr(l->type, l, r, mapOperator(ctx));
    logosBinaryExpr->setPosition(ctx->start, filePath);
    return logosBinaryExpr;
}

LogosUnaryExpr* AntlerConverter::getUnaryExpr(LogosParser::UnaryExprContext* ctx) {
    if (const auto constant = ctx->constant()) {
        return getConstantExpr(constant);
    }

    if (const auto variable = ctx->VARIABLE()) {
        const auto logosVariable = new LogosVariable(variable->getText());
        logosVariable->setPosition(ctx->start, filePath);
        return logosVariable;
    }

    if (const auto funcCall = ctx->constructorCall()) {
        return getConstructorCallExpr(funcCall);
    }

    if (const auto funcCall = ctx->funcCall()) {
        return getFuncCallExpr(funcCall);
    }

    return nullptr;
}

LogosSelection* AntlerConverter::resolveSelection(LogosParser::SelectionContext* selection) {
    vector<LogosUnaryExpr*> exprs;
    for (const auto unaryExpr : selection->unaryExpr()) {
        auto logosUnaryExpr = getUnaryExpr(unaryExpr);
        exprs.emplace_back(logosUnaryExpr);
    }
    return new LogosSelection(exprs);
}

LogosConstructor* AntlerConverter::getConstructorCallExpr(LogosParser::ConstructorCallContext* ctx) {
    const auto name = ctx->TYPE()->getText();
    const auto constructorExpr = new LogosConstructor(name);
    constructorExpr->setPosition(ctx->start, filePath);
    const auto args = ctx->funcArgList();
    if (!args) {
        return constructorExpr;
    }
    for (const auto arg : args->funcArg()) {
        auto argExpr = getExpr(arg->expr());
        constructorExpr->args.push_back(argExpr);
    }
    return constructorExpr;
}

LogosFuncCall* AntlerConverter::getFuncCallExpr(LogosParser::FuncCallContext* ctx) {
    const auto name = ctx->VARIABLE()->getText();
    const auto funcCallExpr = new LogosFuncCall(name);
    funcCallExpr->setPosition(ctx->start, filePath);
    const auto args = ctx->funcArgList()->funcArg();
    for (const auto arg : args) {
        auto argExpr = getExpr(arg->expr());
        funcCallExpr->args.push_back(argExpr);
    }
    return funcCallExpr;
}

LogosUnaryExpr* AntlerConverter::getConstantExpr(LogosParser::ConstantContext* ctx) {
    if (const auto intToken = ctx->INTEGER()) {
        const auto value = stoi(intToken->getText());
        return new LogosConstant(&LOGOS_INT, value);
    }
    return nullptr;
}

const LogosType& AntlerConverter::getType(antlr4::tree::TerminalNode* type) {
    if (!type) return LOGOS_VOID;
    if (type->getText() == LogosInt::name) return LOGOS_INT;
    return LOGOS_VOID;
}
