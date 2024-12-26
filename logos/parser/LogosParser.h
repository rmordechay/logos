
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosParser : public antlr4::Parser {
public:
  enum {
    DOUBLE_EQUAL = 1, GREATER_EQUAL_THAN = 2, LESS_EQUAL_THAN = 3, LEFT_PAREN = 4, 
    RIGHT_PAREN = 5, LEFT_BRACE = 6, RIGHT_BRACE = 7, LEFT_BRACKET = 8, 
    RIGHT_BRACKET = 9, LEFT_ANGLE = 10, RIGHT_ANGLE = 11, COMMA = 12, DOUBLE_DOT = 13, 
    DOT = 14, COLON = 15, EQUAL = 16, MINUS = 17, PLUS = 18, STAR = 19, 
    SLASH = 20, HASH = 21, QUEST_MARK = 22, EXCLA_MARK = 23, PERCENT = 24, 
    DOLLAR = 25, AMPERSAND = 26, OBJECT = 27, INTERFACE = 28, ENUM = 29, 
    IMPLEMENTS = 30, IMPORT = 31, IF = 32, ELSE = 33, FOR = 34, BREAK = 35, 
    CONTINUE = 36, RETURN = 37, AND = 38, OR = 39, NOT = 40, IN = 41, INTEGER = 42, 
    FLOAT = 43, BOOL = 44, CONST = 45, TYPE = 46, VARIABLE = 47, STRING = 48, 
    LINE_COMMENT = 49, BLOCK_COMMENT = 50, WS = 51
  };

  enum {
    RuleLogosFile = 0, RuleMainFile = 1, RuleInterfaceFile = 2, RuleObjectFile = 3, 
    RuleImportStatement = 4, RuleObjectDeclaration = 5, RuleInterfaceDeclaration = 6, 
    RuleObjectImplements = 7, RuleFuncDec = 8, RuleFuncImplementation = 9, 
    RuleFuncBody = 10, RuleFuncCall = 11, RuleConstructorCall = 12, RuleExplicitVarDecList = 13, 
    RuleExplicitVarDec = 14, RuleImplicitVarDec = 15, RuleParamCall = 16, 
    RuleParamCallList = 17, RuleStatement = 18, RuleEnumDeclaration = 19, 
    RuleEnumField = 20, RuleStatemets_block = 21, RuleExprList = 22, RuleExpr = 23, 
    RuleBinaryExpr = 24, RuleBoolExpr = 25, RuleUnaryExpr = 26, RuleSelection = 27, 
    RuleIfStatement = 28, RuleElseStatement = 29, RulePatterMatching = 30, 
    RulePattern = 31, RuleLoopStatemet = 32, RuleRange = 33, RuleControlFlowStatement = 34
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
  class ImportStatementContext;
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
  class EnumDeclarationContext;
  class EnumFieldContext;
  class Statemets_blockContext;
  class ExprListContext;
  class ExprContext;
  class BinaryExprContext;
  class BoolExprContext;
  class UnaryExprContext;
  class SelectionContext;
  class IfStatementContext;
  class ElseStatementContext;
  class PatterMatchingContext;
  class PatternContext;
  class LoopStatemetContext;
  class RangeContext;
  class ControlFlowStatementContext; 

  class  LogosFileContext : public antlr4::ParserRuleContext {
  public:
    LogosFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MainFileContext *mainFile();
    ObjectFileContext *objectFile();
    InterfaceFileContext *interfaceFile();
    ImportStatementContext *importStatement();

   
  };

  LogosFileContext* logosFile();

  class  MainFileContext : public antlr4::ParserRuleContext {
  public:
    MainFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    ExplicitVarDecContext *explicitVarDec();
    ImplicitVarDecContext *implicitVarDec();
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

  class  ImportStatementContext : public antlr4::ParserRuleContext {
  public:
    ImportStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    antlr4::tree::TerminalNode *LEFT_PAREN();
    antlr4::tree::TerminalNode *RIGHT_PAREN();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);

   
  };

  ImportStatementContext* importStatement();

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
    EnumDeclarationContext *enumDeclaration();

   
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
    LoopStatemetContext *loopStatemet();
    ControlFlowStatementContext *controlFlowStatement();
    EnumDeclarationContext *enumDeclaration();
    ExprContext *expr();

   
  };

  StatementContext* statement();

  class  EnumDeclarationContext : public antlr4::ParserRuleContext {
  public:
    EnumDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ENUM();
    antlr4::tree::TerminalNode *TYPE();
    antlr4::tree::TerminalNode *LEFT_BRACE();
    antlr4::tree::TerminalNode *RIGHT_BRACE();
    std::vector<EnumFieldContext *> enumField();
    EnumFieldContext* enumField(size_t i);

   
  };

  EnumDeclarationContext* enumDeclaration();

  class  EnumFieldContext : public antlr4::ParserRuleContext {
  public:
    EnumFieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONST();
    antlr4::tree::TerminalNode *EQUAL();
    antlr4::tree::TerminalNode *STRING();

   
  };

  EnumFieldContext* enumField();

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

  class  ExprListContext : public antlr4::ParserRuleContext {
  public:
    ExprListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

   
  };

  ExprListContext* exprList();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BinaryExprContext *binaryExpr();
    UnaryExprContext *unaryExpr();
    BoolExprContext *boolExpr();
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

  class  BoolExprContext : public antlr4::ParserRuleContext {
  public:
    BoolExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UnaryExprContext *unaryExpr();
    ExprContext *expr();
    antlr4::tree::TerminalNode *DOUBLE_EQUAL();
    antlr4::tree::TerminalNode *RIGHT_BRACKET();
    antlr4::tree::TerminalNode *LEFT_BRACKET();
    antlr4::tree::TerminalNode *GREATER_EQUAL_THAN();
    antlr4::tree::TerminalNode *LESS_EQUAL_THAN();

   
  };

  BoolExprContext* boolExpr();

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

  class  LoopStatemetContext : public antlr4::ParserRuleContext {
  public:
    LoopStatemetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FOR();
    Statemets_blockContext *statemets_block();
    ExprContext *expr();
    ExprListContext *exprList();
    antlr4::tree::TerminalNode *IN();
    RangeContext *range();

   
  };

  LoopStatemetContext* loopStatemet();

  class  RangeContext : public antlr4::ParserRuleContext {
  public:
    RangeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DOUBLE_DOT();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);

   
  };

  RangeContext* range();

  class  ControlFlowStatementContext : public antlr4::ParserRuleContext {
  public:
    ControlFlowStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BREAK();
    ExprContext *expr();
    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *CONTINUE();
    antlr4::tree::TerminalNode *RETURN();

   
  };

  ControlFlowStatementContext* controlFlowStatement();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

