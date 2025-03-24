grammar Logos;

logosFile:
        mainFile | objectFile | interfaceFile
    ;

mainFile:
        enumDeclaration funcImplementation+ EOF
    ;

objectFile:
        objectDeclaration objectImplements? explicitVarDec* funcImplementation* EOF
    ;

interfaceFile:
        interfaceDeclaration objectImplements? explicitVarDec* funcSignature+ funcImplementation* EOF
    ;

objectDeclaration:
        OBJECT COLON TYPE
    ;

interfaceDeclaration:
        INTERFACE COLON TYPE
    ;

objectImplements:
        IMPLEMENTS COLON TYPE
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
    |   loopStatement
    |   controlFlow
    |   returnStatement
    |   enumDeclaration
    |   funcCall
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
        VARIABLE EQUAL expr
    ;

ifStatement:
        IF expr statementsBlock elseIfStatement* elseStatement?
    |   patternMatching
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

controlFlow:
        BREAK expr
    |   BREAK IF
    |   CONTINUE
    ;

returnStatement:
        RETURN expr
    ;

enumDeclaration:
        ENUM TYPE LBRACE enumField* RBRACE
    ;

enumField:
        CONST (EQUAL STRING)?
    ;

expr:
        left=expr op=(STAR | SLASH) right=expr
    |   left=expr op=(PLUS | MINUS) right=expr
    |   left=expr op=(DOUBLE_EQUAL | NOT_EQUAL | LANGLE | RANGLE | GE | LE) right=expr
    |   unaryExpr
    |   LPAREN left=expr RPAREN
    ;

exprList:
        expr (COMMA expr)* COMMA?
    ;

unaryExpr:
        VARIABLE
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
        LBRACK expr (COMMA expr)* COMMA? RBRACK
    ;

map:
        LBRACE (expr COLON expr COMMA?)* RBRACE
    ;

funcCall:
        VARIABLE LPAREN funcArgList? RPAREN
    ;

constructor:
        TYPE LPAREN funcArgList? RPAREN
    ;

funcArgList:
        funcArg (COMMA funcArg)* COMMA?
    ;

funcArg:
        (VARIABLE EQUAL)? expr
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
        TYPE
   |    TYPE (LBRACK INTEGER? RBRACK)+
   |    LBRACE type COLON type RBRACE
   ;

vector:
        VEC | VEC2 | VEC3 | VEC4
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

AND: 'and';
OR: 'or';
NOT: 'not';
IN: 'in';

INTEGER: [0-9]+;
FLOAT: [0-9]+ '.' [0-9]+;
BOOL: 'true' | 'false';
NULL: 'null';
CONST: [A-Z0-9_]+;
TYPE: [A-Z][a-zA-Z0-9_]*;
VARIABLE: [a-z_][a-zA-Z0-9_]*;
STRING: '"' ( ~["\\] | '\\' . )* '"';
LINE_COMMENT: '//' ~( '\r' | '\n' )* -> skip;
BLOCK_COMMENT: '///' .*? '///' -> skip;
WS: [ \t\r\n]+ -> skip;