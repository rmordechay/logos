
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "LogosListener.h"


/**
 * This class provides an empty implementation of LogosListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  LogosBaseListener : public LogosListener {
public:

  virtual void enterLogosFile(LogosParser::LogosFileContext * /*ctx*/) override { }
  virtual void exitLogosFile(LogosParser::LogosFileContext * /*ctx*/) override { }

  virtual void enterInterfaceFile(LogosParser::InterfaceFileContext * /*ctx*/) override { }
  virtual void exitInterfaceFile(LogosParser::InterfaceFileContext * /*ctx*/) override { }

  virtual void enterObjectFile(LogosParser::ObjectFileContext * /*ctx*/) override { }
  virtual void exitObjectFile(LogosParser::ObjectFileContext * /*ctx*/) override { }

  virtual void enterObjectDeclaration(LogosParser::ObjectDeclarationContext * /*ctx*/) override { }
  virtual void exitObjectDeclaration(LogosParser::ObjectDeclarationContext * /*ctx*/) override { }

  virtual void enterInterfaceDeclaration(LogosParser::InterfaceDeclarationContext * /*ctx*/) override { }
  virtual void exitInterfaceDeclaration(LogosParser::InterfaceDeclarationContext * /*ctx*/) override { }

  virtual void enterObjectImplements(LogosParser::ObjectImplementsContext * /*ctx*/) override { }
  virtual void exitObjectImplements(LogosParser::ObjectImplementsContext * /*ctx*/) override { }

  virtual void enterExplicitVarDecList(LogosParser::ExplicitVarDecListContext * /*ctx*/) override { }
  virtual void exitExplicitVarDecList(LogosParser::ExplicitVarDecListContext * /*ctx*/) override { }

  virtual void enterExplicitVarDec(LogosParser::ExplicitVarDecContext * /*ctx*/) override { }
  virtual void exitExplicitVarDec(LogosParser::ExplicitVarDecContext * /*ctx*/) override { }

  virtual void enterImplicitVarDec(LogosParser::ImplicitVarDecContext * /*ctx*/) override { }
  virtual void exitImplicitVarDec(LogosParser::ImplicitVarDecContext * /*ctx*/) override { }

  virtual void enterFuncDec(LogosParser::FuncDecContext * /*ctx*/) override { }
  virtual void exitFuncDec(LogosParser::FuncDecContext * /*ctx*/) override { }

  virtual void enterFuncCall(LogosParser::FuncCallContext * /*ctx*/) override { }
  virtual void exitFuncCall(LogosParser::FuncCallContext * /*ctx*/) override { }

  virtual void enterFuncImplementation(LogosParser::FuncImplementationContext * /*ctx*/) override { }
  virtual void exitFuncImplementation(LogosParser::FuncImplementationContext * /*ctx*/) override { }

  virtual void enterFuncBody(LogosParser::FuncBodyContext * /*ctx*/) override { }
  virtual void exitFuncBody(LogosParser::FuncBodyContext * /*ctx*/) override { }

  virtual void enterStatement(LogosParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(LogosParser::StatementContext * /*ctx*/) override { }

  virtual void enterExpr_list(LogosParser::Expr_listContext * /*ctx*/) override { }
  virtual void exitExpr_list(LogosParser::Expr_listContext * /*ctx*/) override { }

  virtual void enterExpr(LogosParser::ExprContext * /*ctx*/) override { }
  virtual void exitExpr(LogosParser::ExprContext * /*ctx*/) override { }

  virtual void enterBinary_expr(LogosParser::Binary_exprContext * /*ctx*/) override { }
  virtual void exitBinary_expr(LogosParser::Binary_exprContext * /*ctx*/) override { }

  virtual void enterUnary_expr(LogosParser::Unary_exprContext * /*ctx*/) override { }
  virtual void exitUnary_expr(LogosParser::Unary_exprContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

