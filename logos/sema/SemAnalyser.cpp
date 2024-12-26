#include "SemAnalyser.h"

void SemAnalyser::checkLogosFile(LogosParser::LogosFileContext* ctx) {
    if (ctx == nullptr) return;
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
}

void SemAnalyser::checkObjectImplements(LogosParser::ObjectImplementsContext* ctx) {
    if (ctx == nullptr) return;

}
