#include "SemAnalyser.h"

#include "LogosConfigs.h"
#include "LogosValue.h"

SemAnalyser::SemAnalyser(LogosPackage* rootPackage) {
    this->rootPackage = rootPackage;
    this->rootScope = new Scope();
    this->currentScope = this->rootScope;
}

void SemAnalyser::analyseProject() {
    const auto mainFileCtx = rootPackage->mainFile->fileCtx;
    checkImportStatement(mainFileCtx->importStatement());
    checkMainFile(mainFileCtx->mainFile());
}

void SemAnalyser::checkImportStatement(LogosParser::ImportStatementContext* ctx) const {
    if (ctx == nullptr) return;
    const auto importPaths = ctx->importPath();
    for (const auto importPath : importPaths) {
        for (const auto package : rootPackage->packages) {
            for (const auto file : package->files) {
            }
        }
    }
}

void SemAnalyser::checkMainFile(LogosParser::MainFileContext* ctx) {
    for (const auto func : ctx->funcImplementation()) {
        if (func->funcDec()->VARIABLE()->getText() == LOGOS_MAIN_FUNCTION) {
            checkMain(func);
        }
    }
}

void SemAnalyser::checkMain(LogosParser::FuncImplementationContext* ctx) {
    const auto statements = ctx->funcBody()->statementsBlock()->statement();
    for (const auto statement : statements) {
        checkStatement(statement);
    }
}

void SemAnalyser::checkObjectFile(LogosParser::ObjectFileContext* ctx) {
    if (ctx == nullptr) return;
}

void SemAnalyser::checkObjectImplements(LogosParser::ObjectImplementsContext* ctx) {
    if (ctx == nullptr) return;
}

void SemAnalyser::checkStatement(LogosParser::StatementContext* ctx) const {
    if (const auto explicitVarDec = ctx->explicitVarDec()) {
        setExplicitVariableSymbol(explicitVarDec);
    } else if (const auto implicitVarDec = ctx->implicitVarDec()) {
        setImplicitVariableSymbol(implicitVarDec);
    }
}

void SemAnalyser::setExplicitVariableSymbol(LogosParser::ExplicitVarDecContext* const ctx) const {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto typeName = ctx->TYPE()->getText();
    const auto symbol = new Symbol(variableName, typeName, LOCAL_VARIABLE);
    currentScope->symbolTable[variableName] = symbol;
}

void SemAnalyser::setImplicitVariableSymbol(LogosParser::ImplicitVarDecContext* ctx) const {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto symbol = new Symbol(variableName, LOCAL_VARIABLE);
    setSymbolFromExpr(ctx->expr(), symbol);
    currentScope->symbolTable[variableName] = symbol;
}

void SemAnalyser::setSymbolFromExpr(LogosParser::ExprContext* ctx, Symbol* symbol) const {
    if (const auto unary = ctx->unaryExpr()) {
        setSymbolFromUnaryExpr(unary, symbol);
    } else if (ctx->boolExpr()) {
        symbol->typeName = "Bool";
    }
}

void SemAnalyser::setSymbolFromUnaryExpr(LogosParser::UnaryExprContext* unary, Symbol* symbol) const {
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

SemAnalyser::~SemAnalyser() {
    delete rootPackage;
    delete rootScope;
}
