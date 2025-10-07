grammar Logos;

logosFile:
        (extern_c | extern_cpp)? (mainFile | objectFile | interfaceFile | testFile)
    ;

logosEnvFile:
        (implicitVarDec | explicitVarDec)* EOF
    ;

logosAppFile:
        (IDENTIFIER EQUAL expr)* requireEnvVars? requirePackages? EOF
    ;

mainFile:
        (subtype | object | enumDeclaration | interface | group)* func+ EOF
    ;

objectFile:
        (SINGLETON | OBJECT) IDENTIFIER objectBody EOF
    ;

interfaceFile:
        INTERFACE IDENTIFIER interfaceBody EOF
    ;

testFile:
        'test' IDENTIFIER field* func*
    ;

object:
        (SINGLETON | OBJECT) IDENTIFIER LBRACE objectBody RBRACE
    ;

objectBody:
        implements? (enumDeclaration | field | subtype)* method* ioPair*
    ;

interface:
        INTERFACE IDENTIFIER LBRACE interfaceBody RBRACE
    ;

interfaceBody:
        interfaceField* interfaceFunc*
    ;

subtype:
        IDENTIFIER EQUAL type
    ;

field:
        OWNER? VISIBILITY? CONST? IDENTIFIER COLON type (EQUAL expr)?
    ;

interfaceField:
        IDENTIFIER QUEST_MARK? COLON type
    ;

implements:
        IMPLEMENTS COLON IDENTIFIER (COMMA IDENTIFIER)? COMMA?
    ;

enumDeclaration:
        ENUM IDENTIFIER LBRACE enumField* RBRACE
    ;

enumField:
        IDENTIFIER (EQUAL STRING)?
    ;

ioPair:
        IO LBRACE (LPAREN opening=IDENTIFIER COMMA closing=IDENTIFIER RPAREN)+ RBRACE
    ;

group:
        IDENTIFIER EQUAL LBRACE groupTypesList RBRACE ARROW LPAREN groupTargetList RPAREN
    ;

groupTypesList:
        type (COMMA type)* COMMA?
    ;

groupTargetList:
        IDENTIFIER (COMMA IDENTIFIER)* COMMA?
    ;

funcSignatureHeader:
        IDENTIFIER LPAREN (param (COMMA param)* COMMA?)? RPAREN
    ;

funcSignature:
        funcSignatureHeader (COLON type)?
    ;

interfaceFunc:
        funcSignatureHeader QUEST_MARK? (COLON type)? statementsBlock?
    ;

func:
        funcSignature statementsBlock
    ;

lambda:
        (IDENTIFIER | (LPAREN lambdaParams? RPAREN)) (COLON rt=type)? ARROW statementsBlock
    ;

lambdaParams:
         lambdaParam (COMMA lambdaParam)* COMMA?
    ;

lambdaParam:
        IDENTIFIER (COLON type)?
    ;

method:
        VISIBILITY? funcSignature statementsBlock
    ;

param:
        IDENTIFIER COLON type TRIPLE_DOT? (EQUAL expr)?
    ;

statement:
        assignment
    |   returnStatement
    |   explicitVarDec
    |   implicitVarDec
    |   patternMatching
    |   ifStatement
    |   loopStatement
    |   coroutine
    |   deferStmt
    |   breakStmt
    |   ioStatement
    |   funcCall
    |   selection
    |   postfixExpr
    |   CONTINUE
    ;

statementsBlock:
        LBRACE statement* RBRACE
    |   statement
    ;

assignment:
        (IDENTIFIER | iterIndex | selection) assignemntOp expr
    ;

explicitVarDec:
        OWNER? CONST? IDENTIFIER COLON type (EQUAL expr)?
    ;

implicitVarDec:
        OWNER? CONST? IDENTIFIER EQUAL expr QUEST_MARK?
    ;

ifStatement:
        IF expr TAG? (statementsBlock) elseIfStatement* elseStatement?
    ;

elseIfStatement:
        ELSE expr statementsBlock
    ;

elseStatement:
        ELSE statementsBlock
    ;

patternMatching:
        IF expr? LBRACE pattern* (ELSE COLON statementsBlock)? RBRACE
    ;

pattern:
        expr COLON statementsBlock
    ;

