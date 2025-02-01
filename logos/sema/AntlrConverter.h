#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

#include "LogosParser.h"
#include "exprs/LogosSelection.h"
#include "funcs/LogosUserFunc.h"

#include <vector>

class LogosType;
class LogosFuncCall;
class LogosConstructor;
class LogosUnaryExpr;
class LogosExpr;
class LogosIfStmt;
class LogosVarDec;
class LogosStmt;
class LogosFunc;
class LogosObjectFile;
class LogosImport;
class LogosObject;
class LogosMainFile;
class LogosFile;

using namespace std;

class AntlerConverter {
public:
    const string& filePath;
    explicit AntlerConverter(const string& filePath) : filePath(filePath) {}
    LogosFile* getLogosFile(LogosParser::LogosFileContext* ctx, const filesystem::path& filePath);
    LogosMainFile* getMainFile(LogosParser::MainFileContext* ctx);
    LogosObjectFile* getObjFile(LogosParser::ObjectFileContext* ctx);
    LogosObject* getObject(LogosParser::ObjectFileContext* ctx);
    LogosUserFunc* getFunc(LogosParser::FuncImplementationContext* ctx);
    LogosStmt* getStmt(LogosParser::StatementContext* ctx);
    vector<LogosStmt*> getStmtList(LogosParser::StatementsBlockContext* ctx);
    LogosVarDec* getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx);
    LogosVarDec* getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx);
    LogosIfStmt* getIfStatement(LogosParser::IfStatementContext* ctx);
    LogosSelection* getSelection(LogosParser::SelectionContext* selection);
    LogosExpr* getExpr(LogosParser::ExprContext* ctx);
    LogosUnaryExpr* getUnaryExpr(LogosParser::UnaryExprContext* ctx);
    LogosConstructor* getConstructorCallExpr(LogosParser::ConstructorCallContext* ctx);
    LogosFuncCall* getFuncCallExpr(LogosParser::FuncCallContext* ctx);
    static LogosUnaryExpr* getConstantExpr(LogosParser::ConstantContext* ctx);
    static LogosType* getType(antlr4::tree::TerminalNode* type);
    ~AntlerConverter() = default;
};


#endif //SEMANTICANALYSER_H
