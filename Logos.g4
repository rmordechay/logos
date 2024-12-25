grammar Logos;

logosFile: mainFile | objectFile | interfaceFile;

mainFile: funcImplementation+ EOF;

interfaceFile: interfaceDeclaration objectImplements? explicitVarDec* funcDec+ funcImplementation* EOF;

objectFile: objectDeclaration objectImplements? explicitVarDec* funcImplementation* EOF;

objectDeclaration: OBJECT COLON TYPE;

interfaceDeclaration: INTERFACE COLON TYPE;

objectImplements: IMPLEMENTS COLON TYPE;

funcDec: VARIABLE LEFT_PAREN explicitVarDecList? RIGHT_PAREN COLON TYPE;

funcImplementation: funcDec funcBody;

funcBody: LEFT_BRACE statement* RIGHT_BRACE;

funcCall: VARIABLE LEFT_PAREN paramCallList* RIGHT_PAREN;

constructorCall: TYPE LEFT_PAREN paramCallList* RIGHT_PAREN;

explicitVarDecList: explicitVarDec (COMMA explicitVarDec)*;

explicitVarDec: VARIABLE COLON TYPE (EQUAL expr)?;

implicitVarDec: VARIABLE (EQUAL expr)?;

paramCall: (VARIABLE EQUAL)? expr;

paramCallList: paramCall (COMMA paramCall)*;

statement:
        explicitVarDec
    |   implicitVarDec
    |   if_statement
    |   expr
    ;

expr:
        binary_expr
    |   unary_expr
    |   selection
    ;

binary_expr:
        unary_expr (STAR | SLASH) expr
    |   unary_expr (PLUS | MINUS) expr
    ;

unary_expr:
        funcCall
    |   constructorCall
    |   INTEGER
    |   FLOAT
    |   BOOL
    |   STRING
    |   VARIABLE
    ;

selection:
        unary_expr (DOT unary_expr)*
    ;

if_statement:
    IF expr LEFT_BRACE statement* RIGHT_BRACE
    ;

LEFT_PAREN: '(';
RIGHT_PAREN: ')';
LEFT_BRACE: '{';
RIGHT_BRACE: '}';
LEFT_BRACKET: '[';
RIGHT_BRACKET: ']';
LEFT_ANGLE: '<';
RIGHT_ANGLE: '>';

COMMA: ',';
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
VARIABLE: [a-z_] [a-zA-Z0-9_]*;
TYPE: [A-Z] [a-zA-Z0-9_]*;
CONST: [A-Z0-9_]+;
STRING: '"' ( ~["\\] | '\\' . )* '"';
LINE_COMMENT: '//' ~( '\r' | '\n' )* -> skip;
BLOCK_COMMENT: '///' .*? '///' -> skip;
WS: [ \t\r\n]+ -> skip;