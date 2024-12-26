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

void SemAnalyser::checkMain(LogosParser::FuncImplementationContext* ctx) {

}

void SemAnalyser::checkMainFile(LogosParser::MainFileContext* ctx) {
    for (const auto func : ctx->funcImplementation()) {
        if (func->funcDec()->VARIABLE()->getText() == LOGOS_MAIN_FUNCTION) {
            checkMain(func);
        }
    }
}

void SemAnalyser::checkObjectFile(LogosParser::ObjectFileContext* ctx) {
    if (ctx == nullptr) return;
    checkObjectImplements(ctx->objectImplements());
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