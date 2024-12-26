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
    void inferType(LogosParser::ExprContext* ctx);
    void setExplicitVariableSymbol(LogosParser::ExplicitVarDecContext* ctx);
    void setImplicitVariableSymbol(LogosParser::ImplicitVarDecContext* ctx);

    ~SemAnalyser();
};



#endif //SEMANTICANALYSER_H
