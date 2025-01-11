#include "SemAnalyser.h"

#include "LogosConfigs.h"
#include "LogosErrors.h"
#include "LogosParser.h"
#include "exprs/LogosConstantExpr.h"
#include "exprs/LogosFuncCallExpr.h"
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

void SemAnalyser::visitFuncCall(LogosParser::FuncCallContext* funcCall) {
    auto funcName = funcCall->VARIABLE()->getText();
}

shared_ptr<LogosExpr> SemAnalyser::getExpr(LogosParser::ExprContext* ctx) {
    if (const auto unary = ctx->unaryExpr()) {
        return getUnaryExpr(unary);
    }
    if (ctx->right != nullptr) {
        auto l = getExpr(ctx->left);
        auto r = getExpr(ctx->right);
        auto op = mapOperator(ctx);
        return make_shared<LogosBinaryExpr>(l, r, op);
    }
    return nullptr;
}

shared_ptr<LogosExpr> SemAnalyser::getUnaryExpr(LogosParser::UnaryExprContext* ctx) {
    if (const auto constant = ctx->constant()) {
        return getConstantExpr(constant);
    }

    if (const auto variable = ctx->VARIABLE()) {
        if (const auto resolvedSymbol = currentScope->resolveSymbol(variable->getText())) {
            return resolvedSymbol->expr;
        }
        return nullptr;
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
