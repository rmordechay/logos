#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

#include "LogosPackage.h"
#include "LogosParser.h"
#include "Scope.h"
#include "exprs/LogosBinaryExpr.h"
#include "exprs/LogosConstantExpr.h"
#include "exprs/LogosFuncCallExpr.h"
#include "exprs/LogosUnaryExpr.h"

using namespace std;

class SemAnalyser {
public:
    LogosPackage* rootPackage;
    Scope* rootScope;
    Scope* currentScope;
    LogosFile* mainFile;

    explicit SemAnalyser(LogosPackage* rootPackage);
    void analyseProject();
    void visitPackage(const LogosPackage* package);
    void visitLogosFile(LogosParser::LogosFileContext* ctx);
    void visitImportStatement(LogosParser::ImportStatementContext* ctx) const;
    void visitMainFile();
    void visitFuncImplementation(LogosParser::FuncImplementationContext* ctx);
    void visitObjectFile(LogosParser::ObjectFileContext* ctx);
    void visitObjectImplements(LogosParser::ObjectImplementsContext* ctx);
    void visitStatement(LogosParser::StatementContext* ctx);
    void visitExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx);
    void visitImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx);
    static void visitFuncCall(LogosParser::FuncCallContext* funcCall);
    LogosExpr* getExpr(LogosParser::ExprContext* ctx);
    LogosExpr* getUnaryExpr(LogosParser::UnaryExprContext* ctx) const;
    static LogosConstantExpr* getConstantExpr(LogosParser::ConstantContext* ctx);
    static LogosFuncCallExpr* getFuncCallExpr(LogosParser::FuncCallContext* ctx);
    void addSymbol(const std::string& name, SymbolKind kind, const LogosSymbol::SymbolValue& value) const;
    void addSymbol(const string& name, SymbolKind kind) const;
    void printError(int errorCode) const;
    ~SemAnalyser();
};


#endif //SEMANTICANALYSER_H