loopStatement:
        WHILE whileExpr=expr statementsBlock
    |   FOR IDENTIFIER (COMMA IDENTIFIER)* COMMA? IN iterableExpr=unaryExpr statementsBlock
    |   FOREVER statementsBlock
    |   rangeLoop statementsBlock
    ;

rangeLoop:
        FOR IDENTIFIER IN iterableRange=range
    |   FOR expr
    ;

breakStmt:
        BREAK (TAG | IF)?
    ;

returnStatement:
        RETURN expr?
    ;

ioStatement:
        IO (IDENTIFIER (COLON type)? EQUAL)? expr statementsBlock
    ;

coroutine:
        GO (funcCall | selection)
    ;

deferStmt:
        DEFER (funcCall | selection)
    ;

expr:
        LPAREN left=expr RPAREN
    |   unaryExpr QUEST_MARK? (ARROW cast=type)?
    |   left=expr op=(STAR | SLASH | PERCENT) right=expr
    |   left=expr op=(PLUS | MINUS) right=expr
    |   left=expr op=(LANGLE | RANGLE | GE | LE) right=expr
    |   left=expr op=(DOUBLE_EQUAL | NOT_EQUAL) right=expr
    |   left=expr op=(AND | OR) right=expr
    |   left=expr op=(AMPERSAND | CARET | PIPE) right=expr
    |   left=expr op=(DOUBLE_LANGLE | DOUBLE_RANGLE) right=expr
    |   left=expr op=IN right=expr
    ;

unaryExpr:
        vector
    |   JSON json
    |   constant
    |   funcCall
    |   prefixExpr
    |   postfixExpr
    |   lambda
    |   instance
    |   iterIndex
    |   selection
    |   arrayExpr
    |   hashMap
    |   FOR_META
    |   SELF_INSTANCE
    |   SELF_CLASS
    |   NULL
    |   IDENTIFIER
    ;

prefixExpr:
        (NOT | MINUS | SLIDER) expr
    ;

postfixExpr:
        (IDENTIFIER |  iterIndex | selection | funcCall | constant) (INC | DEC)
    ;

arrayExpr:
        LBRACK (expr (COMMA expr)* COMMA?)? RBRACK EXCLA_MARK?
    ;

hashMap:
        LBRACE (keyValue (COMMA keyValue)* COMMA?)? RBRACE
    ;

keyValue:
        key=expr COLON value=expr
    ;

funcCall:
        IDENTIFIER LPAREN funcArgList? TRIPLE_DOT? COMMA? RPAREN
    ;

funcArgList:
        funcArg (COMMA funcArg)*
    ;

funcArg:
        (IDENTIFIER EQUAL)? expr
    ;

instance:
        IDENTIFIER LBRACE instanceArgList? RBRACE
    ;

instanceArgList:
        instanceArg (COMMA instanceArg)* COMMA?
    ;

instanceArg:
        IDENTIFIER EQUAL expr
    ;

constant:
        LONG
    |   INTEGER
    |   FLOAT
    |   BOOL
    |   STRING
    ;

iterIndex:
        (funcCall | IDENTIFIER) (index)+
    ;

index:
        LBRACK from=expr COLON? RBRACK
    |   LBRACK COLON to=expr RBRACK
    |   LBRACK from=expr COLON to=expr RBRACK
    ;

selection:
        firstSelectionElement QUEST_MARK? (DOT innerSelectionElement QUEST_MARK?)+
    ;

firstSelectionElement:
        IDENTIFIER
    |   STRING
    |   SELF_CLASS
    |   SELF_INSTANCE
    |   funcCall
    |   instance
    |   iterIndex
    ;

innerSelectionElement:
        funcCall
    |   iterIndex
    |   IDENTIFIER
    ;

range:
        start=expr DOUBLE_DOT end=expr
    |   DOUBLE_DOT end=expr
    ;

type:
        type (LBRACK unaryExpr RBRACK)+
   |    type (LBRACK RBRACK)+ EXCLA_MARK?
   |    mapType
   |    funcType
   |    IDENTIFIER QUEST_MARK?
   |    SELF_CLASS
   ;

mapType:
        LBRACE key=type COLON value=type RBRACE
    ;

funcType:
        LPAREN (type (COMMA type)* COMMA?)? RPAREN COLON rt=type
    ;

