#ifndef TREE_H
#define TREE_H

typedef enum ExprType {
    UNARY,
    BINARY,
} ExprType;

typedef enum StmtType {
    LOCAL_DEC,
    IF_STMT,
} StmtType;

/**
 *
 */
typedef struct Identifier {
    char *name;
} Identifier;

/**
 *
 */
typedef struct Type {
    char *name;
} Type;

/**
 *
 */
typedef struct TypeList {
    Type **types;
    int count;
} TypeList;

/**
 *
 */
typedef struct VariableDeclaration {
    Type *type;
    Identifier *identifier;
} VariableDec;

/**
 *
 */
typedef struct VariableDeclarationList {
    VariableDec **declarations;
    int count;
} VarDecList;

/**
 *
 */
typedef struct Field {
    VariableDec *variable_declaration;
    Type *implements;  // Optional
} Field;

/**
 *
 */
typedef struct FieldList {
    Field **fields;
    int count;
} FieldList;

/**
 *
 */
typedef struct FieldsBlock {
    FieldList *field_list;
} FieldsBlock;

/**
 *
 */
typedef struct ImplementsBlock {
    TypeList *type_list;
} ImplementsBlock;

/**
 *
 */
typedef struct Expr {
    int type;
    union {
        struct UnaryExpr *unary_expr;
        struct BinaryExpr *binary_expr;
    };
} Expr;

/**
 *
 */
typedef struct UnaryExpr {
    ExprType type;
    union {
        char *integer_value;
        char *float_value;
        Identifier *identifier;
    };
} UnaryExpr;

/**
 *
 */
typedef struct BinaryExpr {
    Expr *left;
    Expr *right;
    char operator;
} BinaryExpr;

/**
 *
 */
typedef struct LocalDeclaration {
    VariableDec *variable_declaration;
    Expr *expr;
} LocalDeclaration;

/**
 *
 */
typedef struct IfBlock {
    Expr *expr;
    struct StatementList *statement_list;
} IfBlock;

/**
 *
 */
typedef struct IfOrBlock {
    Expr *expr;
    struct StatementList *statement_list;
} IfOrBlock;

/**
 *
 */
typedef struct IfOrBlockList {
    IfOrBlock **if_or_blocks;
    int count;
} IfOrBlockList;

/**
 *
 */
typedef struct OrBlock {
    struct StatementList *statement_list;
} OrBlock;


/**
 *
 */
typedef struct IfStatement {
    IfBlock *if_block;
    IfOrBlockList *if_or_block_list;
    OrBlock *or_block;
} IfStatement;


/**
 *
 */
typedef struct Statement {
    StmtType type;
    union {
        LocalDeclaration *local_declaration;
        IfStatement *if_statement;
    };
} Statement;

/**
 *
 */
typedef struct StatementList {
    Statement **statements;
    int count;
} StatementList;

/**
 *
 */
typedef struct MethodHeader {
    VariableDec *variable_declaration;
} MethodHeader;

/**
 *
 */
typedef struct MethodSignature {
    MethodHeader *method_header;
    VarDecList *variable_declaration_list;  // Optional
} MethodSignature;

/**
 *
 */
typedef struct Method {
    MethodSignature *method_signature;
    StatementList *statement_list;  // Optional
} Method;

/**
 *
 */
typedef struct MethodsList {
    Method **methods;
    int count;
} MethodsList;

/**
 *
 */
typedef struct MethodsBlock {
    Identifier *identifier;
    MethodsList *methods_list;
} MethodsBlock;

/**
 *
 */
typedef struct MethodsBlockList {
    MethodsBlock **blocks;
    int count;
} MethodsBlockList;


/**
 *
 */
typedef struct ObjectFile {
    Identifier *id;
    FieldsBlock *fields_block;
    ImplementsBlock *implements_block;
    MethodsBlockList *methods_block_list;
} ObjectFile;



void analyse_ast(ObjectFile *root);

