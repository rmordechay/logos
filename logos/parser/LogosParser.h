
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
    IMPORT = 27, IF = 28, ELSE = 29, FOR = 30, BREAK = 31, CONTINUE = 32, 
    RETURN = 33, AND = 34, OR = 35, NOT = 36, IN = 37, INTEGER = 38, FLOAT = 39, 
    BOOL = 40, VARIABLE = 41, TYPE = 42, CONST = 43, STRING = 44, LINE_COMMENT = 45, 
    BLOCK_COMMENT = 46, WS = 47
  };

  enum {
    RuleLogosFile = 0, RuleMainFile = 1, RuleInterfaceFile = 2, RuleObjectFile = 3, 
    RuleObjectDeclaration = 4, RuleInterfaceDeclaration = 5, RuleObjectImplements = 6, 
    RuleFuncDec = 7, RuleFuncImplementation = 8, RuleFuncBody = 9, RuleFuncCall = 10, 
    RuleConstructorCall = 11, RuleExplicitVarDecList = 12, RuleExplicitVarDec = 13, 
    RuleImplicitVarDec = 14, RuleParamCall = 15, RuleParamCallList = 16, 
    RuleStatement = 17, RuleStatemets_block = 18, RuleExpr = 19, RuleBinaryExpr = 20, 
    RuleUnaryExpr = 21, RuleSelection = 22, RuleIfStatement = 23, RuleElseStatement = 24, 
    RulePatterMatching = 25, RulePattern = 26
  };

  explicit LogosParser(antlr4::TokenStream *input);

  LogosParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~LogosParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class LogosFileContext;
  class MainFileContext;
  class InterfaceFileContext;
  class ObjectFileContext;
  class ObjectDeclarationContext;
  class InterfaceDeclarationContext;
  class ObjectImplementsContext;
  class FuncDecContext;
  class FuncImplementationContext;
  class FuncBodyContext;
  class FuncCallContext;
  class ConstructorCallContext;
  class ExplicitVarDecListContext;
  class ExplicitVarDecContext;
  class ImplicitVarDecContext;
  class ParamCallContext;
  class ParamCallListContext;
  class StatementContext;
  class Statemets_blockContext;
  class ExprContext;
  class BinaryExprContext;
  class UnaryExprContext;
  class SelectionContext;
  class IfStatementContext;
  class ElseStatementContext;
  class PatterMatchingContext;
  class PatternContext; 

  class  LogosFileContext : public antlr4::ParserRuleContext {
  public:
    LogosFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MainFileContext *mainFile();
    ObjectFileContext *objectFile();
    InterfaceFileContext *interfaceFile();

   
  };

  LogosFileContext* logosFile();

  class  MainFileContext : public antlr4::ParserRuleContext {
  public:
    MainFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<FuncImplementationContext *> funcImplementation();
    FuncImplementationContext* funcImplementation(size_t i);

   
  };

  MainFileContext* mainFile();

  class  InterfaceFileContext : public antlr4::ParserRuleContext {
  public:
    InterfaceFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    InterfaceDeclarationContext *interfaceDeclaration();
    antlr4::tree::TerminalNode *EOF();
    ObjectImplementsContext *objectImplements();
    std::vector<ExplicitVarDecContext *> explicitVarDec();
    ExplicitVarDecContext* explicitVarDec(size_t i);
    std::vector<FuncDecContext *> funcDec();
    FuncDecContext* funcDec(size_t i);
    std::vector<FuncImplementationContext *> funcImplementation();
    FuncImplementationContext* funcImplementation(size_t i);

   
  };

  InterfaceFileContext* interfaceFile();

  class  ObjectFileContext : public antlr4::ParserRuleContext {
  public:
    ObjectFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ObjectDeclarationContext *objectDeclaration();
    antlr4::tree::TerminalNode *EOF();
    ObjectImplementsContext *objectImplements();
    std::vector<ExplicitVarDecContext *> explicitVarDec();
    ExplicitVarDecContext* explicitVarDec(size_t i);
    std::vector<FuncImplementationContext *> funcImplementation();
    FuncImplementationContext* funcImplementation(size_t i);

   
  };

  ObjectFileContext* objectFile();

  class  ObjectDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ObjectDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OBJECT();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *TYPE();

   
  };

  ObjectDeclarationContext* objectDeclaration();

  class  InterfaceDeclarationContext : public antlr4::ParserRuleContext {
  public:
    InterfaceDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTERFACE();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *TYPE();

   
  };

  InterfaceDeclarationContext* interfaceDeclaration();

  class  ObjectImplementsContext : public antlr4::ParserRuleContext {
  public:
    ObjectImplementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPLEMENTS();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *TYPE();

   
  };

  ObjectImplementsContext* objectImplements();

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

   
  };

  FuncDecContext* funcDec();

  class  FuncImplementationContext : public antlr4::ParserRuleContext {
  public:
    FuncImplementationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncDecContext *funcDec();
    FuncBodyContext *funcBody();

   
  };

  FuncImplementationContext* funcImplementation();

  class  FuncBodyContext : public antlr4::ParserRuleContext {
  public:
    FuncBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Statemets_blockContext *statemets_block();

   
  };

  FuncBodyContext* funcBody();

  class  FuncCallContext : public antlr4::ParserRuleContext {
  public:
    FuncCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *LEFT_PAREN();
    antlr4::tree::TerminalNode *RIGHT_PAREN();
    std::vector<ParamCallListContext *> paramCallList();
    ParamCallListContext* paramCallList(size_t i);

   
  };

  FuncCallContext* funcCall();

  class  ConstructorCallContext : public antlr4::ParserRuleContext {
  public:
    ConstructorCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TYPE();
    antlr4::tree::TerminalNode *LEFT_PAREN();
    antlr4::tree::TerminalNode *RIGHT_PAREN();
    std::vector<ParamCallListContext *> paramCallList();
    ParamCallListContext* paramCallList(size_t i);

   
  };

  ConstructorCallContext* constructorCall();

  class  ExplicitVarDecListContext : public antlr4::ParserRuleContext {
  public:
    ExplicitVarDecListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExplicitVarDecContext *> explicitVarDec();
    ExplicitVarDecContext* explicitVarDec(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

   
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

   
  };

  ExplicitVarDecContext* explicitVarDec();

  class  ImplicitVarDecContext : public antlr4::ParserRuleContext {
  public:
    ImplicitVarDecContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *EQUAL();
    ExprContext *expr();

   
  };

  ImplicitVarDecContext* implicitVarDec();

  class  ParamCallContext : public antlr4::ParserRuleContext {
  public:
    ParamCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *EQUAL();

   
  };

  ParamCallContext* paramCall();

  class  ParamCallListContext : public antlr4::ParserRuleContext {
  public:
    ParamCallListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ParamCallContext *> paramCall();
    ParamCallContext* paramCall(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

   
  };

  ParamCallListContext* paramCallList();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExplicitVarDecContext *explicitVarDec();
    ImplicitVarDecContext *implicitVarDec();
    IfStatementContext *ifStatement();
    ExprContext *expr();

   
  };

  StatementContext* statement();

  class  Statemets_blockContext : public antlr4::ParserRuleContext {
  public:
    Statemets_blockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LEFT_BRACE();
    antlr4::tree::TerminalNode *RIGHT_BRACE();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

   
  };

  Statemets_blockContext* statemets_block();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BinaryExprContext *binaryExpr();
    UnaryExprContext *unaryExpr();
    SelectionContext *selection();

   
  };

  ExprContext* expr();

  class  BinaryExprContext : public antlr4::ParserRuleContext {
  public:
    BinaryExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UnaryExprContext *unaryExpr();
    ExprContext *expr();
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *SLASH();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

   
  };

  BinaryExprContext* binaryExpr();

  class  UnaryExprContext : public antlr4::ParserRuleContext {
  public:
    UnaryExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncCallContext *funcCall();
    ConstructorCallContext *constructorCall();
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *FLOAT();
    antlr4::tree::TerminalNode *BOOL();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *VARIABLE();

   
  };

  UnaryExprContext* unaryExpr();

  class  SelectionContext : public antlr4::ParserRuleContext {
  public:
    SelectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<UnaryExprContext *> unaryExpr();
    UnaryExprContext* unaryExpr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DOT();
    antlr4::tree::TerminalNode* DOT(size_t i);

   
  };

  SelectionContext* selection();

  class  IfStatementContext : public antlr4::ParserRuleContext {
  public:
    IfStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    ExprContext *expr();
    Statemets_blockContext *statemets_block();
    ElseStatementContext *elseStatement();
    PatterMatchingContext *patterMatching();

   
  };

  IfStatementContext* ifStatement();

  class  ElseStatementContext : public antlr4::ParserRuleContext {
  public:
    ElseStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ELSE();
    antlr4::tree::TerminalNode* ELSE(size_t i);
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<Statemets_blockContext *> statemets_block();
    Statemets_blockContext* statemets_block(size_t i);

   
  };

  ElseStatementContext* elseStatement();

  class  PatterMatchingContext : public antlr4::ParserRuleContext {
  public:
    PatterMatchingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *LEFT_BRACE();
    antlr4::tree::TerminalNode *RIGHT_BRACE();
    ExprContext *expr();
    std::vector<PatternContext *> pattern();
    PatternContext* pattern(size_t i);
    antlr4::tree::TerminalNode *ELSE();
    antlr4::tree::TerminalNode *COLON();
    Statemets_blockContext *statemets_block();

   
  };

  PatterMatchingContext* patterMatching();

  class  PatternContext : public antlr4::ParserRuleContext {
  public:
    PatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();
    antlr4::tree::TerminalNode *COLON();
    Statemets_blockContext *statemets_block();

   
  };

  PatternContext* pattern();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