vector:
        (VEC2 | VEC3 | VEC4) LPAREN (expr (COMMA expr)* COMMA?)? RPAREN
    ;

extern_c:
        EXTERN 'C' LBRACE STRING* RBRACE
    ;

extern_cpp:
        EXTERN 'C++' LBRACE STRING* RBRACE
    ;

requireEnvVars:
        'require' 'envs' LBRACE (IDENTIFIER COLON type)+ RBRACE
    ;

requirePackages:
        'require' 'packages' LBRACE STRING+ RBRACE
    ;

assignemntOp:
        WALRUS
    |   EQUAL_PLUS
    |   EQUAL_MINUS
    |   EQUAL_STAR
    |   EQUAL_SLASH
    |   EQUAL_PERCENT
    |   EQUAL_AMPERSAND
    |   EQUAL_PIPE
    |   EQUAL_CARET
    |   EQUAL_DOUBLE_RANGLE
    |   EQUAL_DOUBLE_LANGLE
    ;

json:
        constant
    |   jsonObj
    |   jsonArray
    |   NULL
    ;

jsonObj:
        LBRACE jsonPair (COMMA jsonPair)* RBRACE
    |   LBRACE RBRACE
    ;

jsonPair:
        STRING COLON json
    ;

jsonArray:
        LBRACK json (COMMA json)* RBRACK
    |   LBRACK RBRACK
    ;

// Token
DOUBLE_EQUAL: '==';
NOT_EQUAL: '!=';
GE: '>=';
LE: '<=';

LPAREN: '(';
RPAREN: ')';
LBRACE: '{';
RBRACE: '}';
LBRACK: '[';
RBRACK: ']';
LANGLE: '<';
RANGLE: '>';

COMMA: ',';
ARROW: '->';
TRIPLE_DOT: '...';
DOUBLE_DOT: '..';
WALRUS: ':=';
EQUAL_PLUS: '+=';
EQUAL_MINUS: '-=';
EQUAL_STAR: '*=';
EQUAL_SLASH: '/=';
EQUAL_PERCENT: '%=';
EQUAL_AMPERSAND: '&=';
EQUAL_PIPE: '|=';
EQUAL_CARET: '^=';
EQUAL_DOUBLE_RANGLE: '<<=';
EQUAL_DOUBLE_LANGLE: '>>=';
INC: '++';
DEC: '--';
DOT: '.';
COLON: ':';
EQUAL: '=';
PLUS: '+';
MINUS: '-';
STAR: '*';
SLIDER: '_/';
SLASH: '/';
HASH: '#';
QUEST_MARK: '?';
EXCLA_MARK: '!';
PERCENT: '%';
DOLLAR: '$';
AMPERSAND: '&';
PIPE: '|';
CARET: '^';
DOUBLE_RANGLE: '<<';
DOUBLE_LANGLE: '>>';

OBJECT: 'object';
SINGLETON: 'single';
SELF_INSTANCE: 'self';
SELF_CLASS: 'Self';
INTERFACE: 'interface';
EXTERN: 'extern';
VISIBILITY: 'pub';
IMPLEMENTS: 'implements';
CONST: 'const';
ENUM: 'enum';
GO: 'go';
DEFER: 'defer';
IO: 'io';
OWNER: 'owner';

AND: 'and';
OR: 'or';
NOT: 'not';
IN: 'in';
IF: 'if';
WHILE: 'while';
ELSE: 'else';
BREAK: 'break';
CONTINUE: 'continue';
RETURN: 'return';

FOR: 'for';
FOR_META: 'for.'[a-zA-Z]+;
FOREVER: 'for.ever';
JSON: '.json';

VEC2: 'vec2';
VEC3: 'vec3';
VEC4: 'vec4';

LONG: [0-9][0-9_]*'L';
INTEGER: [0-9][0-9_]*;
FLOAT: '-'?[0-9]*'.'[0-9]*;
BOOL: 'true' | 'false';
NULL: 'null';
IDENTIFIER: [a-zA-Z][a-zA-Z0-9_]*;
STRING: '"' ( ~["\\] | '\\'.)* '"';
TAG: '@'[a-zA-Z0-9_]+;
LINE_COMMENT: '//' ~( '\r' | '\n' )* -> skip;
BLOCK_COMMENT: '///' .*? '///' -> skip;
WS: [ \t\r\n]+ -> skip;
