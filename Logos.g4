grammar Logos;

logosFile:
        importStatement? (mainFile | objectFile | interfaceFile)
    ;

mainFile:
        funcImplementation+ EOF
    ;

interfaceFile:
        interfaceDeclaration objectImplements? explicitVarDec* funcSignature+ funcImplementation* EOF
    ;

objectFile:
        objectDeclaration objectImplements? explicitVarDec* funcImplementation* EOF
    ;

importStatement:
        IMPORT LPAREN importPath* RPAREN
    ;

importPath:
        TYPE (DOT TYPE)*
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
        VARIABLE LPAREN variableDefintionList? RPAREN (COLON TYPE)?
    ;

funcImplementation:
        funcSignature funcBody
    ;

funcBody:
        statementsBlock
    ;

funcCall:
        VARIABLE LPAREN funcArgList? RPAREN
    ;

constructorCall:
        TYPE LPAREN funcArgList? RPAREN
    ;

variableDefintionList:
        explicitVarDec (COMMA explicitVarDec)* COMMA?
    ;

explicitVarDec:
        VARIABLE COLON TYPE (EQUAL expr)?
    ;

implicitVarDec:
        VARIABLE (EQUAL expr)?
    ;

funcArg:
        (VARIABLE EQUAL)? expr
    ;

funcArgList:
        funcArg (COMMA funcArg)* COMMA?
    ;

statement:
        explicitVarDec
    |   implicitVarDec
    |   ifStatement
    |   loopStatement
    |   loopControlStatement
    |   returnStatement
    |   enumDeclaration
    |   funcCall
    ;

enumDeclaration: ENUM TYPE LBRACE enumField* RBRACE;

enumField: CONST (EQUAL STRING)?;

statementsBlock:
        LBRACE statement* RBRACE
    ;

exprList:
        expr (COMMA expr)* COMMA?
    ;

expr:
        left=expr op=(STAR | SLASH) right=expr
    |   left=expr op=(PLUS | MINUS) right=expr
    |   left=expr op=(DOUBLE_EQUAL | LANGLE | RANGLE | GE | LE) right=expr
    |   unaryExpr
    |   LPAREN left=expr RPAREN
    ;

unaryExpr:
        funcCall
    |   constructorCall
    |   constant
    |   VARIABLE
    ;

constant:
        INTEGER
    |   FLOAT
    |   BOOL
    |   STRING
;

selection:
        unaryExpr (DOT unaryExpr)*
    ;

ifStatement:
        IF expr statementsBlock elseStatement
    |   patternMatching
    ;

elseStatement:
    (ELSE expr statementsBlock)* (ELSE statementsBlock)?
    ;

patternMatching:
        IF expr? LBRACE pattern* (ELSE COLON statementsBlock)? RBRACE
    ;

pattern:
        expr COLON statementsBlock
    ;

loopStatement:
        FOR expr? statementsBlock
    |   FOR exprList IN expr statementsBlock
    |   FOR exprList IN range statementsBlock
    ;

loopControlStatement:
        BREAK expr
    |   BREAK IF
    |   CONTINUE
    ;

returnStatement:
        RETURN expr
    ;

range:
        expr? DOUBLE_DOT expr
    ;

DOUBLE_EQUAL: '==';
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
INTERFACE: 'interface';
ENUM: 'enum';

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
CONST: [A-Z0-9_]+;
TYPE: [A-Z] [a-zA-Z0-9_]*;
VARIABLE: [a-z_][a-zA-Z0-9_]*;
STRING: '"' ( ~["\\] | '\\' . )* '"';
LINE_COMMENT: '//' ~( '\r' | '\n' )* -> skip;
BLOCK_COMMENT: '///' .*? '///' -> skip;
WS: [ \t\r\n]+ -> skip;