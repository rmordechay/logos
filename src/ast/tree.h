#ifndef TREE_H
#define TREE_H

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
    Type *type;  // Optional
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
    union {
        struct UnaryExpr *unary_expr;
        struct BinaryExpr *binary_expr;
    };
} Expr;

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
typedef struct UnaryExpr {
    union {
        char *integer_value;
        char *float_value;
        Identifier *identifier;
    };
} UnaryExpr;

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
typedef struct Statement {
    LocalDeclaration *local_declaration;
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
Expr *create_expr_unary(UnaryExpr *unary_expr);
Expr *create_expr_binary(BinaryExpr *binary_expr);
BinaryExpr *create_binary_expr(Expr *left, Expr *right, char operator);
UnaryExpr *create_unary_expr_int(char *integer_value);
UnaryExpr *create_unary_expr_float(char *float_value);
UnaryExpr *create_unary_expr_id(Identifier *identifier);
VarDecList *create_var_dec_list(VariableDec *variable_dec);
VarDecList *flatten_var_dec_list(VarDecList *var_dec_list, VariableDec *variable_dec);
VariableDec *create_variable_declaration(Type *type, Identifier *identifier);
Identifier *create_identifier(const char *name);
Type *create_type(const char *name);
TypeList *create_type_list(Type *type);
TypeList *flatten_type_list(TypeList *type_list, Type *type);

void free_object_file(ObjectFile *obj);
void free_implements_block(ImplementsBlock *implements_block);
void free_fields_block(FieldsBlock *fields_block);
void free_field_list(FieldList *field_list);
void free_field(Field *field);
void free_methods_block_list(MethodsBlockList *methods_block_list);
void free_methods_block(MethodsBlock *methods_block);
void free_methods_list(MethodsList *methods_list);
void free_method(Method *method);
void free_method_signature(MethodSignature *method_signature);
void free_method_header(MethodHeader *method_header);
void free_statement_list(StatementList *statement_list);
void free_statement(Statement *statement);
void free_local_declaration(LocalDeclaration *local_declaration);
void free_expr(Expr *expr);
void free_binary_expr(BinaryExpr *binary_expr);
void free_unary_expr(UnaryExpr *unary_expr);
void free_variable_declaration_list(VarDecList *variable_declaration_list);
void free_variable_declaration(VariableDec *variable_dec);
void free_identifier(Identifier *identifier);
void free_type(Type *type);
void free_type_list(TypeList *type_list);

#endif //TREE_H
