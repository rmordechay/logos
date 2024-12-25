
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "LogosParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by LogosParser.
 */
class  LogosListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterLogosFile(LogosParser::LogosFileContext *ctx) = 0;
  virtual void exitLogosFile(LogosParser::LogosFileContext *ctx) = 0;

  virtual void enterInterfaceFile(LogosParser::InterfaceFileContext *ctx) = 0;
  virtual void exitInterfaceFile(LogosParser::InterfaceFileContext *ctx) = 0;

  virtual void enterObjectFile(LogosParser::ObjectFileContext *ctx) = 0;
  virtual void exitObjectFile(LogosParser::ObjectFileContext *ctx) = 0;

  virtual void enterObjectDeclaration(LogosParser::ObjectDeclarationContext *ctx) = 0;
  virtual void exitObjectDeclaration(LogosParser::ObjectDeclarationContext *ctx) = 0;

  virtual void enterInterfaceDeclaration(LogosParser::InterfaceDeclarationContext *ctx) = 0;
  virtual void exitInterfaceDeclaration(LogosParser::InterfaceDeclarationContext *ctx) = 0;

  virtual void enterObjectImplements(LogosParser::ObjectImplementsContext *ctx) = 0;
  virtual void exitObjectImplements(LogosParser::ObjectImplementsContext *ctx) = 0;

  virtual void enterExplicitVarDecList(LogosParser::ExplicitVarDecListContext *ctx) = 0;
  virtual void exitExplicitVarDecList(LogosParser::ExplicitVarDecListContext *ctx) = 0;

  virtual void enterExplicitVarDec(LogosParser::ExplicitVarDecContext *ctx) = 0;
  virtual void exitExplicitVarDec(LogosParser::ExplicitVarDecContext *ctx) = 0;

  virtual void enterImplicitVarDec(LogosParser::ImplicitVarDecContext *ctx) = 0;
  virtual void exitImplicitVarDec(LogosParser::ImplicitVarDecContext *ctx) = 0;

  virtual void enterFuncDec(LogosParser::FuncDecContext *ctx) = 0;
  virtual void exitFuncDec(LogosParser::FuncDecContext *ctx) = 0;

  virtual void enterFuncCall(LogosParser::FuncCallContext *ctx) = 0;
  virtual void exitFuncCall(LogosParser::FuncCallContext *ctx) = 0;

  virtual void enterFuncImplementation(LogosParser::FuncImplementationContext *ctx) = 0;
  virtual void exitFuncImplementation(LogosParser::FuncImplementationContext *ctx) = 0;

  virtual void enterFuncBody(LogosParser::FuncBodyContext *ctx) = 0;
  virtual void exitFuncBody(LogosParser::FuncBodyContext *ctx) = 0;

  virtual void enterStatement(LogosParser::StatementContext *ctx) = 0;
  virtual void exitStatement(LogosParser::StatementContext *ctx) = 0;

  virtual void enterExpr_list(LogosParser::Expr_listContext *ctx) = 0;
  virtual void exitExpr_list(LogosParser::Expr_listContext *ctx) = 0;

  virtual void enterExpr(LogosParser::ExprContext *ctx) = 0;
  virtual void exitExpr(LogosParser::ExprContext *ctx) = 0;

  virtual void enterBinary_expr(LogosParser::Binary_exprContext *ctx) = 0;
  virtual void exitBinary_expr(LogosParser::Binary_exprContext *ctx) = 0;

  virtual void enterUnary_expr(LogosParser::Unary_exprContext *ctx) = 0;
  virtual void exitUnary_expr(LogosParser::Unary_exprContext *ctx) = 0;


};

