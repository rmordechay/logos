grammar Logos;

logosFile:
        extern? (mainFile | objectFile | interfaceFile)
    ;

extern:
        EXTERN 'C' LBRACE STRING* RBRACE
    ;

logosEnvFile:
        (implicitVarDec | explicitVarDec)* EOF
    ;

logosAppFile:
        (implicitVarDec | explicitVarDec)* requireEnvVars? EOF
    ;

mainFile:
        (object | enumDeclaration | interface | group)* funcImpl+ EOF
    ;

objectFile:
        objectDeclaration objectBody EOF
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
            implements? interfaceField* interfaceFuncSignature* funcImpl*
    ;

object:
        (OBJECT | SINGLETON) IDENTIFIER LBRACE objectBody RBRACE
    ;

objectBody:
        implements? field* methodImplementation*
    ;


field:
        VISIBILITY? CONST? IDENTIFIER COLON type (EQUAL expr)?
    ;

interfaceField:
        CONST? IDENTIFIER QUEST_MARK? COLON type (EQUAL expr)?
    ;

objectDeclaration:
        (OBJECT | SINGLETON) IDENTIFIER
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

interfaceFuncSignature:
        funcSignatureHeader QUEST_MARK? (COLON type)?
    ;

funcImpl:
        funcSignature funcBody
    ;

anonnymosfuncSignature:
        LPAREN (param (COMMA param)* COMMA?)? RPAREN (COLON type)?
    ;

anonnymosFunc:
        anonnymosfuncSignature funcBody
    ;

methodImplementation:
        VISIBILITY? funcSignature funcBody
    ;

funcBody:
        statementsBlock
    ;

param:
        IDENTIFIER COLON type TRIPLE_DOT? (EQUAL expr)? | IDENTIFIER funcType
    ;

statement:
        assignment
    |   explicitVarDec
    |   implicitVarDec
    |   ifStatement
    |   patternMatching
    |   loopStatement
    |   CONTINUE
    |   breakStmt
    |   returnStatement
    |   funcCall
    |   selection
    |   postfixExpr
    ;

statementsBlock:
        LBRACE statement* RBRACE
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
        IF expr TAG? statementsBlock elseIfStatement* elseStatement?
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
        FOR IDENTIFIER COMMA? IN iterableRange=range statementsBlock
    |   FOR IDENTIFIER (COMMA IDENTIFIER)* COMMA? IN iterableExpr=unaryExpr statementsBlock
    |   FOR IDENTIFIER? statementsBlock
    ;

breakStmt:
        BREAK TAG?
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
    ;

unaryExpr:
        IDENTIFIER
    |   SELF_INSTANCE
    |   SELF_CLASS
    |   NULL
    |   prefixExpr
    |   postfixExpr
    |   funcCall
    |   anonnymosFunc
    |   vector
    |   constructor
    |   constant
    |   iterIndex
    |   selection
    |   arrayExpr
    |   hashMap
    ;

prefixExpr:
        (NOT | MINUS) expr
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

constructor:
        IDENTIFIER LBRACE constructorArgList? RBRACE
    ;

constructorArgList:
        constructorArg (COMMA constructorArg)* COMMA?
    ;

constructorArg:
        IDENTIFIER EQUAL expr
    ;

constant:
        INTEGER
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
    |   constructor
    |   iterIndex
    ;

innerSelectionElement:
        IDENTIFIER
    |   funcCall
    |   iterIndex
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

requireEnvVars:
        'require' 'envs' LBRACE (IDENTIFIER COLON type)* RBRACE
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
ARROW: '->';
LANGLE: '<';
RANGLE: '>';

COMMA: ',';
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
