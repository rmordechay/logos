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
    void checkMainFile(LogosParser::MainFileContext* ctx);
    void checkMain(LogosParser::FuncImplementationContext* ctx);
    void checkObjectFile(LogosParser::ObjectFileContext* ctx);
    void checkImportStatement(LogosParser::ImportStatementContext* ctx);
    void checkObjectImplements(LogosParser::ObjectImplementsContext* ctx);

    ~SemAnalyser();
};



#endif //SEMANTICANALYSER_H
