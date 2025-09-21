
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    DOUBLE_EQUAL = 8, NOT_EQUAL = 9, GE = 10, LE = 11, LPAREN = 12, RPAREN = 13, 
    LBRACE = 14, RBRACE = 15, LBRACK = 16, RBRACK = 17, LANGLE = 18, RANGLE = 19, 
    COMMA = 20, ARROW = 21, TRIPLE_DOT = 22, DOUBLE_DOT = 23, WALRUS = 24, 
    EQUAL_PLUS = 25, EQUAL_MINUS = 26, EQUAL_STAR = 27, EQUAL_SLASH = 28, 
    EQUAL_PERCENT = 29, EQUAL_AMPERSAND = 30, EQUAL_PIPE = 31, EQUAL_CARET = 32, 
    EQUAL_DOUBLE_RANGLE = 33, EQUAL_DOUBLE_LANGLE = 34, INC = 35, DEC = 36, 
    DOT = 37, COLON = 38, EQUAL = 39, PLUS = 40, MINUS = 41, STAR = 42, 
    SLIDER = 43, SLASH = 44, HASH = 45, QUEST_MARK = 46, EXCLA_MARK = 47, 
    PERCENT = 48, DOLLAR = 49, AMPERSAND = 50, PIPE = 51, CARET = 52, DOUBLE_RANGLE = 53, 
    DOUBLE_LANGLE = 54, OBJECT = 55, SINGLETON = 56, SELF_INSTANCE = 57, 
    SELF_CLASS = 58, INTERFACE = 59, EXTERN = 60, VISIBILITY = 61, IMPLEMENTS = 62, 
    CONST = 63, ENUM = 64, GO = 65, DEFER = 66, IO = 67, OWNER = 68, AND = 69, 
    OR = 70, NOT = 71, IN = 72, IF = 73, WHILE = 74, ELSE = 75, BREAK = 76, 
    CONTINUE = 77, RETURN = 78, FOR = 79, FOREVER = 80, FOR_IS_FIRST = 81, 
    FOR_IS_LAST = 82, FOR_I = 83, VEC2 = 84, VEC3 = 85, VEC4 = 86, LONG = 87, 
    INTEGER = 88, FLOAT = 89, BOOL = 90, NULL_ = 91, IDENTIFIER = 92, STRING = 93, 
    TAG = 94, LINE_COMMENT = 95, BLOCK_COMMENT = 96, WS = 97
  };

  enum {
    RuleLogosFile = 0, RuleLogosEnvFile = 1, RuleLogosAppFile = 2, RuleMainFile = 3, 
    RuleObjectFile = 4, RuleInterfaceFile = 5, RuleTestFile = 6, RuleInterface = 7, 
    RuleInterfaceBody = 8, RuleObject = 9, RuleObjectBody = 10, RuleField = 11, 
    RuleInterfaceField = 12, RuleImplements = 13, RuleEnumDeclaration = 14, 
    RuleEnumField = 15, RuleIoPair = 16, RuleGroup = 17, RuleGroupTypesList = 18, 
    RuleGroupTargetList = 19, RuleFuncSignatureHeader = 20, RuleFuncSignature = 21, 
    RuleInterfaceFunc = 22, RuleFunc = 23, RuleLambda = 24, RuleLambdaParams = 25, 
    RuleLambdaParam = 26, RuleMethod = 27, RuleParam = 28, RuleStatement = 29, 
    RuleStatementsBlock = 30, RuleAssignment = 31, RuleExplicitVarDec = 32, 
    RuleImplicitVarDec = 33, RuleIfStatement = 34, RuleElseIfStatement = 35, 
    RuleElseStatement = 36, RulePatternMatching = 37, RulePattern = 38, 
    RuleLoopStatement = 39, RuleRangeLoop = 40, RuleBreakStmt = 41, RuleReturnStatement = 42, 
    RuleIoStatement = 43, RuleCoroutine = 44, RuleDeferStmt = 45, RuleExpr = 46, 
    RuleUnaryExpr = 47, RulePrefixExpr = 48, RulePostfixExpr = 49, RuleArrayExpr = 50, 
    RuleHashMap = 51, RuleKeyValue = 52, RuleFuncCall = 53, RuleFuncArgList = 54, 
    RuleFuncArg = 55, RuleInstance = 56, RuleInstanceArgList = 57, RuleInstanceArg = 58, 
    RuleConstant = 59, RuleIterIndex = 60, RuleIndex = 61, RuleSelection = 62, 
    RuleFirstSelectionElement = 63, RuleInnerSelectionElement = 64, RuleForVariable = 65, 
    RuleRange = 66, RuleType = 67, RuleMapType = 68, RuleArraySize = 69, 
    RuleFuncType = 70, RuleVector = 71, RuleExtern_c = 72, RuleExtern_cpp = 73, 
    RuleRequireEnvVars = 74, RuleRequirePackages = 75, RuleAssignemntOp = 76, 
    RuleJson = 77, RuleJsonObj = 78, RuleJsonPair = 79, RuleJsonArray = 80
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
  class EnumDeclarationContext;
  class EnumFieldContext;
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
  class Extern_cContext;
  class Extern_cppContext;
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
    Extern_cContext *extern_c();
    Extern_cppContext *extern_cpp();

   
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
    std::vector<FieldContext *> field();
    FieldContext* field(size_t i);
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
    std::vector<EnumDeclarationContext *> enumDeclaration();
    EnumDeclarationContext* enumDeclaration(size_t i);
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
    PatternMatchingContext *patternMatching();
    IfStatementContext *ifStatement();
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
    antlr4::tree::TerminalNode *FOREVER();
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
    ConstantContext *constant();
    FuncCallContext *funcCall();
    PrefixExprContext *prefixExpr();
    PostfixExprContext *postfixExpr();
    LambdaContext *lambda();
    JsonContext *json();
    InstanceContext *instance();
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

  class  Extern_cContext : public antlr4::ParserRuleContext {
  public:
    Extern_cContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EXTERN();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> STRING();
    antlr4::tree::TerminalNode* STRING(size_t i);

   
  };

  Extern_cContext* extern_c();

  class  Extern_cppContext : public antlr4::ParserRuleContext {
  public:
    Extern_cppContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EXTERN();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> STRING();
    antlr4::tree::TerminalNode* STRING(size_t i);

   
  };

  Extern_cppContext* extern_cpp();

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

