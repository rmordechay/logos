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
        (object | enumDeclaration)* funcImplementation+ EOF
    ;

objectFile:
        objectDeclaration objectBody EOF
    ;

interfaceFile:
        interfaceDeclaration explicitVarDec* funcSignature+ funcImplementation* EOF
    ;

object:
        OBJECT TYPE LBRACE objectBody RBRACE
    ;

objectBody:
        objectImplements? field* funcImplementation*
    ;

field:
        VISIBILITY? CONST? VARIABLE COLON type (EQUAL expr)?
    ;

objectDeclaration:
        OBJECT COLON TYPE
    ;

interfaceDeclaration:
        INTERFACE COLON TYPE
    ;

objectImplements:
        IMPLEMENTS COLON TYPE (COMMA TYPE)? COMMA?
    ;

funcSignature:
        VARIABLE LPAREN paramList? RPAREN (COLON type)?
    ;

funcImplementation:
        funcSignature funcBody
    ;

funcBody:
        statementsBlock
    ;

paramList:
        explicitVarDec (COMMA explicitVarDec)* COMMA?
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
        (VARIABLE | arrayIndex | selection) COLON EQUAL expr
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
        FOR VARIABLE (COMMA VARIABLE)* IN iterableRange=range statementsBlock
    |   FOR VARIABLE (COMMA VARIABLE)* IN iterableExpr=unaryExpr statementsBlock
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
        left=expr op=(STAR | SLASH) right=expr
    |   left=expr op=(PLUS | MINUS) right=expr
    |   left=expr op=(DOUBLE_EQUAL | NOT_EQUAL | LANGLE | RANGLE | GE | LE) right=expr
    |   unaryExpr (CAST cast=type)?
    |   LPAREN left=expr RPAREN (CAST type)?
    ;

unaryExpr:
        VARIABLE
    |   CONST_NAME
    |   SELF_INSTANCE
    |   SELF_CLASS
    |   NULL
    |   funcCall
    |   constructor
    |   constant
    |   array
    |   map
    |   arrayIndex
    |   selection
    ;

array:
        LBRACK (expr (COMMA expr)* COMMA?)? RBRACK
    ;

map:
        LBRACE (expr COLON expr COMMA?)* RBRACE
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

arrayIndex:
        (funcCall | VARIABLE) (LBRACK expr RBRACK)+
    ;

selection:
        firstSelectionElement (DOT innerSelectionElement)+
    ;

firstSelectionElement:
        VARIABLE
    |   TYPE
    |   SELF_CLASS
    |   SELF_INSTANCE
    |   funcCall
    |   constructor
    |   arrayIndex
    ;

innerSelectionElement:
        VARIABLE
    |   funcCall
    |   arrayIndex
    ;

range:
        start=expr? DOUBLE_DOT end=expr
    ;

type:
        SELF_CLASS
   |    TYPE QUEST_MARK?
   |    TYPE (LBRACK INTEGER? RBRACK)+
   |    LBRACE type COLON type RBRACE
   ;

vector:
        VEC | VEC2 | VEC3 | VEC4
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

OBJECT: 'object';
SELF_INSTANCE: 'self';
SELF_CLASS: 'Self';
INTERFACE: 'interface';
ENUM: 'enum';

VEC: 'vec';
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
STRING: '"' ( ~["\\] | '\\' . )* '"';
LINE_COMMENT: '//' ~( '\r' | '\n' )* -> skip;
BLOCK_COMMENT: '///' .*? '///' -> skip;
WS: [ \t\r\n]+ -> skip;