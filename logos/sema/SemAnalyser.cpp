#include "SemAnalyser.h"

#include "Comparison.h"
#include "FuncCall.h"
#include "LogosConfigs.h"
#include "LogosErrors.h"
#include "LogosParser.h"
#include "StoreExpr.h"
#include "exprs/LogosBinaryExpr.h"
#include "exprs/LogosConstantExpr.h"
#include "exprs/LogosFuncCallExpr.h"
#include "exprs/LogosOperator.h"
#include "exprs/LogosVariableExpr.h"
#include "types/LogosBool.h"

void SemAnalyser::analyseProject(const LogosFile* mainFile) {
    visitMainFile(mainFile);
}

void SemAnalyser::visitMainFile(const LogosFile* mainFile) {
    const auto fileCtx = mainFile->fileCtx;
    for (const auto func : fileCtx->mainFile()->funcImplementation()) {
        if (func->funcSignature()->VARIABLE()->getText() == LOGOS_MAIN_FUNCTION) {
            visitFuncImplementation(func);
        }
    }
}

void SemAnalyser::visitFuncImplementation(LogosParser::FuncImplementationContext* ctx) {
    const auto statements = ctx->funcBody()->statementsBlock()->statement();
    for (const auto statement : statements) {
        visitStatement(statement);
    }
}

void SemAnalyser::visitStatement(LogosParser::StatementContext* ctx) {
    if (const auto explicitVarDec = ctx->explicitVarDec()) {
        visitExplicitVarDec(explicitVarDec);
    } else if (const auto implicitVarDec = ctx->implicitVarDec()) {
        visitImplicitVarDec(implicitVarDec);
    } else if (const auto funcCall = ctx->funcCall()) {
        visitFuncCall(funcCall);
    } else if (const auto ifStmt = ctx->ifStatement()) {
        visitIfStatement(ifStmt);
    }
}

void SemAnalyser::visitExplicitVarDec(LogosParser::ExplicitVarDecContext* const ctx) {
    // const auto variableName = ctx->VARIABLE()->getText();
    // const auto logosExpr = getExpr(ctx->expr());
    // addSymbol(variableName, logosExpr);
}

void SemAnalyser::visitImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto logosExpr = getExpr(ctx->expr());
    addSymbol(variableName, logosExpr);
    codeNodes.push_back(new StoreExpr(variableName, logosExpr));
}

void SemAnalyser::visitFuncCall(LogosParser::FuncCallContext* ctx) {
    const auto callExpr = getFuncCallExpr(ctx);
}

void SemAnalyser::visitIfStatement(LogosParser::IfStatementContext* ctx) {
    const auto expr = getExpr(ctx->expr());
    auto statementsContext = ctx->statementsBlock()->statement();
    codeNodes.push_back(new Comparison(expr));
}

LogosExpr* SemAnalyser::getExpr(LogosParser::ExprContext* ctx) {
    if (const auto unary = ctx->unaryExpr()) {
        return getUnaryExpr(unary);
    }
    const auto l = getExpr(ctx->left);
    const auto r = getExpr(ctx->right);
    return new LogosBinaryExpr(l->type, l, r, mapOperator(ctx));
}

LogosUnaryExpr* SemAnalyser::getUnaryExpr(LogosParser::UnaryExprContext* ctx) {
    if (const auto constant = ctx->constant()) {
        return getConstantExpr(constant);
    }

    if (const auto variable = ctx->VARIABLE()) {
        return getVariableExpr(variable->getText());
    }

    if (const auto funcCall = ctx->funcCall()) {
        return getFuncCallExpr(funcCall);
    }
    return nullptr;
}

LogosUnaryExpr* SemAnalyser::getVariableExpr(const string& symbolName) {
    if (const auto resolvedSymbol = resolveSymbol(symbolName)) {
        return new LogosVariableExpr(resolvedSymbol->type, symbolName);
    }
    return nullptr;
}


LogosUnaryExpr* SemAnalyser::getConstantExpr(LogosParser::ConstantContext* ctx) const {
    if (const auto intToken = ctx->INTEGER()) {
        const auto value = stoi(intToken->getText());
        return new LogosConstantExpr(INT_TYPE, value);
    }
    return nullptr;
}

LogosUnaryExpr* SemAnalyser::getFuncCallExpr(LogosParser::FuncCallContext* ctx) {
    const auto funcName = ctx->VARIABLE()->getText();
    const auto logosFunc = std::get<LogosFunc>(resolveSymbol(funcName)->value);
    vector<LogosExpr*> args;
    for (const auto funcArg : ctx->funcArgList()->funcArg()) {
        args.push_back(getExpr(funcArg->expr()));
    }
    const auto funcCallExpr = new LogosFuncCallExpr(logosFunc, args);
    codeNodes.push_back(new FuncCall(funcCallExpr));
    return funcCallExpr;

}

void SemAnalyser::addSymbol(const string& variableName, LogosExpr* logosExpr) {
    if (logosExpr) {
        currentScope[variableName] = new LogosSymbol(logosExpr->type, *logosExpr);
    }
}

LogosSymbol* SemAnalyser::resolveSymbol(const string& symbolName) {
    const auto it = currentScope.find(symbolName);
    if (it == currentScope.end()) {
        return nullptr;
    }
    return it->second;
}

SemAnalyser::~SemAnalyser() {
    for (auto& [name, symbol] : currentScope) {
        delete symbol;
    }
}