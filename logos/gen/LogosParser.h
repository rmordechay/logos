
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosParser : public antlr4::Parser {
public:
  enum {
    LEFT_PAREN = 1, RIGHT_PAREN = 2, LEFT_BRACE = 3, RIGHT_BRACE = 4, LEFT_BRACKET = 5, 
    RIGHT_BRACKET = 6, LEFT_ANGLE = 7, RIGHT_ANGLE = 8, COMMA = 9, DOT = 10, 
    COLON = 11, EQUAL = 12, MINUS = 13, PLUS = 14, STAR = 15, SLASH = 16, 
    HASH = 17, QUEST_MARK = 18, EXCLA_MARK = 19, PERCENT = 20, DOLLAR = 21, 
    AMPERSAND = 22, OBJECT = 23, INTERFACE = 24, ENUM = 25, IMPLEMENTS = 26, 
    IMPORT = 27, IF = 28, FOR = 29, BREAK = 30, CONTINUE = 31, RETURN = 32, 
    AND = 33, OR = 34, NOT = 35, IN = 36, INTEGER = 37, FLOAT = 38, BOOL = 39, 
    VARIABLE = 40, TYPE = 41, CONST = 42, STRING = 43, LINE_COMMENT = 44, 
    BLOCK_COMMENT = 45, WS = 46
  };

  enum {
    RuleEntry = 0, RuleInterfaceFile = 1, RuleObjectFile = 2, RuleObjectDeclaration = 3, 
    RuleInterfaceDeclaration = 4, RuleObjectImplements = 5, RuleExplicitVarDecList = 6, 
    RuleExplicitVarDec = 7, RuleImplicitVarDec = 8, RuleFuncDec = 9, RuleFuncCall = 10, 
    RuleFuncImplementation = 11, RuleFuncBody = 12, RuleStatement = 13, 
    RuleExpr_list = 14, RuleExpr = 15, RuleUnary_expr = 16, RuleBinary_expr = 17
  };

  explicit LogosParser(antlr4::TokenStream *input);

  LogosParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~LogosParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class EntryContext;
  class InterfaceFileContext;
  class ObjectFileContext;
  class ObjectDeclarationContext;
  class InterfaceDeclarationContext;
  class ObjectImplementsContext;
  class ExplicitVarDecListContext;
  class ExplicitVarDecContext;
  class ImplicitVarDecContext;
  class FuncDecContext;
  class FuncCallContext;
  class FuncImplementationContext;
  class FuncBodyContext;
  class StatementContext;
  class Expr_listContext;
  class ExprContext;
  class Unary_exprContext;
  class Binary_exprContext; 

  class  EntryContext : public antlr4::ParserRuleContext {
  public:
    EntryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ObjectFileContext *objectFile();
    InterfaceFileContext *interfaceFile();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EntryContext* entry();

  class  InterfaceFileContext : public antlr4::ParserRuleContext {
  public:
    InterfaceFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    InterfaceDeclarationContext *interfaceDeclaration();
    ObjectImplementsContext *objectImplements();
    std::vector<ExplicitVarDecContext *> explicitVarDec();
    ExplicitVarDecContext* explicitVarDec(size_t i);
    std::vector<FuncDecContext *> funcDec();
    FuncDecContext* funcDec(size_t i);
    std::vector<FuncImplementationContext *> funcImplementation();
    FuncImplementationContext* funcImplementation(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InterfaceFileContext* interfaceFile();

  class  ObjectFileContext : public antlr4::ParserRuleContext {
  public:
    ObjectFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ObjectDeclarationContext *objectDeclaration();
    ObjectImplementsContext *objectImplements();
    std::vector<ExplicitVarDecContext *> explicitVarDec();
    ExplicitVarDecContext* explicitVarDec(size_t i);
    std::vector<FuncImplementationContext *> funcImplementation();
    FuncImplementationContext* funcImplementation(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ObjectFileContext* objectFile();

  class  ObjectDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ObjectDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OBJECT();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *TYPE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ObjectDeclarationContext* objectDeclaration();

  class  InterfaceDeclarationContext : public antlr4::ParserRuleContext {
  public:
    InterfaceDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTERFACE();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *TYPE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InterfaceDeclarationContext* interfaceDeclaration();

  class  ObjectImplementsContext : public antlr4::ParserRuleContext {
  public:
    ObjectImplementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPLEMENTS();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *TYPE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ObjectImplementsContext* objectImplements();

  class  ExplicitVarDecListContext : public antlr4::ParserRuleContext {
  public:
    ExplicitVarDecListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExplicitVarDecContext *> explicitVarDec();
    ExplicitVarDecContext* explicitVarDec(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExplicitVarDecListContext* explicitVarDecList();

  class  ExplicitVarDecContext : public antlr4::ParserRuleContext {
  public:
    ExplicitVarDecContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *TYPE();
    antlr4::tree::TerminalNode *EQUAL();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExplicitVarDecContext* explicitVarDec();

  class  ImplicitVarDecContext : public antlr4::ParserRuleContext {
  public:
    ImplicitVarDecContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *EQUAL();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImplicitVarDecContext* implicitVarDec();

  class  FuncDecContext : public antlr4::ParserRuleContext {
  public:
    FuncDecContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *LEFT_PAREN();
    antlr4::tree::TerminalNode *RIGHT_PAREN();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *TYPE();
    ExplicitVarDecListContext *explicitVarDecList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FuncDecContext* funcDec();

  class  FuncCallContext : public antlr4::ParserRuleContext {
  public:
    FuncCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *LEFT_PAREN();
    antlr4::tree::TerminalNode *RIGHT_PAREN();
    std::vector<Expr_listContext *> expr_list();
    Expr_listContext* expr_list(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FuncCallContext* funcCall();

  class  FuncImplementationContext : public antlr4::ParserRuleContext {
  public:
    FuncImplementationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncDecContext *funcDec();
    FuncBodyContext *funcBody();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FuncImplementationContext* funcImplementation();

  class  FuncBodyContext : public antlr4::ParserRuleContext {
  public:
    FuncBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LEFT_BRACE();
    antlr4::tree::TerminalNode *RIGHT_BRACE();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FuncBodyContext* funcBody();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExplicitVarDecContext *explicitVarDec();
    ImplicitVarDecContext *implicitVarDec();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StatementContext* statement();

  class  Expr_listContext : public antlr4::ParserRuleContext {
  public:
    Expr_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_listContext* expr_list();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Unary_exprContext *unary_expr();
    Binary_exprContext *binary_expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExprContext* expr();

  class  Unary_exprContext : public antlr4::ParserRuleContext {
  public:
    Unary_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *FLOAT();
    antlr4::tree::TerminalNode *BOOL();
    antlr4::tree::TerminalNode *STRING();
    FuncCallContext *funcCall();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Unary_exprContext* unary_expr();

  class  Binary_exprContext : public antlr4::ParserRuleContext {
  public:
    Binary_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Unary_exprContext *unary_expr();
    ExprContext *expr();
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *SLASH();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Binary_exprContext* binary_expr();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

