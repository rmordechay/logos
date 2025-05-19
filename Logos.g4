grammar Logos;

logosFile:
        mainFile | objectFile | interfaceFile
    ;

logosEnvFile:
        (implicitVarDec | explicitVarDec)* EOF
    ;

logosAppFile:
        (implicitVarDec | explicitVarDec)* requireEnvVars? EOF
    ;

mainFile:
        (object | enumDeclaration | interface)* funcImpl+ EOF
    ;

objectFile:
        objectDeclaration objectBody EOF
    ;

interfaceFile:
        interfaceDeclaration interfaceBody EOF
    ;

interface:
        INTERFACE TYPE LBRACE interfaceBody RBRACE
    ;

interfaceBody:
        explicitVarDec* funcSignature+ funcImpl*
    ;

object:
        (OBJECT | SINGLETON) TYPE LBRACE objectBody RBRACE
    ;

objectBody:
        objectImplements? field* methodImplementation*
    ;

field:
        VISIBILITY? CONST? VARIABLE COLON type (EQUAL expr)?
    ;

objectDeclaration:
        (OBJECT | SINGLETON) COLON TYPE
    ;

interfaceDeclaration:
        INTERFACE COLON TYPE
    ;

objectImplements:
        IMPLEMENTS COLON TYPE (COMMA TYPE)? COMMA?
    ;

funcSignature:
        VARIABLE LPAREN (param (COMMA param)* COMMA?)? RPAREN (COLON type)?
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
        explicitVarDec | VARIABLE funcType
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
    ;

statementsBlock:
        LBRACE statement* RBRACE
    ;

assignment:
        (VARIABLE | iterIndex | selection) COLON EQUAL expr
    ;

explicitVarDec:
        VARIABLE COLON type (EQUAL expr)?
    ;

implicitVarDec:
        VARIABLE (QUEST_MARK)? EQUAL expr
    ;

ifStatement:
        IF expr statementsBlock elseIfStatement* elseStatement?
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
        FOR VARIABLE (COMMA VARIABLE)* COMMA? IN iterableRange=range statementsBlock
    |   FOR VARIABLE (COMMA VARIABLE)* COMMA? IN iterableExpr=unaryExpr statementsBlock
    |   FOR VARIABLE? statementsBlock
    ;

breakStmt:
        BREAK
    ;

returnStatement:
        RETURN expr
    ;

enumDeclaration:
        ENUM TYPE LBRACE enumField* RBRACE
    ;

enumField:
        CONST_NAME (EQUAL STRING)?
    ;

expr:
        LPAREN left=expr RPAREN (CAST type)?
    |   unaryExpr (CAST cast=type)?
    |   left=expr op=(STAR | SLASH) right=expr
    |   left=expr op=(PLUS | MINUS) right=expr
    |   left=expr op=(LANGLE | RANGLE | GE | LE) right=expr
    |   left=expr op=(DOUBLE_EQUAL | NOT_EQUAL) right=expr
    |   left=expr op=(AND | OR) right=expr
    |   left=expr op=(AMPERSAND | CARET | PIPE) right=expr
    |   left=expr op=(DOUBLE_LANGLE | DOUBLE_RANGLE) right=expr
    ;

unaryExpr:
        VARIABLE
    |   CONST_NAME
    |   SELF_INSTANCE
    |   SELF_CLASS
    |   NULL
    |   funcCall
    |   anonnymosFunc
    |   vector
    |   constructor
    |   constant
    |   array
    |   hashMap
    |   iterIndex
    |   selection
    ;

array:
        LBRACK (expr (COMMA expr)* COMMA?)? RBRACK
    ;

hashMap:
        LBRACE (keyValue (COMMA keyValue)* COMMA?)? RBRACE
    ;

keyValue:
        key=expr COLON value=expr
    ;

funcCall:
        VARIABLE LPAREN funcArgList? RPAREN
    ;

funcArgList:
        funcArg (COMMA funcArg)* COMMA?
    ;

funcArg:
        (VARIABLE EQUAL)? expr
    ;

constructor:
        TYPE LPAREN constructorArgList? RPAREN
    ;

constructorArgList:
        constructorArg (COMMA constructorArg)* COMMA?
    ;

constructorArg:
        VARIABLE EQUAL expr
    ;

constant:
        INTEGER
    |   FLOAT
    |   BOOL
    |   STRING
    ;

iterIndex:
        (funcCall | VARIABLE) (index)+
    ;

index:
        LBRACK from=expr COLON? RBRACK
    |   LBRACK COLON to=expr RBRACK
    |   LBRACK from=expr COLON to=expr RBRACK
    ;

selection:
        firstSelectionElement (DOT innerSelectionElement)+
    ;

firstSelectionElement:
        VARIABLE
    |   TYPE
    |   STRING
    |   SELF_CLASS
    |   SELF_INSTANCE
    |   funcCall
    |   constructor
    |   iterIndex
    ;

innerSelectionElement:
        VARIABLE
    |   funcCall
    |   iterIndex
    ;

range:
        start=expr DOUBLE_DOT end=expr
    |   DOUBLE_DOT end=expr
    |   start=expr DOUBLE_DOT
    ;

type:
        TYPE QUEST_MARK?
   |    SELF_CLASS
   |    baseType=type (LBRACK expr? RBRACK)+
   |    mapType
   |    funcType
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

requireEnvVars:
        'require' 'envs' LBRACE (VARIABLE COLON type)* RBRACE
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
CAST: '->';
LANGLE: '<';
RANGLE: '>';

COMMA: ',';
DOUBLE_DOT: '..';
DOT: '.';
COLON: ':';
EQUAL: '=';
MINUS: '-';
PLUS: '+';
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
SINGLETON: 'singleton';
SELF_INSTANCE: 'self';
SELF_CLASS: 'Self';
INTERFACE: 'interface';
ENUM: 'enum';

VEC2: 'vec2';
VEC3: 'vec3';
VEC4: 'vec4';

IMPLEMENTS: 'implements';
IMPORT: 'import';

IF: 'if';
ELSE: 'else';
FOR: 'for';
BREAK: 'break';
CONTINUE: 'continue';
RETURN: 'return';
VISIBILITY: 'pub';
CONST: 'const';

AND: 'and';
OR: 'or';
NOT: 'not';
IN: 'in';

INTEGER: [0-9]+;
FLOAT: [0-9]+ '.' [0-9]+;
BOOL: 'true' | 'false';
NULL: 'null';
CONST_NAME: [A-Z0-9_]+;
TYPE: [A-Z][a-zA-Z0-9_]*;
VARIABLE: [a-z_][a-zA-Z0-9_]*;
STRING: '"' ( ~["\\] | '\\'.)* '"';
LINE_COMMENT: '//' ~( '\r' | '\n' )* -> skip;
BLOCK_COMMENT: '///' .*? '///' -> skip;
WS: [ \t\r\n]+ -> skip;