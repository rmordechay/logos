
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, DOUBLE_EQUAL = 7, 
    NOT_EQUAL = 8, GE = 9, LE = 10, LPAREN = 11, RPAREN = 12, LBRACE = 13, 
    RBRACE = 14, LBRACK = 15, RBRACK = 16, LANGLE = 17, RANGLE = 18, COMMA = 19, 
    ARROW = 20, TRIPLE_DOT = 21, DOUBLE_DOT = 22, WALRUS = 23, EQUAL_PLUS = 24, 
    EQUAL_MINUS = 25, EQUAL_STAR = 26, EQUAL_SLASH = 27, EQUAL_PERCENT = 28, 
    EQUAL_AMPERSAND = 29, EQUAL_PIPE = 30, EQUAL_CARET = 31, EQUAL_DOUBLE_RANGLE = 32, 
    EQUAL_DOUBLE_LANGLE = 33, INC = 34, DEC = 35, DOT = 36, COLON = 37, 
    EQUAL = 38, PLUS = 39, MINUS = 40, STAR = 41, SLASH = 42, HASH = 43, 
    QUEST_MARK = 44, EXCLA_MARK = 45, PERCENT = 46, DOLLAR = 47, AMPERSAND = 48, 
    PIPE = 49, CARET = 50, DOUBLE_RANGLE = 51, DOUBLE_LANGLE = 52, SLIDER = 53, 
    OBJECT = 54, SINGLETON = 55, SELF_INSTANCE = 56, SELF_CLASS = 57, INTERFACE = 58, 
    EXTERN = 59, VISIBILITY = 60, IMPLEMENTS = 61, CONST = 62, ENUM = 63, 
    GO = 64, DEFER = 65, IO = 66, OWNER = 67, VEC2 = 68, VEC3 = 69, VEC4 = 70, 
    IF = 71, WHILE = 72, ELSE = 73, BREAK = 74, CONTINUE = 75, RETURN = 76, 
    FOR = 77, FOR_IS_FIRST = 78, FOR_IS_LAST = 79, FOR_I = 80, AND = 81, 
    OR = 82, NOT = 83, IN = 84, LONG = 85, INTEGER = 86, FLOAT = 87, BOOL = 88, 
    NULL_ = 89, IDENTIFIER = 90, STRING = 91, TAG = 92, LINE_COMMENT = 93, 
    BLOCK_COMMENT = 94, WS = 95
  };

  enum {
    RuleLogosFile = 0, RuleLogosEnvFile = 1, RuleLogosAppFile = 2, RuleMainFile = 3, 
    RuleObjectFile = 4, RuleInterfaceFile = 5, RuleTestFile = 6, RuleInterface = 7, 
    RuleInterfaceBody = 8, RuleObject = 9, RuleObjectBody = 10, RuleField = 11, 
    RuleInterfaceField = 12, RuleImplements = 13, RuleIoPair = 14, RuleGroup = 15, 
    RuleGroupTypesList = 16, RuleGroupTargetList = 17, RuleFuncSignatureHeader = 18, 
    RuleFuncSignature = 19, RuleInterfaceFunc = 20, RuleFunc = 21, RuleLambda = 22, 
    RuleLambdaParams = 23, RuleLambdaParam = 24, RuleMethod = 25, RuleParam = 26, 
    RuleStatement = 27, RuleStatementsBlock = 28, RuleAssignment = 29, RuleExplicitVarDec = 30, 
    RuleImplicitVarDec = 31, RuleIfStatement = 32, RuleElseIfStatement = 33, 
    RuleElseStatement = 34, RulePatternMatching = 35, RulePattern = 36, 
    RuleLoopStatement = 37, RuleRangeLoop = 38, RuleBreakStmt = 39, RuleReturnStatement = 40, 
    RuleIoStatement = 41, RuleEnumDeclaration = 42, RuleEnumField = 43, 
    RuleCoroutine = 44, RuleDeferStmt = 45, RuleExpr = 46, RuleUnaryExpr = 47, 
    RulePrefixExpr = 48, RulePostfixExpr = 49, RuleArrayExpr = 50, RuleHashMap = 51, 
    RuleKeyValue = 52, RuleFuncCall = 53, RuleFuncArgList = 54, RuleFuncArg = 55, 
    RuleInstance = 56, RuleInstanceArgList = 57, RuleInstanceArg = 58, RuleConstant = 59, 
    RuleIterIndex = 60, RuleIndex = 61, RuleSelection = 62, RuleFirstSelectionElement = 63, 
    RuleInnerSelectionElement = 64, RuleForVariable = 65, RuleRange = 66, 
    RuleType = 67, RuleMapType = 68, RuleArraySize = 69, RuleFuncType = 70, 
    RuleVector = 71, RuleExtern = 72, RuleRequireEnvVars = 73, RuleRequirePackages = 74, 
    RuleAssignemntOp = 75, RuleJson = 76, RuleJsonObj = 77, RuleJsonPair = 78, 
    RuleJsonArray = 79
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
  class LogosAppFileContext;
  class MainFileContext;
  class ObjectFileContext;
  class InterfaceFileContext;
  class TestFileContext;
  class InterfaceContext;
  class InterfaceBodyContext;
  class ObjectContext;
  class ObjectBodyContext;
  class FieldContext;
  class InterfaceFieldContext;
  class ImplementsContext;
  class IoPairContext;
  class GroupContext;
  class GroupTypesListContext;
  class GroupTargetListContext;
  class FuncSignatureHeaderContext;
  class FuncSignatureContext;
  class InterfaceFuncContext;
  class FuncContext;
  class LambdaContext;
  class LambdaParamsContext;
  class LambdaParamContext;
  class MethodContext;
  class ParamContext;
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
  class RangeLoopContext;
  class BreakStmtContext;
  class ReturnStatementContext;
  class IoStatementContext;
  class EnumDeclarationContext;
  class EnumFieldContext;
  class CoroutineContext;
  class DeferStmtContext;
  class ExprContext;
  class UnaryExprContext;
  class PrefixExprContext;
  class PostfixExprContext;
  class ArrayExprContext;
  class HashMapContext;
  class KeyValueContext;
  class FuncCallContext;
  class FuncArgListContext;
  class FuncArgContext;
  class InstanceContext;
  class InstanceArgListContext;
  class InstanceArgContext;
  class ConstantContext;
  class IterIndexContext;
  class IndexContext;
  class SelectionContext;
  class FirstSelectionElementContext;
  class InnerSelectionElementContext;
  class ForVariableContext;
  class RangeContext;
  class TypeContext;
  class MapTypeContext;
  class ArraySizeContext;
  class FuncTypeContext;
  class VectorContext;
  class ExternContext;
  class RequireEnvVarsContext;
  class RequirePackagesContext;
  class AssignemntOpContext;
  class JsonContext;
  class JsonObjContext;
  class JsonPairContext;
  class JsonArrayContext; 

  class  LogosFileContext : public antlr4::ParserRuleContext {
  public:
    LogosFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MainFileContext *mainFile();
    ObjectFileContext *objectFile();
    InterfaceFileContext *interfaceFile();
    TestFileContext *testFile();
    ExternContext *extern_();

   
  };

  LogosFileContext* logosFile();

  class  LogosEnvFileContext : public antlr4::ParserRuleContext {
  public:
    LogosEnvFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<ImplicitVarDecContext *> implicitVarDec();
    ImplicitVarDecContext* implicitVarDec(size_t i);
    std::vector<ExplicitVarDecContext *> explicitVarDec();
    ExplicitVarDecContext* explicitVarDec(size_t i);

   
  };

  LogosEnvFileContext* logosEnvFile();

  class  LogosAppFileContext : public antlr4::ParserRuleContext {
  public:
    LogosAppFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> EQUAL();
    antlr4::tree::TerminalNode* EQUAL(size_t i);
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    RequireEnvVarsContext *requireEnvVars();
    RequirePackagesContext *requirePackages();

   
  };

  LogosAppFileContext* logosAppFile();

  class  MainFileContext : public antlr4::ParserRuleContext {
  public:
    MainFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<ObjectContext *> object();
    ObjectContext* object(size_t i);
    std::vector<EnumDeclarationContext *> enumDeclaration();
    EnumDeclarationContext* enumDeclaration(size_t i);
    std::vector<InterfaceContext *> interface();
    InterfaceContext* interface(size_t i);
    std::vector<GroupContext *> group();
    GroupContext* group(size_t i);
    std::vector<FuncContext *> func();
    FuncContext* func(size_t i);

   
  };

  MainFileContext* mainFile();

  class  ObjectFileContext : public antlr4::ParserRuleContext {
  public:
    ObjectFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    ObjectBodyContext *objectBody();
    antlr4::tree::TerminalNode *EOF();
    antlr4::tree::TerminalNode *SINGLETON();
    antlr4::tree::TerminalNode *OBJECT();

   
  };

  ObjectFileContext* objectFile();

  class  InterfaceFileContext : public antlr4::ParserRuleContext {
  public:
    InterfaceFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTERFACE();
    antlr4::tree::TerminalNode *IDENTIFIER();
    InterfaceBodyContext *interfaceBody();
    antlr4::tree::TerminalNode *EOF();

   
  };

  InterfaceFileContext* interfaceFile();

  class  TestFileContext : public antlr4::ParserRuleContext {
  public:
    TestFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<FuncContext *> func();
    FuncContext* func(size_t i);

   
  };

  TestFileContext* testFile();

  class  InterfaceContext : public antlr4::ParserRuleContext {
  public:
    InterfaceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTERFACE();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LBRACE();
    InterfaceBodyContext *interfaceBody();
    antlr4::tree::TerminalNode *RBRACE();

   
  };

  InterfaceContext* interface();

  class  InterfaceBodyContext : public antlr4::ParserRuleContext {
  public:
    InterfaceBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ImplementsContext *implements();
    std::vector<InterfaceFieldContext *> interfaceField();
    InterfaceFieldContext* interfaceField(size_t i);
    std::vector<InterfaceFuncContext *> interfaceFunc();
    InterfaceFuncContext* interfaceFunc(size_t i);

   
  };

  InterfaceBodyContext* interfaceBody();

  class  ObjectContext : public antlr4::ParserRuleContext {
  public:
    ObjectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LBRACE();
    ObjectBodyContext *objectBody();
    antlr4::tree::TerminalNode *RBRACE();
    antlr4::tree::TerminalNode *SINGLETON();
    antlr4::tree::TerminalNode *OBJECT();

   
  };

  ObjectContext* object();

  class  ObjectBodyContext : public antlr4::ParserRuleContext {
  public:
    ObjectBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ImplementsContext *implements();
    std::vector<FieldContext *> field();
    FieldContext* field(size_t i);
    std::vector<MethodContext *> method();
    MethodContext* method(size_t i);
    std::vector<IoPairContext *> ioPair();
    IoPairContext* ioPair(size_t i);

   
  };

  ObjectBodyContext* objectBody();

  class  FieldContext : public antlr4::ParserRuleContext {
  public:
    FieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();
    antlr4::tree::TerminalNode *OWNER();
    antlr4::tree::TerminalNode *VISIBILITY();
    antlr4::tree::TerminalNode *CONST();
    antlr4::tree::TerminalNode *EQUAL();
    ExprContext *expr();

   
  };

  FieldContext* field();

  class  InterfaceFieldContext : public antlr4::ParserRuleContext {
  public:
    InterfaceFieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();
    antlr4::tree::TerminalNode *CONST();
    antlr4::tree::TerminalNode *QUEST_MARK();
    antlr4::tree::TerminalNode *EQUAL();
    ExprContext *expr();

   
  };

  InterfaceFieldContext* interfaceField();

  class  ImplementsContext : public antlr4::ParserRuleContext {
  public:
    ImplementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPLEMENTS();
    antlr4::tree::TerminalNode *COLON();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

   
  };

  ImplementsContext* implements();

  class  IoPairContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *opening = nullptr;
    antlr4::Token *closing = nullptr;
    IoPairContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IO();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);

   
  };

  IoPairContext* ioPair();

  class  GroupContext : public antlr4::ParserRuleContext {
  public:
    GroupContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *EQUAL();
    std::vector<antlr4::tree::TerminalNode *> LBRACE();
    antlr4::tree::TerminalNode* LBRACE(size_t i);
    GroupTypesListContext *groupTypesList();
    std::vector<antlr4::tree::TerminalNode *> RBRACE();
    antlr4::tree::TerminalNode* RBRACE(size_t i);
    antlr4::tree::TerminalNode *ARROW();
    GroupTargetListContext *groupTargetList();

   
  };

  GroupContext* group();

  class  GroupTypesListContext : public antlr4::ParserRuleContext {
  public:
    GroupTypesListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

   
  };

  GroupTypesListContext* groupTypesList();

  class  GroupTargetListContext : public antlr4::ParserRuleContext {
  public:
    GroupTargetListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

   
  };

  GroupTargetListContext* groupTargetList();

  class  FuncSignatureHeaderContext : public antlr4::ParserRuleContext {
  public:
    FuncSignatureHeaderContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<ParamContext *> param();
    ParamContext* param(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

   
  };

  FuncSignatureHeaderContext* funcSignatureHeader();

  class  FuncSignatureContext : public antlr4::ParserRuleContext {
  public:
    FuncSignatureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncSignatureHeaderContext *funcSignatureHeader();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();

   
  };

  FuncSignatureContext* funcSignature();

  class  InterfaceFuncContext : public antlr4::ParserRuleContext {
  public:
    InterfaceFuncContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncSignatureHeaderContext *funcSignatureHeader();
    antlr4::tree::TerminalNode *QUEST_MARK();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();
    StatementsBlockContext *statementsBlock();

   
  };

  InterfaceFuncContext* interfaceFunc();

  class  FuncContext : public antlr4::ParserRuleContext {
  public:
    FuncContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncSignatureContext *funcSignature();
    StatementsBlockContext *statementsBlock();

   
  };

  FuncContext* func();

  class  LambdaContext : public antlr4::ParserRuleContext {
  public:
    LogosParser::TypeContext *rt = nullptr;
    LambdaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ARROW();
    StatementsBlockContext *statementsBlock();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    TypeContext *type();
    LambdaParamsContext *lambdaParams();

   
  };

  LambdaContext* lambda();

  class  LambdaParamsContext : public antlr4::ParserRuleContext {
  public:
    LambdaParamsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LambdaParamContext *> lambdaParam();
    LambdaParamContext* lambdaParam(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

   
  };

  LambdaParamsContext* lambdaParams();

  class  LambdaParamContext : public antlr4::ParserRuleContext {
  public:
    LambdaParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();

   
  };

  LambdaParamContext* lambdaParam();

  class  MethodContext : public antlr4::ParserRuleContext {
  public:
    MethodContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncSignatureContext *funcSignature();
    StatementsBlockContext *statementsBlock();
    antlr4::tree::TerminalNode *VISIBILITY();

   
  };

  MethodContext* method();

  class  ParamContext : public antlr4::ParserRuleContext {
  public:
    ParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();
    antlr4::tree::TerminalNode *OWNER();
    antlr4::tree::TerminalNode *TRIPLE_DOT();
    antlr4::tree::TerminalNode *EQUAL();
    ExprContext *expr();

   
  };

  ParamContext* param();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssignmentContext *assignment();
    ReturnStatementContext *returnStatement();
    ExplicitVarDecContext *explicitVarDec();
    ImplicitVarDecContext *implicitVarDec();
    IfStatementContext *ifStatement();
    PatternMatchingContext *patternMatching();
    LoopStatementContext *loopStatement();
    CoroutineContext *coroutine();
    DeferStmtContext *deferStmt();
    BreakStmtContext *breakStmt();
    IoStatementContext *ioStatement();
    ExprContext *expr();
    antlr4::tree::TerminalNode *CONTINUE();

   
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
    AssignemntOpContext *assignemntOp();
    ExprContext *expr();
    antlr4::tree::TerminalNode *IDENTIFIER();
    IterIndexContext *iterIndex();
    SelectionContext *selection();

   
  };

  AssignmentContext* assignment();

  class  ExplicitVarDecContext : public antlr4::ParserRuleContext {
  public:
    ExplicitVarDecContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();
    antlr4::tree::TerminalNode *OWNER();
    antlr4::tree::TerminalNode *CONST();
    antlr4::tree::TerminalNode *EQUAL();
    ExprContext *expr();

   
  };

  ExplicitVarDecContext* explicitVarDec();

  class  ImplicitVarDecContext : public antlr4::ParserRuleContext {
  public:
    ImplicitVarDecContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *EQUAL();
    ExprContext *expr();
    antlr4::tree::TerminalNode *OWNER();
    antlr4::tree::TerminalNode *CONST();
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
    antlr4::tree::TerminalNode *TAG();
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
    LogosParser::ExprContext *whileExpr = nullptr;
    LogosParser::UnaryExprContext *iterableExpr = nullptr;
    LoopStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WHILE();
    StatementsBlockContext *statementsBlock();
    ExprContext *expr();
    antlr4::tree::TerminalNode *FOR();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    antlr4::tree::TerminalNode *IN();
    UnaryExprContext *unaryExpr();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    RangeLoopContext *rangeLoop();

   
  };

  LoopStatementContext* loopStatement();

  class  RangeLoopContext : public antlr4::ParserRuleContext {
  public:
    LogosParser::RangeContext *iterableRange = nullptr;
    RangeLoopContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *IN();
    RangeContext *range();
    ExprContext *expr();

   
  };

  RangeLoopContext* rangeLoop();

  class  BreakStmtContext : public antlr4::ParserRuleContext {
  public:
    BreakStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BREAK();
    antlr4::tree::TerminalNode *TAG();
    antlr4::tree::TerminalNode *IF();

   
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

  class  IoStatementContext : public antlr4::ParserRuleContext {
  public:
    IoStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IO();
    StatementsBlockContext *statementsBlock();
    ImplicitVarDecContext *implicitVarDec();

   
  };

  IoStatementContext* ioStatement();

  class  EnumDeclarationContext : public antlr4::ParserRuleContext {
  public:
    EnumDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ENUM();
    antlr4::tree::TerminalNode *IDENTIFIER();
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
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *EQUAL();
    antlr4::tree::TerminalNode *STRING();

   
  };

  EnumFieldContext* enumField();

  class  CoroutineContext : public antlr4::ParserRuleContext {
  public:
    CoroutineContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GO();
    FuncCallContext *funcCall();
    SelectionContext *selection();

   
  };

  CoroutineContext* coroutine();

  class  DeferStmtContext : public antlr4::ParserRuleContext {
  public:
    DeferStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DEFER();
    FuncCallContext *funcCall();
    SelectionContext *selection();

   
  };

  DeferStmtContext* deferStmt();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    LogosParser::ExprContext *left = nullptr;
    LogosParser::TypeContext *cast = nullptr;
    antlr4::Token *op = nullptr;
    LogosParser::ExprContext *right = nullptr;
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *ARROW();
    TypeContext *type();
    UnaryExprContext *unaryExpr();
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *SLASH();
    antlr4::tree::TerminalNode *PERCENT();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *LANGLE();
    antlr4::tree::TerminalNode *RANGLE();
    antlr4::tree::TerminalNode *GE();
    antlr4::tree::TerminalNode *LE();
    antlr4::tree::TerminalNode *DOUBLE_EQUAL();
    antlr4::tree::TerminalNode *NOT_EQUAL();
    antlr4::tree::TerminalNode *AND();
    antlr4::tree::TerminalNode *OR();
    antlr4::tree::TerminalNode *AMPERSAND();
    antlr4::tree::TerminalNode *CARET();
    antlr4::tree::TerminalNode *PIPE();
    antlr4::tree::TerminalNode *DOUBLE_LANGLE();
    antlr4::tree::TerminalNode *DOUBLE_RANGLE();
    antlr4::tree::TerminalNode *IN();

   
  };

  ExprContext* expr();
  ExprContext* expr(int precedence);
  class  UnaryExprContext : public antlr4::ParserRuleContext {
  public:
    UnaryExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VectorContext *vector();
    FuncCallContext *funcCall();
    PostfixExprContext *postfixExpr();
    LambdaContext *lambda();
    PrefixExprContext *prefixExpr();
    JsonContext *json();
    InstanceContext *instance();
    ConstantContext *constant();
    IterIndexContext *iterIndex();
    SelectionContext *selection();
    ArrayExprContext *arrayExpr();
    HashMapContext *hashMap();
    ForVariableContext *forVariable();
    antlr4::tree::TerminalNode *SELF_INSTANCE();
    antlr4::tree::TerminalNode *SELF_CLASS();
    antlr4::tree::TerminalNode *NULL_();
    antlr4::tree::TerminalNode *IDENTIFIER();

   
  };

  UnaryExprContext* unaryExpr();

  class  PrefixExprContext : public antlr4::ParserRuleContext {
  public:
    PrefixExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();
    antlr4::tree::TerminalNode *NOT();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *SLIDER();

   
  };

  PrefixExprContext* prefixExpr();

  class  PostfixExprContext : public antlr4::ParserRuleContext {
  public:
    PostfixExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INC();
    antlr4::tree::TerminalNode *DEC();
    antlr4::tree::TerminalNode *IDENTIFIER();
    IterIndexContext *iterIndex();
    SelectionContext *selection();
    FuncCallContext *funcCall();
    ConstantContext *constant();

   
  };

  PostfixExprContext* postfixExpr();

  class  ArrayExprContext : public antlr4::ParserRuleContext {
  public:
    ArrayExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACK();
    antlr4::tree::TerminalNode *RBRACK();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *EXCLA_MARK();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

   
  };

  ArrayExprContext* arrayExpr();

  class  HashMapContext : public antlr4::ParserRuleContext {
  public:
    HashMapContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<KeyValueContext *> keyValue();
    KeyValueContext* keyValue(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

   
  };

  HashMapContext* hashMap();

  class  KeyValueContext : public antlr4::ParserRuleContext {
  public:
    LogosParser::ExprContext *key = nullptr;
    LogosParser::ExprContext *value = nullptr;
    KeyValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);

   
  };

  KeyValueContext* keyValue();

  class  FuncCallContext : public antlr4::ParserRuleContext {
  public:
    FuncCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    FuncArgListContext *funcArgList();
    antlr4::tree::TerminalNode *TRIPLE_DOT();
    antlr4::tree::TerminalNode *COMMA();

   
  };

  FuncCallContext* funcCall();

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
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *EQUAL();

   
  };

  FuncArgContext* funcArg();

  class  InstanceContext : public antlr4::ParserRuleContext {
  public:
    InstanceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    InstanceArgListContext *instanceArgList();

   
  };

  InstanceContext* instance();

  class  InstanceArgListContext : public antlr4::ParserRuleContext {
  public:
    InstanceArgListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<InstanceArgContext *> instanceArg();
    InstanceArgContext* instanceArg(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

   
  };

  InstanceArgListContext* instanceArgList();

  class  InstanceArgContext : public antlr4::ParserRuleContext {
  public:
    InstanceArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *EQUAL();
    ExprContext *expr();

   
  };

  InstanceArgContext* instanceArg();

  class  ConstantContext : public antlr4::ParserRuleContext {
  public:
    ConstantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LONG();
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *FLOAT();
    antlr4::tree::TerminalNode *BOOL();
    antlr4::tree::TerminalNode *STRING();

   
  };

  ConstantContext* constant();

  class  IterIndexContext : public antlr4::ParserRuleContext {
  public:
    IterIndexContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncCallContext *funcCall();
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<IndexContext *> index();
    IndexContext* index(size_t i);

   
  };

  IterIndexContext* iterIndex();

  class  IndexContext : public antlr4::ParserRuleContext {
  public:
    LogosParser::ExprContext *from = nullptr;
    LogosParser::ExprContext *to = nullptr;
    IndexContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACK();
    antlr4::tree::TerminalNode *RBRACK();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *COLON();

   
  };

  IndexContext* index();

  class  SelectionContext : public antlr4::ParserRuleContext {
  public:
    SelectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FirstSelectionElementContext *firstSelectionElement();
    std::vector<antlr4::tree::TerminalNode *> QUEST_MARK();
    antlr4::tree::TerminalNode* QUEST_MARK(size_t i);
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
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *SELF_CLASS();
    antlr4::tree::TerminalNode *SELF_INSTANCE();
    FuncCallContext *funcCall();
    InstanceContext *instance();
    IterIndexContext *iterIndex();

   
  };

  FirstSelectionElementContext* firstSelectionElement();

  class  InnerSelectionElementContext : public antlr4::ParserRuleContext {
  public:
    InnerSelectionElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncCallContext *funcCall();
    IterIndexContext *iterIndex();
    antlr4::tree::TerminalNode *IDENTIFIER();

   
  };

  InnerSelectionElementContext* innerSelectionElement();

  class  ForVariableContext : public antlr4::ParserRuleContext {
  public:
    ForVariableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FOR_I();
    antlr4::tree::TerminalNode *FOR_IS_FIRST();
    antlr4::tree::TerminalNode *FOR_IS_LAST();

   
  };

  ForVariableContext* forVariable();

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
    LogosParser::TypeContext *baseType = nullptr;
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *QUEST_MARK();
    antlr4::tree::TerminalNode *SELF_CLASS();
    MapTypeContext *mapType();
    FuncTypeContext *funcType();
    TypeContext *type();
    std::vector<ArraySizeContext *> arraySize();
    ArraySizeContext* arraySize(size_t i);
    antlr4::tree::TerminalNode *EXCLA_MARK();

   
  };

  TypeContext* type();
  TypeContext* type(int precedence);
  class  MapTypeContext : public antlr4::ParserRuleContext {
  public:
    LogosParser::TypeContext *key = nullptr;
    LogosParser::TypeContext *value = nullptr;
    MapTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);

   
  };

  MapTypeContext* mapType();

  class  ArraySizeContext : public antlr4::ParserRuleContext {
  public:
    ArraySizeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACK();
    antlr4::tree::TerminalNode *RBRACK();
    ExprContext *expr();

   
  };

  ArraySizeContext* arraySize();

  class  FuncTypeContext : public antlr4::ParserRuleContext {
  public:
    LogosParser::TypeContext *rt = nullptr;
    FuncTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *COLON();
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

   
  };

  FuncTypeContext* funcType();

  class  VectorContext : public antlr4::ParserRuleContext {
  public:
    VectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *VEC2();
    antlr4::tree::TerminalNode *VEC3();
    antlr4::tree::TerminalNode *VEC4();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

   
  };

  VectorContext* vector();

  class  ExternContext : public antlr4::ParserRuleContext {
  public:
    ExternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EXTERN();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> STRING();
    antlr4::tree::TerminalNode* STRING(size_t i);

   
  };

  ExternContext* extern_();

  class  RequireEnvVarsContext : public antlr4::ParserRuleContext {
  public:
    RequireEnvVarsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COLON();
    antlr4::tree::TerminalNode* COLON(size_t i);
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);

   
  };

  RequireEnvVarsContext* requireEnvVars();

  class  RequirePackagesContext : public antlr4::ParserRuleContext {
  public:
    RequirePackagesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> STRING();
    antlr4::tree::TerminalNode* STRING(size_t i);

   
  };

  RequirePackagesContext* requirePackages();

  class  AssignemntOpContext : public antlr4::ParserRuleContext {
  public:
    AssignemntOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WALRUS();
    antlr4::tree::TerminalNode *EQUAL_PLUS();
    antlr4::tree::TerminalNode *EQUAL_MINUS();
    antlr4::tree::TerminalNode *EQUAL_STAR();
    antlr4::tree::TerminalNode *EQUAL_SLASH();
    antlr4::tree::TerminalNode *EQUAL_PERCENT();
    antlr4::tree::TerminalNode *EQUAL_AMPERSAND();
    antlr4::tree::TerminalNode *EQUAL_PIPE();
    antlr4::tree::TerminalNode *EQUAL_CARET();
    antlr4::tree::TerminalNode *EQUAL_DOUBLE_RANGLE();
    antlr4::tree::TerminalNode *EQUAL_DOUBLE_LANGLE();

   
  };

  AssignemntOpContext* assignemntOp();

  class  JsonContext : public antlr4::ParserRuleContext {
  public:
    JsonContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *FLOAT();
    antlr4::tree::TerminalNode *BOOL();
    antlr4::tree::TerminalNode *NULL_();
    JsonObjContext *jsonObj();
    JsonArrayContext *jsonArray();

   
  };

  JsonContext* json();

  class  JsonObjContext : public antlr4::ParserRuleContext {
  public:
    JsonObjContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    std::vector<JsonPairContext *> jsonPair();
    JsonPairContext* jsonPair(size_t i);
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

   
  };

  JsonObjContext* jsonObj();

  class  JsonPairContext : public antlr4::ParserRuleContext {
  public:
    JsonPairContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *COLON();
    JsonContext *json();

   
  };

  JsonPairContext* jsonPair();

  class  JsonArrayContext : public antlr4::ParserRuleContext {
  public:
    JsonArrayContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACK();
    std::vector<JsonContext *> json();
    JsonContext* json(size_t i);
    antlr4::tree::TerminalNode *RBRACK();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

   
  };

  JsonArrayContext* jsonArray();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool exprSempred(ExprContext *_localctx, size_t predicateIndex);
  bool typeSempred(TypeContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

