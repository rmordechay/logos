#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H


#include "LogosPackage.h"
#include "LogosParser.h"
#include "Scope.h"

class SemAnalyser final {
public:
    LogosPackage* rootPackage;
    Scope* rootScope;
    Scope* currentScope;
    LogosFile* mainFile;

    explicit SemAnalyser(LogosPackage* rootPackage);
    void analyseProject();
    void checkPackage(const LogosPackage* package);
    void checkLogosFile(LogosParser::LogosFileContext* ctx);
    void checkImportStatement(LogosParser::ImportStatementContext* ctx) const;
    void checkMainFile();
    void checkMain(LogosParser::FuncImplementationContext* ctx);
    void checkObjectFile(LogosParser::ObjectFileContext* ctx);
    void checkObjectImplements(LogosParser::ObjectImplementsContext* ctx);
    void checkStatement(LogosParser::StatementContext* ctx) const;
    void setExplicitVariableSymbol(LogosParser::ExplicitVarDecContext* ctx) const;
    void setImplicitVariableSymbol(LogosParser::ImplicitVarDecContext* ctx) const;
    void setSymbolFromExpr(LogosParser::ExprContext* ctx, Symbol* symbol) const;
    void setSymbolFromUnaryExpr(LogosParser::UnaryExprContext* unary, Symbol* symbol) const;
    void printError(int errorCode);
    ~SemAnalyser();
};


#endif //SEMANTICANALYSER_H
