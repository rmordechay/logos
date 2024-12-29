#include "SemAnalyser.h"

#include "CodeAddInt.h"
#include "CodeFuncCall.h"
#include "CodeStoreInt.h"
#include "LogosConfigs.h"
#include "LogosErrors.h"
#include "LogosParser.h"
#include "exprs/LogosConstantExpr.h"
#include "exprs/LogosFuncCallExpr.h"
#include "exprs/LogosVariableExpr.h"
#include "funcs/LogosPrint.h"
#include "types/LogosBool.h"
#include "types/LogosFloat.h"
#include "types/LogosInt.h"
#include "types/LogosString.h"

SemAnalyser::SemAnalyser(LogosPackage* rootPackage) {
    this->rootPackage = rootPackage;
    this->rootScope = new Scope();
    this->currentScope = this->rootScope;
    this->mainFile = nullptr;
}

void SemAnalyser::analyseProject() {
    mainFile = rootPackage->mainFile;
    visitMainFile();
}

void SemAnalyser::visitMainFile() {
    const auto fileCtx = mainFile->fileCtx;
    for (const auto func : fileCtx->mainFile()->funcImplementation()) {
        if (func->funcDec()->VARIABLE()->getText() == LOGOS_MAIN_FUNCTION) {
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
    } else if (const auto expr = ctx->funcCall()) {
        int logosExpr = 1;
    }
}

void SemAnalyser::visitExplicitVarDec(LogosParser::ExplicitVarDecContext* const ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto logosExpr = getExpr(ctx->expr());
    addSymbol(variableName, logosExpr, LOCAL_VARIABLE);
}

void SemAnalyser::visitImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto logosExpr = getExpr(ctx->expr());
    addSymbol(variableName, logosExpr, LOCAL_VARIABLE);
}

shared_ptr<LogosExpr> SemAnalyser::getExpr(LogosParser::ExprContext* ctx) {
    if (const auto unary = ctx->unaryExpr()) {
        return getUnaryExpr(unary);
    }
    const auto exprs = ctx->expr();
    if (exprs.size() == 1) {
        return getExpr(exprs[0]);
    }
    if (exprs.size() == 2) {
        auto left = getExpr(exprs[0]);
        auto right = getExpr(exprs[1]);
        if (ctx->PLUS()) {
            return make_shared<LogosBinaryExpr>(left, right, PLUS);
        }
        if (ctx->MINUS()) {
            return make_shared<LogosBinaryExpr>(left, right, MINUS);
        }
        if (ctx->STAR()) {
            return make_shared<LogosBinaryExpr>(left, right, STAR);
        }
        if (ctx->SLASH()) {
            return make_shared<LogosBinaryExpr>(left, right, SLASH);
        }
    }
    return nullptr;
}

shared_ptr<LogosUnaryExpr> SemAnalyser::getUnaryExpr(LogosParser::UnaryExprContext* ctx) {
    if (const auto constant = ctx->constant()) {
        auto logosConstantExpr = getConstantExpr(constant);
        return logosConstantExpr;
    }

    if (const auto variable = ctx->VARIABLE()) {
        return make_shared<LogosVariableExpr>(variable->getText());
    }

    if (const auto funcCall = ctx->funcCall()) {
        return getFuncCallExpr(funcCall);
    }
    return nullptr;
}


shared_ptr<LogosConstantExpr> SemAnalyser::getConstantExpr(LogosParser::ConstantContext* ctx) {
    if (const auto intToken = ctx->INTEGER()) {
        const auto value = stoi(intToken->getText());
        return make_shared<LogosConstantExpr>(make_shared<LogosInt>(value));
    }

    if (const auto floatToken = ctx->FLOAT()) {
        const auto value = stof(floatToken->getText());
        return make_shared<LogosConstantExpr>(make_shared<LogosFloat>(value));
    }

    if (const auto boolToken = ctx->BOOL()) {
        const auto value = boolToken->getText() == LogosBool::trueLiteral;
        return make_shared<LogosConstantExpr>(make_shared<LogosBool>(value));
    }

    if (const auto stringToken = ctx->STRING()) {
        const auto value = stringToken->getText();
        return make_shared<LogosConstantExpr>(make_shared<LogosString>(value));
    }
    return nullptr;
}

shared_ptr<LogosFuncCallExpr> SemAnalyser::getFuncCallExpr(LogosParser::FuncCallContext* ctx) {
    const auto funcName = ctx->VARIABLE()->getText();
    auto funcCallExpr = make_shared<LogosFuncCallExpr>(funcName, make_shared<LogosPrint>());
    const auto args = ctx->funcArgList()->funcArg();
    for (const auto arg : args) {
        auto logosExpr = getExpr(arg->expr());
        funcCallExpr->args.push_back(logosExpr);
    }
    return funcCallExpr;
}

void SemAnalyser::addSymbol(const string& name, const shared_ptr<LogosExpr>& expr, const SymbolKind kind) const {
    const auto symbol = new LogosSymbol(name, expr, kind);
    currentScope->symbolTable[name] = symbol;
}

void SemAnalyser::printError(const int errorCode) const {
    cout << "ERROR: " << LOGOS_ERRORS.at(errorCode) << endl;
    cout << "  1. " << mainFile->path << LOGOS_EXTENSION << endl;
}

SemAnalyser::~SemAnalyser() {
    for (auto& [name, symbol] : currentScope->symbolTable) {
        delete symbol;
    }
    delete rootPackage;
    delete rootScope;
}
