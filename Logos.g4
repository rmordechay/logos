grammar Logos;

entry: object_file | interface_file;

interface_file: interface_declaration object_implements? explicit_var_dec* func_dec+ func_implementation*;

object_file: object_declaration object_implements? explicit_var_dec* func_implementation*;

object_declaration: OBJECT COLON TYPE;

interface_declaration: INTERFACE COLON TYPE;

object_implements: IMPLEMENTS COLON TYPE;

explicit_var_dec: VARIABLE COLON TYPE (EQUAL expr)?;

implicit_var_dec: VARIABLE (EQUAL expr)?;

func_dec: VARIABLE LEFT_PAREN explicit_var_dec_list? RIGHT_PAREN COLON TYPE;

func_implementation: func_dec func_body;

func_body: LEFT_BRACE statement* RIGHT_BRACE;

statement:
        explicit_var_dec
    |   implicit_var_dec
    |   expr
    ;

explicit_var_dec_list: explicit_var_dec (COMMA explicit_var_dec)*;

expr:
        VARIABLE
    |   INTEGER
    |   FLOAT
    |   BOOL
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

BLOCK_COMMENT: '///' .*? '///' -> skip;
LINE_COMMENT: '//' ~[/]* -> skip;
WS: [ \t\r\n]+ -> skip;

INTEGER: [0-9]+;
FLOAT: [0-9]+ '.' [0-9]+;
BOOL: 'true' | 'false';
VARIABLE: [a-z_] [a-zA-Z0-9_]*;
TYPE: [A-Z] [a-zA-Z0-9_]*;
CONST: [A-Z0-9_]+;
STRING: '"' ( ~["\\] | '\\' . )* '"';

