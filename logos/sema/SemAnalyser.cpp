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

void SemAnalyser::visitBuiltinFunc(LogosParser::FuncCallContext* const ctx, const string& funcName) {
    const auto builtinFunc = BUILTIN_FUNCS.at(funcName);
    const auto args = ctx->funcArgList()->funcArg();
    const auto newSymbol = new LogosSymbol( PARAM);
    if (const auto exprType = getExpr(args[0]->expr())) {
        newSymbol->logosType = exprType->results.get();
        builtinFunc->args.push_back(newSymbol);
        codeNodes.push_back(builtinFunc);
    }
}

shared_ptr<LogosExpr> SemAnalyser::getExpr(LogosParser::ExprContext* ctx) const {
    if (const auto unary = ctx->unaryExpr()) {
        auto logosTypedValue = getUnaryTypedValue(unary);
        auto logosUnaryExpr = make_shared<LogosUnaryExpr>(logosTypedValue);
        return logosUnaryExpr;
    }
    if (const auto binary = ctx->binaryExpr()) {
        const auto leftExpr = getUnaryTypedValue(ctx->unaryExpr());
        const auto right = binary->expr();
        if (right == nullptr) {
            return make_shared<LogosUnaryExpr>(leftExpr);
        }
        return make_shared<LogosBinaryExpr>(*leftExpr, *getExpr(right)->results, mapOperator(binary));
    }
    return nullptr;
}

shared_ptr<LogosTypedValue> SemAnalyser::getUnaryTypedValue(LogosParser::UnaryExprContext* ctx) const {
    if (const auto intToken = ctx->INTEGER()) {
        const auto value = stoi(intToken->getText());
        return make_shared<LogosInt>(LogosInt(value));
    }

    if (const auto floatToken = ctx->FLOAT()) {
        const auto value = stof(floatToken->getText());
        return make_shared<LogosFloat>(LogosFloat(value));
    }

    if (const auto boolToken = ctx->BOOL()) {
        const auto value = boolToken->getText() == LogosBool::trueLiteral;
        return make_shared<LogosBool>(LogosBool(value));
    }

    if (const auto stringToken = ctx->STRING()) {
        const auto value = stringToken->getText();
        return make_shared<LogosString>(LogosString(value));
    }

    if (const auto variable = ctx->VARIABLE()) {
        const auto resolvedSymbol = currentScope->resolveSymbol(variable->getText());
        if (resolvedSymbol != nullptr) {
            if (const auto intType = dynamic_cast<LogosInt*>(resolvedSymbol->logosType)) {
                return make_shared<LogosInt>(*intType);
            }
        }
        return nullptr;
    }
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
    return nullptr;
}


SemAnalyser::~SemAnalyser() {
    for (auto& [name, symbol] : currentScope->symbolTable) {
        delete symbol;
    }
    delete rootPackage;
    delete rootScope;
}

void SemAnalyser::printError(const int errorCode) const {
    cout << "ERROR: " << LOGOS_ERRORS.at(errorCode) << endl;
    cout << "  1. " << mainFile->path << LOGOS_EXTENSION << endl;
}

