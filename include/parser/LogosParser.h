
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, DOUBLE_EQUAL = 2, NOT_EQUAL = 3, GE = 4, LE = 5, LPAREN = 6, 
    RPAREN = 7, LBRACE = 8, RBRACE = 9, LBRACK = 10, RBRACK = 11, CAST = 12, 
    LANGLE = 13, RANGLE = 14, COMMA = 15, DOUBLE_DOT = 16, DOT = 17, COLON = 18, 
    EQUAL = 19, MINUS = 20, PLUS = 21, STAR = 22, SLASH = 23, HASH = 24, 
    QUEST_MARK = 25, EXCLA_MARK = 26, PERCENT = 27, DOLLAR = 28, AMPERSAND = 29, 
    OBJECT = 30, SELF_INSTANCE = 31, SELF_CLASS = 32, INTERFACE = 33, ENUM = 34, 
    VEC = 35, VEC2 = 36, VEC3 = 37, VEC4 = 38, IMPLEMENTS = 39, IMPORT = 40, 
    IF = 41, ELSE = 42, FOR = 43, BREAK = 44, CONTINUE = 45, RETURN = 46, 
    AND = 47, OR = 48, NOT = 49, IN = 50, INTEGER = 51, FLOAT = 52, BOOL = 53, 
    NULL_ = 54, CONST = 55, TYPE = 56, VARIABLE = 57, STRING = 58, LINE_COMMENT = 59, 
    BLOCK_COMMENT = 60, WS = 61
  };

  enum {
    RuleLogosFile = 0, RuleLogosEnvFile = 1, RuleAppEnvRequire = 2, RuleMainFile = 3, 
    RuleObjectFile = 4, RuleInterfaceFile = 5, RuleObjectDeclaration = 6, 
    RuleInterfaceDeclaration = 7, RuleObjectImplements = 8, RuleFuncSignature = 9, 
    RuleFuncImplementation = 10, RuleFuncBody = 11, RuleParamList = 12, 
    RuleStatement = 13, RuleStatementsBlock = 14, RuleAssignment = 15, RuleExplicitVarDec = 16, 
    RuleImplicitVarDec = 17, RuleIfStatement = 18, RuleElseIfStatement = 19, 
    RuleElseStatement = 20, RulePatternMatching = 21, RulePattern = 22, 
    RuleLoopStatement = 23, RuleBreakStmt = 24, RuleReturnStatement = 25, 
    RuleEnumDeclaration = 26, RuleEnumField = 27, RuleExpr = 28, RuleUnaryExpr = 29, 
    RuleArray = 30, RuleMap = 31, RuleFuncCall = 32, RuleConstructor = 33, 
    RuleFuncArgList = 34, RuleFuncArg = 35, RuleConstant = 36, RuleArrayIndex = 37, 
    RuleSelection = 38, RuleFirstSelectionElement = 39, RuleInnerSelectionElement = 40, 
    RuleRange = 41, RuleType = 42, RuleVector = 43
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
  class LogosEnvFileContext;
  class AppEnvRequireContext;
  class MainFileContext;
  class ObjectFileContext;
  class InterfaceFileContext;
  class ObjectDeclarationContext;
  class InterfaceDeclarationContext;
  class ObjectImplementsContext;
  class FuncSignatureContext;
  class FuncImplementationContext;
  class FuncBodyContext;
  class ParamListContext;
  class StatementContext;
  class StatementsBlockContext;
  class AssignmentContext;
  class ExplicitVarDecContext;
  class ImplicitVarDecContext;
  class IfStatementContext;
  class ElseIfStatementContext;
  class ElseStatementContext;
  class PatternMatchingContext;
  class PatternContext;
  class LoopStatementContext;
  class BreakStmtContext;
  class ReturnStatementContext;
  class EnumDeclarationContext;
  class EnumFieldContext;
  class ExprContext;
  class UnaryExprContext;
  class ArrayContext;
  class MapContext;
  class FuncCallContext;
  class ConstructorContext;
  class FuncArgListContext;
  class FuncArgContext;
  class ConstantContext;
  class ArrayIndexContext;
  class SelectionContext;
  class FirstSelectionElementContext;
  class InnerSelectionElementContext;
  class RangeContext;
  class TypeContext;
  class VectorContext; 

  class  LogosFileContext : public antlr4::ParserRuleContext {
  public:
    LogosFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MainFileContext *mainFile();
    ObjectFileContext *objectFile();
    InterfaceFileContext *interfaceFile();

   
  };

  LogosFileContext* logosFile();

  class  LogosEnvFileContext : public antlr4::ParserRuleContext {
  public:
    LogosEnvFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ImplicitVarDecContext *> implicitVarDec();
    ImplicitVarDecContext* implicitVarDec(size_t i);
    std::vector<ExplicitVarDecContext *> explicitVarDec();
    ExplicitVarDecContext* explicitVarDec(size_t i);

   
  };

  LogosEnvFileContext* logosEnvFile();

  class  AppEnvRequireContext : public antlr4::ParserRuleContext {
  public:
    AppEnvRequireContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> VARIABLE();
    antlr4::tree::TerminalNode* VARIABLE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COLON();
    antlr4::tree::TerminalNode* COLON(size_t i);
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);

   
  };

  AppEnvRequireContext* appEnvRequire();

  class  MainFileContext : public antlr4::ParserRuleContext {
  public:
    MainFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<EnumDeclarationContext *> enumDeclaration();
    EnumDeclarationContext* enumDeclaration(size_t i);
    std::vector<FuncImplementationContext *> funcImplementation();
    FuncImplementationContext* funcImplementation(size_t i);

   
  };

  MainFileContext* mainFile();

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

  class  InterfaceFileContext : public antlr4::ParserRuleContext {
  public:
    InterfaceFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    InterfaceDeclarationContext *interfaceDeclaration();
    antlr4::tree::TerminalNode *EOF();
    std::vector<ExplicitVarDecContext *> explicitVarDec();
    ExplicitVarDecContext* explicitVarDec(size_t i);
    std::vector<FuncSignatureContext *> funcSignature();
    FuncSignatureContext* funcSignature(size_t i);
    std::vector<FuncImplementationContext *> funcImplementation();
    FuncImplementationContext* funcImplementation(size_t i);

   
  };

  InterfaceFileContext* interfaceFile();

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
    std::vector<antlr4::tree::TerminalNode *> TYPE();
    antlr4::tree::TerminalNode* TYPE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

   
  };

  ObjectImplementsContext* objectImplements();

  class  FuncSignatureContext : public antlr4::ParserRuleContext {
  public:
    FuncSignatureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    ParamListContext *paramList();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();

   
  };

  FuncSignatureContext* funcSignature();

  class  FuncImplementationContext : public antlr4::ParserRuleContext {
  public:
    FuncImplementationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncSignatureContext *funcSignature();
    FuncBodyContext *funcBody();

   
  };

  FuncImplementationContext* funcImplementation();

  class  FuncBodyContext : public antlr4::ParserRuleContext {
  public:
    FuncBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementsBlockContext *statementsBlock();

   
  };

  FuncBodyContext* funcBody();

  class  ParamListContext : public antlr4::ParserRuleContext {
  public:
    ParamListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExplicitVarDecContext *> explicitVarDec();
    ExplicitVarDecContext* explicitVarDec(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

   
  };

  ParamListContext* paramList();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssignmentContext *assignment();
    ExplicitVarDecContext *explicitVarDec();
    ImplicitVarDecContext *implicitVarDec();
    IfStatementContext *ifStatement();
    PatternMatchingContext *patternMatching();
    LoopStatementContext *loopStatement();
    antlr4::tree::TerminalNode *CONTINUE();
    BreakStmtContext *breakStmt();
    ReturnStatementContext *returnStatement();
    EnumDeclarationContext *enumDeclaration();
    FuncCallContext *funcCall();
    SelectionContext *selection();

   
  };

  StatementContext* statement();

  class  StatementsBlockContext : public antlr4::ParserRuleContext {
  public:
    StatementsBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

   
  };

  StatementsBlockContext* statementsBlock();

  class  AssignmentContext : public antlr4::ParserRuleContext {
  public:
    AssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *EQUAL();
    ExprContext *expr();
    antlr4::tree::TerminalNode *VARIABLE();
    ArrayIndexContext *arrayIndex();
    SelectionContext *selection();

   
  };

  AssignmentContext* assignment();

  class  ExplicitVarDecContext : public antlr4::ParserRuleContext {
  public:
    ExplicitVarDecContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();
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
    antlr4::tree::TerminalNode *QUEST_MARK();

   
  };

  ImplicitVarDecContext* implicitVarDec();

  class  IfStatementContext : public antlr4::ParserRuleContext {
  public:
    IfStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    ExprContext *expr();
    StatementsBlockContext *statementsBlock();
    std::vector<ElseIfStatementContext *> elseIfStatement();
    ElseIfStatementContext* elseIfStatement(size_t i);
    ElseStatementContext *elseStatement();

   
  };

  IfStatementContext* ifStatement();

  class  ElseIfStatementContext : public antlr4::ParserRuleContext {
  public:
    ElseIfStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ELSE();
    ExprContext *expr();
    StatementsBlockContext *statementsBlock();

   
  };

  ElseIfStatementContext* elseIfStatement();

  class  ElseStatementContext : public antlr4::ParserRuleContext {
  public:
    ElseStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ELSE();
    StatementsBlockContext *statementsBlock();

   
  };

  ElseStatementContext* elseStatement();

  class  PatternMatchingContext : public antlr4::ParserRuleContext {
  public:
    PatternMatchingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    ExprContext *expr();
    std::vector<PatternContext *> pattern();
    PatternContext* pattern(size_t i);
    antlr4::tree::TerminalNode *ELSE();
    antlr4::tree::TerminalNode *COLON();
    StatementsBlockContext *statementsBlock();

   
  };

  PatternMatchingContext* patternMatching();

  class  PatternContext : public antlr4::ParserRuleContext {
  public:
    PatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();
    antlr4::tree::TerminalNode *COLON();
    StatementsBlockContext *statementsBlock();

   
  };

  PatternContext* pattern();

  class  LoopStatementContext : public antlr4::ParserRuleContext {
  public:
    LogosParser::RangeContext *iterableRange = nullptr;
    LogosParser::UnaryExprContext *iterableExpr = nullptr;
    LoopStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FOR();
    std::vector<antlr4::tree::TerminalNode *> VARIABLE();
    antlr4::tree::TerminalNode* VARIABLE(size_t i);
    antlr4::tree::TerminalNode *IN();
    StatementsBlockContext *statementsBlock();
    RangeContext *range();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    UnaryExprContext *unaryExpr();

   
  };

  LoopStatementContext* loopStatement();

  class  BreakStmtContext : public antlr4::ParserRuleContext {
  public:
    BreakStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BREAK();

   
  };

  BreakStmtContext* breakStmt();

  class  ReturnStatementContext : public antlr4::ParserRuleContext {
  public:
    ReturnStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RETURN();
    ExprContext *expr();

   
  };

  ReturnStatementContext* returnStatement();

  class  EnumDeclarationContext : public antlr4::ParserRuleContext {
  public:
    EnumDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ENUM();
    antlr4::tree::TerminalNode *TYPE();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
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

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    LogosParser::ExprContext *left = nullptr;
    LogosParser::TypeContext *cast = nullptr;
    antlr4::Token *op = nullptr;
    LogosParser::ExprContext *right = nullptr;
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UnaryExprContext *unaryExpr();
    antlr4::tree::TerminalNode *CAST();
    TypeContext *type();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *SLASH();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *DOUBLE_EQUAL();
    antlr4::tree::TerminalNode *NOT_EQUAL();
    antlr4::tree::TerminalNode *LANGLE();
    antlr4::tree::TerminalNode *RANGLE();
    antlr4::tree::TerminalNode *GE();
    antlr4::tree::TerminalNode *LE();

   
  };

  ExprContext* expr();
  ExprContext* expr(int precedence);
  class  UnaryExprContext : public antlr4::ParserRuleContext {
  public:
    UnaryExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *CONST();
    antlr4::tree::TerminalNode *SELF_INSTANCE();
    antlr4::tree::TerminalNode *SELF_CLASS();
    antlr4::tree::TerminalNode *NULL_();
    FuncCallContext *funcCall();
    ConstructorContext *constructor();
    ConstantContext *constant();
    ArrayContext *array();
    MapContext *map();
    ArrayIndexContext *arrayIndex();
    SelectionContext *selection();

   
  };

  UnaryExprContext* unaryExpr();

  class  ArrayContext : public antlr4::ParserRuleContext {
  public:
    ArrayContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACK();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *RBRACK();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

   
  };

  ArrayContext* array();

  class  MapContext : public antlr4::ParserRuleContext {
  public:
    MapContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COLON();
    antlr4::tree::TerminalNode* COLON(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

   
  };

  MapContext* map();

  class  FuncCallContext : public antlr4::ParserRuleContext {
  public:
    FuncCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    FuncArgListContext *funcArgList();

   
  };

  FuncCallContext* funcCall();

  class  ConstructorContext : public antlr4::ParserRuleContext {
  public:
    ConstructorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TYPE();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    FuncArgListContext *funcArgList();

   
  };

  ConstructorContext* constructor();

  class  FuncArgListContext : public antlr4::ParserRuleContext {
  public:
    FuncArgListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FuncArgContext *> funcArg();
    FuncArgContext* funcArg(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

   
  };

  FuncArgListContext* funcArgList();

  class  FuncArgContext : public antlr4::ParserRuleContext {
  public:
    FuncArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *EQUAL();

   
  };

  FuncArgContext* funcArg();

  class  ConstantContext : public antlr4::ParserRuleContext {
  public:
    ConstantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *FLOAT();
    antlr4::tree::TerminalNode *BOOL();
    antlr4::tree::TerminalNode *STRING();

   
  };

  ConstantContext* constant();

  class  ArrayIndexContext : public antlr4::ParserRuleContext {
  public:
    ArrayIndexContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncCallContext *funcCall();
    antlr4::tree::TerminalNode *VARIABLE();
    std::vector<antlr4::tree::TerminalNode *> LBRACK();
    antlr4::tree::TerminalNode* LBRACK(size_t i);
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RBRACK();
    antlr4::tree::TerminalNode* RBRACK(size_t i);

   
  };

  ArrayIndexContext* arrayIndex();

  class  SelectionContext : public antlr4::ParserRuleContext {
  public:
    SelectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FirstSelectionElementContext *firstSelectionElement();
    std::vector<antlr4::tree::TerminalNode *> DOT();
    antlr4::tree::TerminalNode* DOT(size_t i);
    std::vector<InnerSelectionElementContext *> innerSelectionElement();
    InnerSelectionElementContext* innerSelectionElement(size_t i);

   
  };

  SelectionContext* selection();

  class  FirstSelectionElementContext : public antlr4::ParserRuleContext {
  public:
    FirstSelectionElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *TYPE();
    antlr4::tree::TerminalNode *SELF_CLASS();
    antlr4::tree::TerminalNode *SELF_INSTANCE();
    FuncCallContext *funcCall();
    ConstructorContext *constructor();
    ArrayIndexContext *arrayIndex();

   
  };

  FirstSelectionElementContext* firstSelectionElement();

  class  InnerSelectionElementContext : public antlr4::ParserRuleContext {
  public:
    InnerSelectionElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    FuncCallContext *funcCall();
    ArrayIndexContext *arrayIndex();

   
  };

  InnerSelectionElementContext* innerSelectionElement();

  class  RangeContext : public antlr4::ParserRuleContext {
  public:
    LogosParser::ExprContext *start = nullptr;
    LogosParser::ExprContext *end = nullptr;
    RangeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DOUBLE_DOT();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);

   
  };

  RangeContext* range();

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SELF_CLASS();
    antlr4::tree::TerminalNode *TYPE();
    antlr4::tree::TerminalNode *QUEST_MARK();
    std::vector<antlr4::tree::TerminalNode *> LBRACK();
    antlr4::tree::TerminalNode* LBRACK(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RBRACK();
    antlr4::tree::TerminalNode* RBRACK(size_t i);
    std::vector<antlr4::tree::TerminalNode *> INTEGER();
    antlr4::tree::TerminalNode* INTEGER(size_t i);
    antlr4::tree::TerminalNode *LBRACE();
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *RBRACE();

   
  };

  TypeContext* type();

  class  VectorContext : public antlr4::ParserRuleContext {
  public:
    VectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VEC();
    antlr4::tree::TerminalNode *VEC2();
    antlr4::tree::TerminalNode *VEC3();
    antlr4::tree::TerminalNode *VEC4();

   
  };

  VectorContext* vector();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool exprSempred(ExprContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