ObjectFile *create_object_file(Identifier *identifier, ImplementsBlock *implements_block, FieldsBlock *fields_block, MethodsBlockList *methods_block_list);
ImplementsBlock *create_implements_block(TypeList *type_list);
FieldsBlock *create_fields_block(FieldList *field_list);
FieldList *create_field_list(Field *field);
FieldList *flatten_field_list(FieldList *field_list, Field *field);
Field *create_field(VariableDec *variable_declaration, Type *type);
MethodsBlockList *create_methods_block_list(MethodsBlock *methodBlock);
MethodsBlockList *flatten_methods_block_list(MethodsBlockList *methods_block_list, MethodsBlock *methods_block);
MethodsBlock *create_methods_block(Identifier *identifier, MethodsList *methods_list);
MethodsList *create_methods_list(Method *method);
MethodsList *flatten_methods_list(MethodsList *methods_list, Method *method);
Method *create_method(MethodSignature *method_signature, StatementList *statement_list);
MethodSignature *create_method_signature(MethodHeader *method_header, VarDecList *variable_declaration_list);
MethodHeader *create_method_header(VariableDec *variable_declaration);
StatementList *create_statement_list(Statement *statement);
StatementList *flatten_statement_list(StatementList *statement_list, Statement *statement);
Statement *create_statement(LocalDeclaration *local_declaration);
LocalDeclaration *create_local_declaration(VariableDec *variable_declaration, Expr *expr);
IfStatement *create_if_statement(IfBlock *if_block, IfOrBlockList *if_or_block_list, OrBlock *or_block);
IfBlock *create_if_block(Expr *expr, StatementList *statement_list);
IfOrBlockList *create_if_or_block_list(IfOrBlock *if_or_block);
IfOrBlockList *flatten_if_or_block_list(IfOrBlockList *if_or_block_list, IfOrBlock *if_or_block);
IfOrBlock *create_if_or_block(Expr *expr, StatementList *statement_list);
OrBlock *create_or_block(StatementList *statement_list);
Expr *create_expr_from_unary(UnaryExpr *unary_expr);
Expr *create_expr_from_binary(BinaryExpr *binary_expr);
BinaryExpr *create_binary_expr(Expr *left, Expr *right, char operator);
UnaryExpr *create_unary_expr_number(int type, char *integer_value);
UnaryExpr *create_unary_expr_id(Identifier *identifier);
VarDecList *create_var_dec_list(VariableDec *variable_dec);
VarDecList *flatten_var_dec_list(VarDecList *var_dec_list, VariableDec *variable_dec);
VariableDec *create_variable_declaration(Type *type, Identifier *identifier);
Identifier *create_identifier(const char *name);
Type *create_type(const char *name);
TypeList *create_type_list(Type *type);
TypeList *flatten_type_list(TypeList *type_list, Type *type);

void free_object_file(ObjectFile *obj);
void free_implements_block(ImplementsBlock *ib);
void free_fields_block(FieldsBlock *fb);
void free_field_list(FieldList *fl);
void free_field(Field *f);
void free_methods_block_list(MethodsBlockList *mbl);
void free_methods_block(MethodsBlock *mb);
void free_methods_list(MethodsList *ml);
void free_method(Method *m);
void free_method_signature(MethodSignature *ms);
void free_method_header(MethodHeader *mh);
void free_statement_list(StatementList *sl);
void free_statement(Statement *s);
void free_local_declaration(LocalDeclaration *ld);
void free_if_statement(IfStatement *is);
void free_if_block(IfBlock *ib);
void free_if_or_block(IfOrBlock *iob);
void free_if_or_block_list(IfOrBlockList *iobl);
void free_or_block(OrBlock *ob);
void free_expr(Expr *expr);
void free_binary_expr(BinaryExpr *be);
void free_unary_expr(UnaryExpr *ue);
void free_variable_declaration_list(VarDecList *vdl);
void free_variable_declaration(VariableDec *vd);
void free_identifier(Identifier *i);
void free_type(Type *t);
void free_type_list(TypeList *tl);

#endif //TREE_H
