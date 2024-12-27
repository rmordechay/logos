#include "SemAnalyser.h"

#include "LogosConfigs.h"
#include "LogosErrors.h"

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
    const auto symbol = new LogosSymbol(variableName, typeName, LOCAL_VARIABLE);
    currentScope->symbolTable[variableName] = symbol;
}

void SemAnalyser::visitImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto symbol = new LogosSymbol(variableName, LOCAL_VARIABLE);
    setSymbolFromExpr(ctx->expr(), symbol);
    currentScope->symbolTable[variableName] = symbol;
    codeNodes.push_back(new StoreInt(symbol));
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
        // const auto variableName = funcCall->VARIABLE()->getText();
        // const auto stringArg = new std::string(funcCall->paramCallList()[0]->paramCall()[0]->expr()->getText());
        // auto logosType = new LogosType();
        // const auto logosStringValue = new LogosValue(stringArg);
        // const auto newSymbol = new LogosSymbol("arg1", "String", PARAM);
        // newSymbol->logosValue = logosStringValue;
        // codeNodes.push_back(new FuncCall(newSymbol));
    }
}

void SemAnalyser::setSymbolFromExpr(LogosParser::ExprContext* ctx, LogosSymbol* symbol) const {
    if (const auto unary = ctx->unaryExpr()) {
        setSymbolFromUnaryExpr(unary, symbol);
    } else if (const auto binary = ctx->binaryExpr()) {
        setSymbolFromBinaryExpr(binary, symbol);
    } else if (ctx->boolExpr()) {
        symbol->typeName = LogosBool::name;
    }
}

void SemAnalyser::setSymbolFromUnaryExpr(LogosParser::UnaryExprContext* unary, LogosSymbol* symbol) const {
    if (const auto intToken = unary->INTEGER()) {
        symbol->typeName = LogosInt::name;
        const auto value = std::stoi(intToken->getText());
        symbol->logosValue = new LogosInt(value);
        return;
    }

    if (const auto floatToken = unary->FLOAT()) {
        symbol->typeName = LogosFloat::name;
        const auto value = std::stof(floatToken->getText());
        symbol->logosValue = new LogosFloat(value);
        return;
    }

    if (const auto boolToken = unary->BOOL()) {
        symbol->typeName = LogosBool::name;
        const auto value = boolToken->getText() == LogosBool::trueLiteral;
        symbol->logosValue = new LogosBool(value);
        return;
    }

    if (const auto stringToken = unary->STRING()) {
        symbol->typeName = LogosString::name;
        const auto value = stringToken->getText();
        symbol->logosValue = new LogosString(value);
        return;
    }

    if (const auto variable = unary->VARIABLE()) {
        const auto resolvedSymbol = currentScope->resolveSymbol(variable->getText());
        if (resolvedSymbol != nullptr) {
            symbol->typeName = resolvedSymbol->typeName;
            symbol->logosValue = resolvedSymbol->logosValue;
        }
        return;
    }

    if (const auto funcCall = unary->funcCall()) {
        const auto resolvedSymbol = currentScope->resolveSymbol(funcCall->getText());
        if (resolvedSymbol != nullptr) {
            symbol->typeName = resolvedSymbol->typeName;
            symbol->logosValue = resolvedSymbol->logosValue;
        }
        return;
    }

    if (const auto constructor = unary->constructorCall()) {
        symbol->typeName = constructor->TYPE()->getText();
    }
}

void SemAnalyser::setSymbolFromBinaryExpr(LogosParser::BinaryExprContext* ctx, LogosSymbol* symbol) const {

}

SemAnalyser::~SemAnalyser() {
    delete rootPackage;
    delete rootScope;
}

void SemAnalyser::printError(const int errorCode) {
    std::cout << "ERROR: " << LOGOS_ERRORS.at(errorCode) << std::endl;
    std::cout << "  1. " << mainFile->path << LOGOS_EXTENSION << std::endl;
}
