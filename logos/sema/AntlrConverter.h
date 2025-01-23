#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H
#include "CodeGeneration.h"
#include "LogosParser.h"

#include <vector>

class LogosFuncCall;
class LogosConstructor;
class LogosUnaryExpr;
class LogosExpr;
class LogosIfStmt;
class LogosVarDec;
class LogosStmt;
class LogosFunc;
class LogosObjectFile;
class LogosImportStmt;
class LogosObject;
class LogosMainFile;
class LogosFile;

using namespace std;

class AntlerConverter {
public:
    static LogosFile* getLogosFile(LogosParser::LogosFileContext* ctx);
    static LogosMainFile* getMainFile(LogosParser::MainFileContext* ctx);
    static LogosObject* getObject(LogosParser::ObjectFileContext* ctx);
    static vector<LogosImportStmt*> getImportsStmt(LogosParser::ImportStatementContext* ctx);
    static LogosObjectFile* getObjFile(LogosParser::ObjectFileContext* ctx);
    static LogosFunc* getFunc(LogosParser::FuncImplementationContext* ctx);
    static LogosStmt* getStmt(LogosParser::StatementContext* ctx);
    static vector<LogosStmt*> getStmtList(LogosParser::StatementsBlockContext* ctx);
    static LogosVarDec* getVarDec(LogosParser::ExplicitVarDecContext* ctx);
    static LogosVarDec* getVarDec(LogosParser::ImplicitVarDecContext* ctx);
    static LogosIfStmt* getIfStatement(LogosParser::IfStatementContext* ctx);
    static LogosExpr* getExpr(LogosParser::ExprContext* ctx);
    static LogosUnaryExpr* getUnaryExpr(LogosParser::UnaryExprContext* ctx);
    static LogosConstructor* getConstructorCallExpr(LogosParser::ConstructorCallContext* ctx);
    static LogosFuncCall* getFuncCallExpr(LogosParser::FuncCallContext* ctx);
    static Position getPosition(const antlr4::Token* ctx);
    static LogosUnaryExpr* getConstantExpr(LogosParser::ConstantContext* ctx);
    static const LogosType& getType(antlr4::tree::TerminalNode* type);
    ~AntlerConverter() = default;
};


#endif //SEMANTICANALYSER_H
