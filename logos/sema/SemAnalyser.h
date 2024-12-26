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

    explicit SemAnalyser(LogosPackage* rootPackage);
    void analyseProject();
    void checkImportStatement(LogosParser::ImportStatementContext* ctx);
    void checkMainFile(LogosParser::MainFileContext* ctx);
    void checkMain(LogosParser::FuncImplementationContext* ctx);
    void checkObjectFile(LogosParser::ObjectFileContext* ctx);
    void checkObjectImplements(LogosParser::ObjectImplementsContext* ctx);
    void checkStatement(LogosParser::StatementContext* ctx);
    void setExplicitVariableSymbol(LogosParser::ExplicitVarDecContext* ctx) const;
    void setImplicitVariableSymbol(LogosParser::ImplicitVarDecContext* ctx);
    void inferType(LogosParser::ExprContext* ctx, Symbol* symbol);
    void setSymbolFromUnary(LogosParser::UnaryExprContext* unary, Symbol* symbol);

    ~SemAnalyser();
};



#endif //SEMANTICANALYSER_H
