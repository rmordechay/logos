#include "SemAnalyser.h"

#include "Print.h"
#include "LogosConfigs.h"
#include "LogosErrors.h"
#include "LogosParser.h"
#include "StoreExpr.h"
#include "exprs/LogosConstantExpr.h"
#include "exprs/LogosFuncCallExpr.h"
#include "exprs/LogosVariableExpr.h"
#include "funcs/LogosPrint.h"
#include "types/LogosBool.h"
#include "types/LogosFloat.h"
#include "types/LogosInt.h"
#include "types/LogosString.h"

SemAnalyser::SemAnalyser(const LogosPackage& rootPackage) : rootPackage(rootPackage) {
    this->rootScope = new Scope();
    this->currentScope = this->rootScope;
    currentScope->symbolTable["print"] = new LogosSymbol("print", FUNC_DEFINITION, SymbolValue(new LogosPrint()));
    this->mainFile = nullptr;
}

void SemAnalyser::analyseProject() {
    mainFile = rootPackage.mainFile;
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
    addSymbol(variableName, logosExpr);
}

void SemAnalyser::visitImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto logosExpr = getExpr(ctx->expr());
    addSymbol(variableName, logosExpr);
    codeNodes.push_back(new StoreExpr(variableName, logosExpr));
}

void SemAnalyser::visitFuncCall(LogosParser::FuncCallContext* ctx) {
    auto logosFuncCallExpr = getFuncCallExpr(ctx);
    codeNodes.push_back(new Print(logosFuncCallExpr));
}

LogosExpr* SemAnalyser::getExpr(LogosParser::ExprContext* ctx) {
    if (const auto unary = ctx->unaryExpr()) {
        return getUnaryExpr(unary);
    }
    if (ctx->right != nullptr) {
        return getBinaryExpr(ctx);
    }
    return nullptr;
}

LogosExpr* SemAnalyser::getUnaryExpr(LogosParser::UnaryExprContext* ctx) {
    if (const auto constant = ctx->constant()) {
        return getConstantExpr(constant);
    }

    if (const auto variable = ctx->VARIABLE()) {
        const auto symbolName = variable->getText();
        if (const auto resolvedSymbol = currentScope->resolveSymbol(symbolName)) {
            return new LogosVariableExpr(symbolName, *resolvedSymbol);
        }
        return nullptr;
    }

    if (const auto funcCall = ctx->funcCall()) {
        return getFuncCallExpr(funcCall);
    }
    return nullptr;
}

LogosExpr* SemAnalyser::getBinaryExpr(LogosParser::ExprContext* ctx) {
    const auto left = getExpr(ctx->left);
    const auto right = getExpr(ctx->right);
    const auto binaryExpr = new LogosBinaryExpr(left, right, mapOperator(ctx));
    binaryExpr->exprType = left->exprType;
    return binaryExpr;
}


LogosConstantExpr* SemAnalyser::getConstantExpr(LogosParser::ConstantContext* ctx) const {
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
    const auto builtinFunc = builtinFuncs.at(funcName);
    std::vector<LogosExpr*> args;
    for (const auto funcArg : ctx->funcArgList()->funcArg()) {
        args.push_back(getExpr(funcArg->expr()));
    }
    if (builtinFunc) {
        return new LogosFuncCallExpr(funcName, builtinFunc, args);
    }
    return nullptr;
}

void SemAnalyser::addSymbol(const std::string& variableName, LogosExpr* const logosExpr) const {
    const SymbolValue symbolValue(logosExpr);
    currentScope->symbolTable[variableName] = new LogosSymbol(variableName, LOCAL_VARIABLE, symbolValue);
}

void SemAnalyser::printError(const int errorCode) const {
    cout << "ERROR: " << LOGOS_ERRORS.at(errorCode) << endl;
    cout << "  1. " << mainFile->path << LOGOS_EXTENSION << endl;
}

SemAnalyser::~SemAnalyser() {
    for (auto& [name, symbol] : currentScope->symbolTable) {
        delete symbol;
    }
    for (const auto codeNode : codeNodes) {
        delete codeNode;
    }
    delete rootScope;
    if (mainFile) {
        delete mainFile;
    }
}