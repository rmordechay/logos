grammar Logos;

logosFile: importStatement? (mainFile | objectFile | interfaceFile);

mainFile: (explicitVarDec | implicitVarDec)? funcImplementation+ EOF;

interfaceFile: interfaceDeclaration objectImplements? explicitVarDec* funcDec+ funcImplementation* EOF;

objectFile: objectDeclaration objectImplements? explicitVarDec* funcImplementation* EOF;

importStatement: IMPORT LPAREN importPath* RPAREN;

importPath: TYPE (DOT TYPE)*;

objectDeclaration: OBJECT COLON TYPE;

interfaceDeclaration: INTERFACE COLON TYPE;

objectImplements: IMPLEMENTS COLON TYPE;

funcDec: VARIABLE LPAREN explicitVarDecList? RPAREN COLON TYPE;

funcImplementation: funcDec funcBody;

funcBody: statementsBlock;

funcCall: VARIABLE LPAREN funcArgList? RPAREN;

constructorCall: TYPE LPAREN funcArgList? RPAREN;

explicitVarDecList: explicitVarDec (COMMA explicitVarDec)* COMMA?;

explicitVarDec:
        VARIABLE COLON TYPE (EQUAL expr)?
    |   enumDeclaration
    ;

implicitVarDec: VARIABLE (EQUAL expr)?;

funcArg: (VARIABLE EQUAL)? expr;

funcArgList: funcArg (COMMA funcArg)* COMMA?;

statement:
        explicitVarDec
    |   implicitVarDec
    |   ifStatement
    |   loopStatement
    |   controlFlowStatement
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
        expr (STAR | SLASH) expr
    |   expr (PLUS | MINUS) expr
    |   expr (DOUBLE_EQUAL | RBRACK | LBRACK | GE | LE) expr
    |   unaryExpr
    |   LPAREN expr RPAREN
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
    |   patterMatching
    ;

elseStatement:
    (ELSE expr statementsBlock)* (ELSE statementsBlock)?
    ;

patterMatching:
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

range:
        expr? DOUBLE_DOT expr
    ;

controlFlowStatement:
        BREAK expr
    |   BREAK IF
    |   CONTINUE
    |   RETURN expr
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
LEFT_ANGLE: '<';
RIGHT_ANGLE: '>';

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