grammar Logos;

logosFile: importStatement? (mainFile | objectFile | interfaceFile);

mainFile: (explicitVarDec | implicitVarDec) funcImplementation+ EOF;

interfaceFile: interfaceDeclaration objectImplements? explicitVarDec* funcDec+ funcImplementation* EOF;

objectFile: objectDeclaration objectImplements? explicitVarDec* funcImplementation* EOF;

importStatement: IMPORT LEFT_PAREN expr* RIGHT_PAREN;

objectDeclaration: OBJECT COLON TYPE;

interfaceDeclaration: INTERFACE COLON TYPE;

objectImplements: IMPLEMENTS COLON TYPE;

funcDec: VARIABLE LEFT_PAREN explicitVarDecList? RIGHT_PAREN COLON TYPE;

funcImplementation: funcDec funcBody;

funcBody: statemets_block;

funcCall: VARIABLE LEFT_PAREN paramCallList* RIGHT_PAREN;

constructorCall: TYPE LEFT_PAREN paramCallList* RIGHT_PAREN;

explicitVarDecList: explicitVarDec (COMMA explicitVarDec)*;

explicitVarDec:
        VARIABLE COLON TYPE (EQUAL expr)?
    |   enumDeclaration
    ;

implicitVarDec: VARIABLE (EQUAL expr)?;

paramCall: (VARIABLE EQUAL)? expr;

paramCallList: paramCall (COMMA paramCall)*;

statement:
        explicitVarDec
    |   implicitVarDec
    |   ifStatement
    |   loopStatemet
    |   controlFlowStatement
    |   enumDeclaration
    |   expr
    ;

enumDeclaration: ENUM TYPE LEFT_BRACE enumField* RIGHT_BRACE;

enumField: CONST (EQUAL STRING)?;

statemets_block:
        LEFT_BRACE statement* RIGHT_BRACE
    ;

exprList:
        expr (COMMA expr)*
;

expr:
        binaryExpr
    |   unaryExpr
    |   boolExpr
    |   selection
    ;

binaryExpr:
        unaryExpr (STAR | SLASH) expr
    |   unaryExpr (PLUS | MINUS) expr
    ;

boolExpr:
        unaryExpr (DOUBLE_EQUAL | RIGHT_BRACKET | LEFT_BRACKET | GREATER_EQUAL_THAN | LESS_EQUAL_THAN) expr
    ;

unaryExpr:
        funcCall
    |   constructorCall
    |   INTEGER
    |   FLOAT
    |   BOOL
    |   STRING
    |   VARIABLE
    ;

selection:
        unaryExpr (DOT unaryExpr)*
    ;

ifStatement:
        IF expr statemets_block elseStatement
    |   patterMatching
    ;

elseStatement:
    (ELSE expr statemets_block)* (ELSE statemets_block)?
    ;

patterMatching:
        IF expr? LEFT_BRACE pattern* (ELSE COLON statemets_block)? RIGHT_BRACE
    ;

pattern:
        expr COLON statemets_block
    ;

loopStatemet:
        FOR expr? statemets_block
    |   FOR exprList IN expr statemets_block
    |   FOR exprList IN range statemets_block
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
GREATER_EQUAL_THAN: '>=';
LESS_EQUAL_THAN: '<=';

LEFT_PAREN: '(';
RIGHT_PAREN: ')';
LEFT_BRACE: '{';
RIGHT_BRACE: '}';
LEFT_BRACKET: '[';
RIGHT_BRACKET: ']';
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