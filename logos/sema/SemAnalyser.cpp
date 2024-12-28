#include "SemAnalyser.h"

#include "LogosConfigs.h"
#include "LogosErrors.h"
#include "LogosParser.h"
#include "builtin/Print.h"
#include "nodes/StoreInt.h"
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
    visitPackage(rootPackage);
}

void SemAnalyser::visitPackage(const LogosPackage* package) {
    for (const auto file : package->files) {
        visitLogosFile(file->fileCtx);
    }
    for (const auto childPackage : package->packages) {
        visitPackage(childPackage);
    }
}

void SemAnalyser::visitLogosFile(LogosParser::LogosFileContext* ctx) {
    visitImportStatement(ctx->importStatement());
    visitObjectFile(ctx->objectFile());
}

void SemAnalyser::visitImportStatement(LogosParser::ImportStatementContext* ctx) const {
    if (ctx == nullptr) return;
    const auto importPaths = ctx->importPath();
    for (const auto importPath : importPaths) {
        for (const auto package : rootPackage->packages) {
            for (const auto file : package->files) {
            }
        }
    }
}

void SemAnalyser::visitMainFile() {
    visitImportStatement(mainFile->fileCtx->importStatement());
    for (const auto func : mainFile->fileCtx->mainFile()->funcImplementation()) {
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

void SemAnalyser::visitObjectFile(LogosParser::ObjectFileContext* ctx) {
    if (ctx == nullptr) return;
}

void SemAnalyser::visitObjectImplements(LogosParser::ObjectImplementsContext* ctx) {
    if (ctx == nullptr) return;
}

void SemAnalyser::visitStatement(LogosParser::StatementContext* ctx) {
    if (const auto explicitVarDec = ctx->explicitVarDec()) {
        visitExplicitVarDec(explicitVarDec);
    } else if (const auto implicitVarDec = ctx->implicitVarDec()) {
        visitImplicitVarDec(implicitVarDec);
    } else if (const auto expr = ctx->expr()) {
        visitExpr(expr);
    }
}

void SemAnalyser::visitExplicitVarDec(LogosParser::ExplicitVarDecContext* const ctx) const {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto typeName = ctx->TYPE()->getText();
    const auto symbol = new LogosSymbol(variableName, LOCAL_VARIABLE);
    currentScope->symbolTable[variableName] = symbol;
}

void SemAnalyser::visitImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto symbol = new LogosSymbol(variableName, LOCAL_VARIABLE);
    // const auto logosExpr = getExpr(ctx->expr());
    // symbol->logosType = logosExpr->results;
    // currentScope->symbolTable[variableName] = symbol;
    // codeNodes.push_back(new StoreInt(symbol));
}

void SemAnalyser::visitExpr(LogosParser::ExprContext* ctx) {
    if (const auto unary = ctx->unaryExpr()) {
        visitUnaryExpr(unary);
    } else if (const auto binary = ctx->binaryExpr()) {

    } else if (ctx->boolExpr()) {

    }
}

void SemAnalyser::visitUnaryExpr(LogosParser::UnaryExprContext* ctx) {
    if (const auto funcCall = ctx->funcCall()) {
        visitFuncCall(funcCall);
    }
}

void SemAnalyser::visitFuncCall(LogosParser::FuncCallContext* const ctx) {
    const auto funcName = ctx->VARIABLE()->getText();
    if (BUILTIN_FUNCS.contains(funcName)) {
        visitBuiltinFunc(ctx, funcName);
    }
}

void SemAnalyser::visitBuiltinFunc(LogosParser::FuncCallContext* const ctx, const std::string& funcName) {
    const auto builtinFunc = BUILTIN_FUNCS.at(funcName);
    const auto args = ctx->funcArgList()->funcArg();
    const auto newSymbol = new LogosSymbol( PARAM);
    const auto exprType = getExpr(args[0]->expr());
    newSymbol->logosType = exprType.results;
    builtinFunc->args.push_back(newSymbol);
    codeNodes.push_back(builtinFunc);
}

LogosExpr SemAnalyser::getExpr(LogosParser::ExprContext* ctx) const {
    if (const auto unary = ctx->unaryExpr()) {
        return LogosExpr(getUnaryExpr(unary));
    }
    if (const auto binary = ctx->binaryExpr()) {
        return LogosExpr(getBinaryExpr(binary));
    }
    if (const auto binary = ctx->binaryExpr()) {
        return LogosExpr(getBinaryExpr(binary));
    }
}

LogosUnaryExpr SemAnalyser::getUnaryExpr(LogosParser::UnaryExprContext* unary) const {
    if (const auto intToken = unary->INTEGER()) {
        const auto value = std::stoi(intToken->getText());
        const auto logosInt = new LogosInt(value);
        return LogosUnaryExpr(*logosInt, logosInt);
    }

    if (const auto floatToken = unary->FLOAT()) {
        const auto value = std::stof(floatToken->getText());
        const auto logosFloat = new LogosFloat(value);
        return LogosUnaryExpr(*logosFloat, logosFloat);
    }

    if (const auto boolToken = unary->BOOL()) {
        const auto value = boolToken->getText() == LogosBool::trueLiteral;
        const auto logosBool = new LogosBool(value);
        return LogosUnaryExpr(*logosBool, logosBool);
    }

    if (const auto stringToken = unary->STRING()) {
        const auto value = stringToken->getText();
        const auto logosString = new LogosString(value);
        return LogosUnaryExpr(*logosString, logosString);
    }

    // if (const auto variable = unary->VARIABLE()) {
    //     const auto resolvedSymbol = currentScope->resolveSymbol(variable->getText());
    //     if (resolvedSymbol != nullptr) {
    //         return resolvedSymbol->logosType;
    //     }
    //     return nullptr;
    // }
    //
    // if (const auto funcCall = unary->funcCall()) {
    //     const auto resolvedSymbol = currentScope->resolveSymbol(funcCall->VARIABLE()->getText());
    //     if (resolvedSymbol != nullptr) {
    //         return resolvedSymbol->logosType;
    //     }
    //     return nullptr;
    // }
    //
    // if (const auto constructor = unary->constructorCall()) {
    //     const auto resolvedSymbol = currentScope->resolveSymbol(constructor->TYPE()->getText());
    //     if (resolvedSymbol != nullptr) {
    //         return resolvedSymbol->logosType;
    //     }
    //     return nullptr;
    // }
}

LogosBinaryExpr SemAnalyser::getBinaryExpr(LogosParser::BinaryExprContext* ctx) const {
    // const auto left = getUnaryExpr(ctx->unaryExpr());
    // const auto right = getExpr(ctx->expr());
    // if (right == nullptr) {
    //     return left;
    // }
    // return left->applyOperation(right);
}


SemAnalyser::~SemAnalyser() {
    delete rootPackage;
    delete rootScope;
}

void SemAnalyser::printError(const int errorCode) {
    std::cout << "ERROR: " << LOGOS_ERRORS.at(errorCode) << std::endl;
    std::cout << "  1. " << mainFile->path << LOGOS_EXTENSION << std::endl;
}
