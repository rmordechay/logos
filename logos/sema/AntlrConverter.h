#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

#include "LogosParser.h"
#include "exprs/LogosSelection.h"
#include "funcs/LogosUserFunc.h"

#include <vector>

class LogosField;
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
    LogosField *getField(LogosParser::ExplicitVarDecContext* varDec);
    LogosUserFunc* getFunc(LogosParser::FuncImplementationContext* ctx);
    LogosStmt* getStmt(LogosParser::StatementContext* ctx);
    vector<LogosStmt*> getStmtList(LogosParser::StatementsBlockContext* ctx);
    LogosVarDec* getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx);
    LogosVarDec* getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx);
    LogosIfStmt* getIfStatement(LogosParser::IfStatementContext* ctx);
    LogosSelection* getSelection(LogosParser::SelectionContext* selection);
    LogosExpr* getExpr(LogosParser::ExprContext* ctx);
    LogosUnaryExpr* getUnaryExpr(LogosParser::UnaryExprContext* ctx);
    LogosConstructor* getConstructor(LogosParser::ConstructorCallContext* ctx);
    LogosFuncCall* getFuncCall(LogosParser::FuncCallContext* ctx);
    static LogosUnaryExpr* getConstant(LogosParser::ConstantContext* ctx);
    static LogosType* getType(antlr4::tree::TerminalNode* type);
    ~AntlerConverter() = default;
};


#endif //SEMANTICANALYSER_H
