#include "SemAnalyser.h"

SemAnalyser::SemAnalyser(LogosPackage* rootPackage) {
    this->rootPackage = rootPackage;
    this->rootScope = new Scope();
    this->currentScope = this->rootScope;
}

void SemAnalyser::analyseProject() {
    const auto mainFile = rootPackage->mainFile->fileCtx;
    if (mainFile == nullptr) return;
    checkImportStatement(mainFile->importStatement());
    checkLogosFile(mainFile);
}

void SemAnalyser::checkLogosFile(LogosParser::LogosFileContext* ctx) {
    const auto objectFile = ctx->objectFile();
    checkImportStatement(ctx->importStatement());
    checkObjectFile(objectFile);
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
                if (file->name == importPath->TYPE()[0]->getText()) {
                    std::cout << file->name << std::endl;
                }
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