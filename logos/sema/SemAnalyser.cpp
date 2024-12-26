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

void SemAnalyser::checkStatement(LogosParser::StatementContext* ctx) {
    const auto explicitVarDec = ctx->explicitVarDec();
    if (explicitVarDec != nullptr) {
        const auto varName = explicitVarDec->VARIABLE()->getText();
        const auto typeName = explicitVarDec->TYPE()->getText();
        auto symbol = new Symbol(varName, typeName, LOCAL_VARIABLE);
        currentScope->symbolTable[varName] = symbol;
    }
}

void SemAnalyser::checkObjectFile(LogosParser::ObjectFileContext* ctx) {
    if (ctx == nullptr) return;
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

void SemAnalyser::checkObjectImplements(LogosParser::ObjectImplementsContext* ctx) {
    if (ctx == nullptr) return;

}

SemAnalyser::~SemAnalyser() {
    delete rootPackage;
    delete rootScope;
}