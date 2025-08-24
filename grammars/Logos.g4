grammar Logos;

logosFile:
        extern? (mainFile | objectFile | interfaceFile)
    ;

logosEnvFile:
        (implicitVarDec | explicitVarDec)* EOF
    ;

logosAppFile:
        (IDENTIFIER EQUAL expr)* requireEnvVars? requirePackages? EOF
    ;

mainFile:
        (object | enumDeclaration | interface | group)* func+ EOF
    ;

objectFile:
        (OBJECT | SINGLETON) IDENTIFIER objectBody EOF
    ;

interfaceFile:
        INTERFACE IDENTIFIER interfaceBody EOF
    ;

interface:
        INTERFACE IDENTIFIER LBRACE interfaceBody RBRACE
    ;

group:
        IDENTIFIER EQUAL LBRACE groupTypesList RBRACE ARROW LBRACE groupTargetList RBRACE
    ;

groupTypesList:
        type (COMMA type)* COMMA?
    ;

groupTargetList:
        IDENTIFIER (COMMA IDENTIFIER)* COMMA?
    ;

interfaceBody:
            implements? interfaceField* interfaceFunc*
    ;

object:
        (OBJECT | SINGLETON) IDENTIFIER LBRACE objectBody RBRACE
    ;

objectBody:
        implements? field* method*
    ;

field:
        VISIBILITY? CONST? IDENTIFIER COLON type (EQUAL expr)?
    ;

interfaceField:
        CONST? IDENTIFIER QUEST_MARK? COLON type (EQUAL expr)?
    ;

implements:
        IMPLEMENTS COLON IDENTIFIER (COMMA IDENTIFIER)? COMMA?
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
    |   ifStatement
    |   patternMatching
    |   loopStatement
    |   coroutine
    |   deferStmt
    |   breakStmt
    |   expr
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
        CONST? IDENTIFIER COLON type (EQUAL expr)?
    ;

implicitVarDec:
        CONST? IDENTIFIER (QUEST_MARK)? EQUAL expr
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
        FOR whileExpr=expr statementsBlock
    |   FOR IDENTIFIER IN iterableRange=range statementsBlock
    |   FOR IDENTIFIER (COMMA IDENTIFIER)* COMMA? IN iterableExpr=unaryExpr statementsBlock
    |   FOR IDENTIFIER? statementsBlock
    ;

breakStmt:
        BREAK (TAG | IF)?
    ;

returnStatement:
        RETURN expr?
    ;

enumDeclaration:
        ENUM IDENTIFIER LBRACE enumField* RBRACE
    ;

enumField:
        IDENTIFIER (EQUAL STRING)?
    ;

coroutine:
        GO (funcCall | selection)
    ;

deferStmt:
        DEFER (funcCall | selection)
    ;

expr:
        LPAREN left=expr RPAREN (ARROW type)?
    |   unaryExpr (ARROW cast=type)?
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
    |   funcCall
    |   postfixExpr
    |   lambda
    |   prefixExpr
    |   'json'json
    |   instance
    |   constant
    |   iterIndex
    |   selection
    |   arrayExpr
    |   hashMap
    |   isFirst
    |   isLast
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

isFirst:
        FOR_IS_FIRST
    ;

isLast:
        FOR_IS_LAST
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
    |   start=expr DOUBLE_DOT
    ;

type:
        IDENTIFIER QUEST_MARK?
   |    SELF_CLASS
   |    baseType=type arraySize+ EXCLA_MARK?
   |    mapType
   |    funcType
   ;

mapType:
        LBRACE key=type COLON value=type RBRACE
    ;

arraySize:
        LBRACK expr? RBRACK
    ;

funcType:
        LPAREN (type (COMMA type)* COMMA?)? RPAREN COLON rt=type
    ;

vector:
        (VEC2 | VEC3 | VEC4) LPAREN (expr (COMMA expr)* COMMA?)? RPAREN
    ;

extern:
        EXTERN 'C' LBRACE STRING* RBRACE
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

// JSON
json:
        STRING
    |   INTEGER
    |   FLOAT
    |   BOOL
    |   NULL
    |   jsonObj
    |   jsonArray
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
SLIDER: '_/';

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
FOR_IS_FIRST: 'for.isFirst';
FOR_IS_LAST: 'for.isLast';

VEC2: 'vec2';
VEC3: 'vec3';
VEC4: 'vec4';

IF: 'if';
ELSE: 'else';
FOR: 'for';
BREAK: 'break';
CONTINUE: 'continue';
RETURN: 'return';

AND: 'and';
OR: 'or';
NOT: 'not';
IN: 'in';

LONG: [0-9][0-9_]*'L';
INTEGER: [0-9][0-9_]*;
FLOAT: '-'?[0-9]+'.'[0-9]+;
BOOL: 'true' | 'false';
NULL: 'null';
IDENTIFIER: [a-zA-Z][a-zA-Z0-9_]*;
STRING: '"' ( ~["\\] | '\\'.)* '"';
TAG: '@'[a-zA-Z0-9_]+;
LINE_COMMENT: '//' ~( '\r' | '\n' )* -> skip;
BLOCK_COMMENT: '///' .*? '///' -> skip;
WS: [ \t\r\n]+ -> skip;
