#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H
#include "LogosParser.h"

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
    LogosObject* getObject(LogosParser::ObjectFileContext* ctx);
    vector<LogosImport*> getImportsStmt(LogosParser::ImportStatementContext* ctx);
    LogosObjectFile* getObjFile(LogosParser::ObjectFileContext* ctx);
    LogosFunc* getFunc(LogosParser::FuncImplementationContext* ctx);
    LogosStmt* getStmt(LogosParser::StatementContext* ctx);
    vector<LogosStmt*> getStmtList(LogosParser::StatementsBlockContext* ctx);
    LogosVarDec* getVarDec(LogosParser::ExplicitVarDecContext* ctx);
    LogosVarDec* getVarDec(LogosParser::ImplicitVarDecContext* ctx);
    LogosIfStmt* getIfStatement(LogosParser::IfStatementContext* ctx);
    LogosExpr* getExpr(LogosParser::ExprContext* ctx);
    LogosUnaryExpr* getUnaryExpr(LogosParser::UnaryExprContext* ctx);
    LogosConstructor* getConstructorCallExpr(LogosParser::ConstructorCallContext* ctx);
    LogosFuncCall* getFuncCallExpr(LogosParser::FuncCallContext* ctx);
    LogosUnaryExpr* getConstantExpr(LogosParser::ConstantContext* ctx);
    const LogosType& getType(antlr4::tree::TerminalNode* type);
    ~AntlerConverter() = default;
};


#endif //SEMANTICANALYSER_H
