#include "SemAnalyser.h"

#include "LogosConfigs.h"
#include "LogosErrors.h"
#include "LogosParser.h"
#include "exprs/LogosConstantExpr.h"
#include "exprs/LogosFuncCallExpr.h"
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
    addSymbol(variableName, LOCAL_VARIABLE);
}

void SemAnalyser::visitImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto logosExpr = getExpr(ctx->expr());
    addSymbol(variableName, LOCAL_VARIABLE);
}

void SemAnalyser::visitFuncCall(LogosParser::FuncCallContext* funcCall) {
    auto funcName = funcCall->VARIABLE()->getText();
}

LogosExpr* SemAnalyser::getExpr(LogosParser::ExprContext* ctx) {
    if (const auto unary = ctx->unaryExpr()) {
        return getUnaryExpr(unary);
    }
    if (ctx->right != nullptr) {
        return new LogosBinaryExpr(getExpr(ctx->left), getExpr(ctx->right), mapOperator(ctx));
    }
    return nullptr;
}

LogosExpr* SemAnalyser::getUnaryExpr(LogosParser::UnaryExprContext* ctx) const {
    if (const auto constant = ctx->constant()) {
        return getConstantExpr(constant);
    }

    if (const auto variable = ctx->VARIABLE()) {
        if (const auto resolvedSymbol = currentScope->resolveSymbol(variable->getText())) {
            return resolvedSymbol->value.expr;
        }
        return nullptr;
    }

    if (const auto funcCall = ctx->funcCall()) {
        return getFuncCallExpr(funcCall);
    }
    return nullptr;
}


LogosConstantExpr* SemAnalyser::getConstantExpr(LogosParser::ConstantContext* ctx) {
    if (const auto intToken = ctx->INTEGER()) {
        const auto value = stoi(intToken->getText());
        return new LogosConstantExpr(new LogosInt(value));
    }

    if (const auto floatToken = ctx->FLOAT()) {
        const auto value = stof(floatToken->getText());
        return new LogosConstantExpr(new LogosFloat(value));
    }

    if (const auto boolToken = ctx->BOOL()) {
        const auto value = boolToken->getText() == LogosBool::trueLiteral;
        return new LogosConstantExpr(new LogosBool(value));
    }

    if (const auto stringToken = ctx->STRING()) {
        const auto value = stringToken->getText();
        return new LogosConstantExpr(new LogosString(value));
    }
    return nullptr;
}

LogosFuncCallExpr* SemAnalyser::getFuncCallExpr(LogosParser::FuncCallContext* ctx) {
    const auto funcName = ctx->VARIABLE()->getText();
    return nullptr;
}

void SemAnalyser::addSymbol(const string& name, const SymbolKind kind, const LogosSymbol::SymbolValue& value) const {
    const auto symbol = new LogosSymbol(name, kind, value);
    currentScope->symbolTable[name] = symbol;
}

void SemAnalyser::addSymbol(const string& name, const SymbolKind kind) const {
    const auto symbol = new LogosSymbol(name, kind);
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
