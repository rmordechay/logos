#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

#include "ASTNode.h"
#include "LogosPackage.h"
#include "LogosParser.h"
#include "Scope.h"

#include <llvm/IR/LLVMContext.h>

class SemAnalyser final {
public:
    LogosPackage* rootPackage;
    Scope* rootScope;
    Scope* currentScope;
    LogosFile* mainFile;
    std::vector<ASTNode> astNodes;

    explicit SemAnalyser(LogosPackage* rootPackage);
    void analyseProject();
    void visitPackage(const LogosPackage* package);
    void visitLogosFile(LogosParser::LogosFileContext* ctx);
    void visitImportStatement(LogosParser::ImportStatementContext* ctx) const;
    void visitMainFile();
    void visitFuncImplementation(LogosParser::FuncImplementationContext* ctx);
    void visitObjectFile(LogosParser::ObjectFileContext* ctx);
    void visitObjectImplements(LogosParser::ObjectImplementsContext* ctx);
    void visitStatement(LogosParser::StatementContext* ctx) const;
    void setExplicitVariableSymbol(LogosParser::ExplicitVarDecContext* ctx) const;
    void setImplicitVariableSymbol(LogosParser::ImplicitVarDecContext* ctx) const;
    void setSymbolFromExpr(LogosParser::ExprContext* ctx, LogosSymbol* symbol) const;
    void setSymbolFromUnaryExpr(LogosParser::UnaryExprContext* unary, LogosSymbol* symbol) const;
    void setSymbolFromBinaryExpr(LogosParser::BinaryExprContext* ctx, LogosSymbol* symbol) const;
    void printError(int errorCode);
    ~SemAnalyser();
};


#endif //SEMANTICANALYSER_H
