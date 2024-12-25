grammar Logos;

entry: objectFile | interfaceFile;

interfaceFile: interfaceDeclaration objectImplements? explicitVarDec* funcDec+ funcImplementation*;

objectFile: objectDeclaration objectImplements? explicitVarDec* funcImplementation*;

objectDeclaration: OBJECT COLON TYPE;

interfaceDeclaration: INTERFACE COLON TYPE;

objectImplements: IMPLEMENTS COLON TYPE;

explicitVarDecList: explicitVarDec (COMMA explicitVarDec)*;

explicitVarDec: VARIABLE COLON TYPE (EQUAL expr)?;

implicitVarDec: VARIABLE (EQUAL expr)?;

funcDec: VARIABLE LEFT_PAREN explicitVarDecList? RIGHT_PAREN COLON TYPE;

funcCall: VARIABLE LEFT_PAREN expr_list+ RIGHT_PAREN;

funcImplementation: funcDec funcBody;

funcBody: LEFT_BRACE statement* RIGHT_BRACE;

statement:
        explicitVarDec
    |   implicitVarDec
    |   expr
    ;

expr_list: expr (COMMA expr)*;

expr:
        binary_expr
    |   unary_expr
    |   LEFT_PAREN binary_expr RIGHT_PAREN
    |   LEFT_PAREN unary_expr RIGHT_PAREN
    ;

binary_expr:
        unary_expr (STAR | SLASH) expr
    |   unary_expr (PLUS | MINUS) expr
    ;

unary_expr:
        VARIABLE
    |   INTEGER
    |   FLOAT
    |   BOOL
    |   STRING
    |   funcCall
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