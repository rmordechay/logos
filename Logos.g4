grammar Logos;

logosFile: importStatement? (mainFile | objectFile | interfaceFile);

mainFile: (explicitVarDec | implicitVarDec)? funcImplementation+ EOF;

interfaceFile: interfaceDeclaration objectImplements? explicitVarDec* funcDec+ funcImplementation* EOF;

objectFile: objectDeclaration objectImplements? explicitVarDec* funcImplementation* EOF;

importStatement: IMPORT LEFT_PAREN importPath* RIGHT_PAREN;

importPath: TYPE (DOT TYPE)*;

objectDeclaration: OBJECT COLON TYPE;

interfaceDeclaration: INTERFACE COLON TYPE;

objectImplements: IMPLEMENTS COLON TYPE;

funcDec: VARIABLE LEFT_PAREN explicitVarDecList? RIGHT_PAREN COLON TYPE;

funcImplementation: funcDec funcBody;

funcBody: statementsBlock;

funcCall: VARIABLE LEFT_PAREN funcArgList? RIGHT_PAREN;

constructorCall: TYPE LEFT_PAREN funcArgList? RIGHT_PAREN;

explicitVarDecList: explicitVarDec (COMMA explicitVarDec)*;

explicitVarDec:
        VARIABLE COLON TYPE (EQUAL expr)?
    |   enumDeclaration
    ;

implicitVarDec: VARIABLE (EQUAL expr)?;

funcArg: (VARIABLE EQUAL)? expr;

funcArgList: funcArg (COMMA funcArg)*;

statement:
        explicitVarDec
    |   implicitVarDec
    |   ifStatement
    |   loopStatement
    |   controlFlowStatement
    |   enumDeclaration
    |   expr
    ;

enumDeclaration: ENUM TYPE LEFT_BRACE enumField* RIGHT_BRACE;

enumField: CONST (EQUAL STRING)?;

statementsBlock:
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
        IF expr? LEFT_BRACE pattern* (ELSE COLON statementsBlock)? RIGHT_BRACE
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