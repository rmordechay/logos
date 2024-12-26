#include "SemAnalyser.h"

#include "LogosConfigs.h"

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

void SemAnalyser::checkImportStatement(LogosParser::ImportStatementContext* ctx) {
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

void SemAnalyser::checkStatement(LogosParser::StatementContext* ctx) {
    if (const auto explicitVarDec = ctx->explicitVarDec()) {
        setExplicitVariableSymbol(explicitVarDec);
    } else if (const auto implicitVarDec = ctx->implicitVarDec()) {
        setImplicitVariableSymbol(implicitVarDec);
    }
}

void SemAnalyser::inferType(LogosParser::ExprContext* ctx) {
    if (ctx->unaryExpr()) {
    }
}

void SemAnalyser::setExplicitVariableSymbol(LogosParser::ExplicitVarDecContext* const ctx) {
    const auto varName = ctx->VARIABLE()->getText();
    const auto typeName = ctx->TYPE()->getText();
    const auto symbol = new Symbol(varName, typeName, LOCAL_VARIABLE);
    currentScope->symbolTable[varName] = symbol;
    inferType(ctx->expr());
}

void SemAnalyser::setImplicitVariableSymbol(LogosParser::ImplicitVarDecContext* ctx) {
    const auto varName = ctx->VARIABLE()->getText();
    const auto symbol = new Symbol(varName, nullptr, LOCAL_VARIABLE);
    currentScope->symbolTable[varName] = symbol;
    inferType(ctx->expr());
}

SemAnalyser::~SemAnalyser() {
    delete rootPackage;
    delete rootScope;
}
