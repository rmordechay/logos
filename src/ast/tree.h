#ifndef TREE_H
#define TREE_H

typedef enum {
    N_OBJECT_FILE,
    N_FULL_TITLE,
    N_PRIMARY_TITLE,
    N_SECONDARY_TITLE,
    N_METHODS_BLOCK_LIST,
    N_METHODS_BLOCK,
    N_METHODS_LIST,
    N_METHOD,
    N_METHOD_SIGNATURE,
    N_METHOD_HEADER,
    N_STATEMENT_LIST,
    N_STATEMENT,
    N_LOCAL_DECLARATION,
    N_EXPR,
    N_UNARY_EXPR,
    N_BINARY_EXPR,
    N_ADD_EXPR,
    N_SUB_EXPR,
    N_MUL_EXPR,
    N_DIV_EXPR,
    N_PARAM,
    N_FIELDS_BLOCK,
    N_FIELD_LIST,
    N_FIELD,
    N_VARIABLE_DECLARATION,
    N_VAR_DEC_LIST,
    N_IDENTIFIER,
    N_IDENTIFIER_LIST,
    N_TYPE,
    N_TYPE_LIST,
} NodeType;

typedef struct Node {
    NodeType type;
    int child_count;
    struct Node **children;
    char *value;  // For leaf nodes (like IDENTIFIER, INTEGER, FLOAT)
} Node;

/**
 *
 */
typedef struct ObjectFile {
    struct FullTitle *full_title;
    struct FieldsBlock *fields_block;
    struct MethodsBlockList *methods_block_list;
} ObjectFile;

/**
 *
 */
typedef struct FullTitle {
    struct PrimaryTitle *primary_title;
    struct ImplementsBlock *implements_block;  // Optional
} FullTitle;

/**
 *
 */
typedef struct PrimaryTitle {
    struct Identifier *identifier;
} PrimaryTitle;

/**
 *
 */
typedef struct ImplementsBlock {
    struct TypeList *type_list;
} ImplementsBlock;

/**
 *
 */
typedef struct FieldsBlock {
    struct FieldList *field_list;
} FieldsBlock;

/**
 *
 */
typedef struct FieldList {
    struct Field **fields;
    int count;
} FieldList;

/**
 *
 */
typedef struct Field {
    struct VariableDec *variable_declaration;
    struct Type *type;  // Optional
} Field;

/**
 *
 */
typedef struct MethodsBlockList {
    struct MethodsBlock **blocks;
    int count;
} MethodsBlockList;

/**
 *
 */
typedef struct MethodsBlock {
    struct Identifier *identifier;
    struct MethodsList *methods_list;
} MethodsBlock;

/**
 *
 */
typedef struct MethodsList {
    struct Method **methods;
    int count;
} MethodsList;

/**
 *
 */
typedef struct Method {
    struct MethodSignature *method_signature;
    struct StatementList *statement_list;  // Optional
} Method;

/**
 *
 */
typedef struct MethodSignature {
    struct MethodHeader *method_header;
    struct VariableDeclarationList *variable_declaration_list;  // Optional
} MethodSignature;

/**
 *
 */
typedef struct MethodHeader {
    struct VariableDec *variable_declaration;
} MethodHeader;

/**
 *
 */
typedef struct StatementList {
    struct Statement **statements;
    int count;
} StatementList;

/**
 *
 */
typedef struct Statement {
    struct LocalDeclaration *local_declaration;
} Statement;

/**
 *
 */
typedef struct LocalDeclaration {
    struct VariableDec *variable_declaration;
    struct Expr *expr;
} LocalDeclaration;

/**
 *
 */
typedef struct Expr {
    union {
        struct UnaryExpr *unary_expr;
        struct BinaryExpr *binary_expr;
    };
} Expr;

/**
 *
 */
typedef struct BinaryExpr {
    struct Expr *left;
    struct Expr *right;
    char operator;
} BinaryExpr;

/**
 *
 */
typedef struct UnaryExpr {
    union {
        char *integer_value;
        char *float_value;
        struct Identifier *identifier;
    };
} UnaryExpr;

/**
 *
 */
typedef struct VariableDeclarationList {
    struct VariableDec **declarations;
    int count;
} VariableDeclarationList;

/**
 *
 */
typedef struct VariableDeclaration {
    struct Type *type;
    struct Identifier *identifier;
} VariableDec;

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
    struct Type **types;
    int count;
} TypeList;

void analyse_ast(Node *root);

void free_node(Node *node);
void free_full_title(FullTitle *ft);
void free_object_file(ObjectFile *obj);
void free_primary_title(PrimaryTitle *pt);
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
void free_expr(Expr *e);
void free_binary_expr(BinaryExpr *be);
void free_unary_expr(UnaryExpr *ue);
void free_variable_declaration_list(VariableDeclarationList *vdl);
void free_variable_declaration(VariableDec *vd);
void free_identifier(Identifier *id);
void free_type(Type *t);
void free_type_list(TypeList *tl);

Node *create_node(NodeType type, int child_count);
ObjectFile *create_object_file(FullTitle *full_title, FieldsBlock *fields_block, MethodsBlockList *methods_block_list);
FullTitle *create_full_title(PrimaryTitle *primary_title, ImplementsBlock *implements_block);
PrimaryTitle *create_primary_title(Identifier *identifier);
ImplementsBlock *create_implements_block(TypeList *type_list);
FieldsBlock *create_fields_block(FieldList *field_list);
FieldList *create_field_list(int count);
Field *create_field(VariableDec *variable_declaration, Type *type);
MethodsBlockList *create_methods_block_list(int count);
MethodsBlock *create_methods_block(Identifier *identifier, MethodsList *methods_list);
MethodsList *create_methods_list(int count);
Method *create_method(MethodSignature *method_signature, StatementList *statement_list);
MethodSignature *create_method_signature(MethodHeader *method_header, VariableDeclarationList *variable_declaration_list);
MethodHeader *create_method_header(VariableDec *variable_declaration);
StatementList *create_statement_list(int count);
Statement *create_statement(LocalDeclaration *local_declaration);
LocalDeclaration *create_local_declaration(VariableDec *variable_declaration, Expr *expr);
Expr *create_expr_unary(UnaryExpr *unary_expr);
Expr *create_expr_binary(BinaryExpr *binary_expr);
BinaryExpr *create_binary_expr(Expr *left, Expr *right, char operator);
UnaryExpr *create_unary_expr_int(char *integer_value);
UnaryExpr *create_unary_expr_float(char *float_value);
UnaryExpr *create_unary_expr_id(Identifier *identifier);
VariableDeclarationList *create_variable_declaration_list(int count);
VariableDec *create_variable_declaration(Type *type, Identifier *identifier);
Identifier *create_identifier(const char *name);
Type *create_type(const char *name);
TypeList *create_type_list(int count);

#endif //TREE_H
