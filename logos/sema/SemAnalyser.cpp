#include "SemAnalyser.h"

#include "LogosConfigs.h"
#include "LogosErrors.h"
#include "LogosValue.h"

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

void SemAnalyser::visitStatement(LogosParser::StatementContext* ctx){
    if (const auto explicitVarDec = ctx->explicitVarDec()) {
        visitExplicitVarDec(explicitVarDec);
    } else if (const auto implicitVarDec = ctx->implicitVarDec()) {
        visitImplicitVarDec(implicitVarDec);
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

void SemAnalyser::setSymbolFromExpr(LogosParser::ExprContext* ctx, LogosSymbol* symbol) const {
    if (const auto unary = ctx->unaryExpr()) {
        setSymbolFromUnaryExpr(unary, symbol);
    } else if (const auto binary = ctx->binaryExpr()) {
        setSymbolFromBinaryExpr(binary, symbol);
    } else if (ctx->boolExpr()) {
        symbol->typeName = "Bool";
    }
}

void SemAnalyser::setSymbolFromUnaryExpr(LogosParser::UnaryExprContext* unary, LogosSymbol* symbol) const {
    if (const auto intToken = unary->INTEGER()) {
        symbol->typeName = "Int";
        const auto value = std::stoi(intToken->getText());
        symbol->value = new LogosValue(ValueType::INT, &value);
        return;
    }

    if (const auto floatToken = unary->FLOAT()) {
        symbol->typeName = "Float";
        const auto value = std::stof(floatToken->getText());
        symbol->value = new LogosValue(ValueType::FLOAT, &value);
        return;
    }

    if (const auto boolToken = unary->BOOL()) {
        symbol->typeName = "Bool";
        const auto value = boolToken->getText() == "true";
        symbol->value = new LogosValue(ValueType::BOOL, &value);
        return;
    }

    if (const auto stringToken = unary->STRING()) {
        symbol->typeName = "String";
        const auto value = stringToken->getText();
        symbol->value = new LogosValue(ValueType::STRING, &value);
        return;
    }

    if (const auto variable = unary->VARIABLE()) {
        const auto it = currentScope->symbolTable.find(variable->getText());
        if (it != currentScope->symbolTable.end()) {
            symbol->typeName = it->second->typeName;
            symbol->value = it->second->value;
        }
        return;
    }

    if (const auto funcCall = unary->funcCall()) {
        const auto it = currentScope->symbolTable.find(funcCall->VARIABLE()->getText());
        if (it != currentScope->symbolTable.end()) {
            symbol->typeName = it->second->typeName;
            symbol->value = it->second->value;
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