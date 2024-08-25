#ifndef TREE_H
#define TREE_H
#include "token_types.h"


/**
 *
 */
typedef struct Identifier {
    char *name;
} Identifier;

/**
 *
 */
typedef struct ConstantVariable {
    char *name;
} ConstantVariable;

/**
 *
 */
typedef struct ConstantVariableList {
    ConstantVariable **constant_variables;
    int count;
} ConstantVariableList;

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
typedef struct EnumDeclaration {
    Type *type;
    ConstantVariableList *const_var_list;
} EnumDeclaration;

/**
 *
 */
typedef struct VariableDec {
    Type *type;
    Identifier *identifier;
} VariableDec;

/**
 *
 */
typedef struct VariableDecList {
    VariableDec **var_declarations;
    int count;
} VariableDecList;

/**
 *
 */
typedef struct Enum {
    char *name;
    char *string;
} Enum;

/**
 *
 */
typedef struct EnumBlock {
    Enum **enums;
    int count;
} EnumBlock;

/**
 *
 */
typedef struct ObjectField {
    VariableDec *variable_declaration;
    Type *implements;  // Optional
} ObjectField;

/**
 *
 */
typedef struct ObjectFieldList {
    ObjectField **fields;
    int count;
} ObjFieldList;

/**
 *
 */
typedef struct InterfaceField {
    VariableDec *variable_declaration;
} InterfaceField;

/**
 *
 */
typedef struct InterfaceFieldList {
    InterfaceField **fields;
    int count;
} InterfaceFieldList;

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
    ExprType type;
    union {
        struct UnaryExpr *unary_expr;
        struct BinaryExpr *binary_expr;
    };
} Expr;

/**
 *
 */
typedef struct ExprList {
    Expr **exprs;
    int count;
} ExprList;

/**
 *
 */
typedef struct MethodCall {
    struct MethodSignature *method_signature;
    ExprList *param_exprs;
} MethodCall;

/**
 *
 */
typedef struct Collection {
    Type *type;
    int size;
    ExprList *expr_list;
} Collection;

/**
 *
 */
typedef struct UnaryExpr {
    UnaryExprType type;
    union {
        char *integer_value;
        char *float_value;
        Identifier *identifier;
        char *string;
        int boolean;
        MethodCall *method_call;
        Collection *collection;
    };
} UnaryExpr;

/**
 *
 */
typedef struct Number {
    NumberType type;
    union {
        int bool_value;
        short short_value;
        unsigned short ushort_value;
        int int_value;
        unsigned int uint_value;
        long long long_value;
        unsigned long long ulong_value;
        float float_value;
        double double_value;
    };
} Number;

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
    Type *type;
    Identifier *identifier;
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
typedef struct Pattern {
    Expr *condition;
    PatternBodyType type;
    union {
        struct StatementList *statement_list;
        Expr *expr;
    };
} Pattern;

/**
 *
 */
typedef struct PatternList {
    Pattern **patterns;
    int count;
} PatternList;

/**
 *
 */
typedef struct PatternMatching {
    PatternList *pattern_list;
} PatternMatching;

/**
 *
 */
typedef struct PatternMatchingExpr {
    Expr *expr;
    PatternList *pattern_list;
} PatternMatchingExpr;

/**
 *
 */
typedef struct WhileLoop {
    ExprList *expr_list;
} WhileLoop;

/**
 *
 */
typedef struct ForInLoop {
    ExprList *expr_list;
    Expr *in_expr;
} ForInLoop;


/**
 *
 */
typedef struct ReturnStatement {
    ExprList *expr_list;
} ReturnStatement;

/**
 *
 */
typedef struct Iteration {
    IterationType type;
    union {
        ForInLoop *for_in_loop;
        WhileLoop *while_loop;
    };
    struct StatementList *statement_list;
} Iteration;

/**
 *
 */
typedef struct Statement {
    StatementType type;
    union {
        LocalDeclaration *local_declaration;
        IfStatement *if_statement;
        PatternMatching *pattern_matching;
        PatternMatchingExpr *pattern_matching_expr;
        Iteration *iteration;
        ReturnStatement *return_statement;
        EnumDeclaration *enum_declaration;
        Expr *break_expr;
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
typedef struct MethodSignature {
    VariableDec *method_variable;
    VariableDecList *param_list;  // Optional
} MethodSignature;

/**
 *
 */
typedef struct ObjectMethod {
    char **name;
    MethodSignature *method_signature;
    StatementList *statement_list;
} ObjectMethod;

/**
 *
 */
typedef struct ObjectMethodsList {
    ObjectMethod **methods;
    int count;
} ObjectMethodsList;

/**
 *
 */
typedef struct ObjectMethodsBlock {
    Type *identifier;
    ObjectMethodsList *methods_list;
} ObjectMethodsBlock;

/**
 *
 */
typedef struct ObjectMethodsBlockList {
    ObjectMethodsBlock **blocks;
    int count;
} ObjMethodsBlockList;

/**
 *
 */
typedef struct InterfaceMethod {
    char **name;
    MethodSignature *method_signature;
    StatementList *statement_list;  // Optional
} InterfaceMethod;

/**
 *
 */
typedef struct InterfaceMethodsList {
    InterfaceMethod **methods;
    int count;
} InterfaceMethodsList;

/**
 *
 */
typedef struct InterfaceMethodsBlock {
    Type *identifier;
    InterfaceMethodsList *methods_list;
} InterfaceMethodsBlock;

/**
 *
 */
typedef struct InterfaceMethodsBlockList {
    InterfaceMethodsBlock **blocks;
    int count;
} InterfaceMethodsBlockList;


/**
 *
 */
typedef struct ObjectEntity {
    Type *id;
    ObjFieldList *field_list;
    ImplementsBlock *implements_block;
    ObjMethodsBlockList *methods_block_list;
} ObjectEntity;

/**
 *
 */
typedef struct InterfaceEntity {
    Type *id;
    InterfaceFieldList *field_list;
} InterfaceEntity;

/**
 *
 */
typedef struct Entity {
    EntityType type;
    union {
        ObjectEntity *object_entity;
        InterfaceEntity *interface_entity;
    };
} Entity;

void analyse_ast(Entity *entity);
Entity *create_entity(EntityType entity_type, void *entity_tree);

ObjectEntity *create_object_entity(Type *type, ImplementsBlock *implements_block, ObjFieldList *fields_list, ObjMethodsBlockList *methods_block_list);
InterfaceEntity *create_interface_entity(Type *type, InterfaceFieldList *fields_list);
ImplementsBlock *create_implements_block(TypeList *type_list);
// Object Field
ObjFieldList *create_object_field_list(ObjectField *field);
ObjFieldList *add_object_field(ObjFieldList *list, ObjectField *element);
ObjectField *create_object_field(VariableDec *variable_declaration, Type *type);
InterfaceFieldList *create_interface_field_list(InterfaceField *field);
InterfaceFieldList *add_interface_field(InterfaceFieldList *list, InterfaceField *element);
InterfaceField *create_interface_field(VariableDec *variable_declaration);
MethodSignature *create_method_signature(VariableDec *variable_dec, VariableDecList *variable_declaration_list);
// Methods
ObjectMethodsBlock *create_object_methods_block(Type *type, ObjectMethodsList *methods_list);
ObjMethodsBlockList *create_object_methods_block_list(ObjectMethodsBlock *methodBlock);
ObjMethodsBlockList *add_object_methods_block(ObjMethodsBlockList *list, ObjectMethodsBlock *element);
ObjectMethodsList *create_object_methods_list(ObjectMethod *method);
ObjectMethodsList *add_object_method(ObjectMethodsList *list, ObjectMethod *element);
ObjectMethod *create_object_method(MethodSignature *method_signature, StatementList *statement_list);
InterfaceMethodsBlock *create_interface_methods_block(Type *type, InterfaceMethodsList *methods_list);
InterfaceMethodsBlockList *create_interface_methods_block_list(InterfaceMethodsBlock *methodBlock);
InterfaceMethodsBlockList *add_interface_methods_block(InterfaceMethodsBlockList *list, InterfaceMethodsBlock *element);
InterfaceMethod *create_interface_method(MethodSignature *method_signature, StatementList *statement_list);
InterfaceMethodsList *create_interface_methods_list(InterfaceMethod *method);
InterfaceMethodsList *add_interface_method(InterfaceMethodsList *list, InterfaceMethod *element);
// Statement
StatementList *create_statement_list(Statement *statement);
StatementList *add_statement(StatementList *list, Statement *element);
Statement *create_stmt_from_local_dec(LocalDeclaration *local_declaration);
Statement *create_stmt_from_if_stmt(IfStatement *if_statement);
Statement *create_stmt_from_pm(PatternMatching *pattern_matching);
Statement *create_stmt_from_pme(PatternMatchingExpr *pattern_matching_expr);
Statement *create_stmt_from_iteration(Iteration *iteration);
Statement *create_stmt_from_return(ReturnStatement *return_statement);
Statement *create_stmt_from_break(Expr *break_expr);
Statement *create_stmt_from_continue();
Statement *create_stmt_from_enum(EnumDeclaration *enum_declaration);
// Declaration
LocalDeclaration *create_local_declaration(Type *type, Identifier *identifier, Expr *expr);
VariableDecList *create_var_dec_list(VariableDec *variable_dec);
VariableDec *create_variable_declaration(Type *type, Identifier *identifier);
VariableDecList *add_var_dec(VariableDecList *list, VariableDec *element);
// If statement
IfStatement *create_if_statement(IfBlock *if_block, IfOrBlockList *if_or_block_list, OrBlock *or_block);
IfBlock *create_if_block(Expr *expr, StatementList *statement_list);
IfOrBlockList *create_if_or_block_list(IfOrBlock *if_or_block);
IfOrBlockList *add_if_or_block(IfOrBlockList *list, IfOrBlock *element);
IfOrBlock *create_if_or_block(Expr *expr, StatementList *statement_list);
OrBlock *create_or_block(StatementList *statement_list);
// Pattern matching
PatternMatchingExpr *create_pattern_matching_expr(Expr *condition, PatternList *pattern_list);
PatternMatching *create_pattern_matching(PatternList *pattern_list);
Pattern *create_pattern_from_stmt_list(Expr *condition, StatementList *statement_list);
Pattern *create_pattern_from_expr(Expr *condition, Expr *expr);
PatternList *create_pattern_list(Pattern *pattern);
PatternList *add_pattern(PatternList *list, Pattern *element);
// For loop
Iteration *create_iteration_from_for_in(ForInLoop *for_in_loop, StatementList *statement_list);
Iteration *create_iteration_from_while(WhileLoop *while_loop, StatementList *statement_list);
Iteration *create_iteration_from_inf_loop(StatementList *statement_list);
ForInLoop *create_for_in_loop(ExprList *expr_list, Expr *in_expr);
WhileLoop *create_while_loop(ExprList *expr_list);
// Return statement
ReturnStatement *create_return_statement(ExprList *expr_list);
// Expression
Expr *create_expr_from_unary(UnaryExpr *unary_expr);
Expr *create_expr_from_binary(BinaryExpr *binary_expr);
ExprList *create_expr_list(Expr *expr);
ExprList *add_expr(ExprList *list, Expr *element);
BinaryExpr *create_binary_expr(Expr *left, Expr *right, char operator);
UnaryExpr *create_unary_expr_from_number(int type, char *integer_value);
UnaryExpr *create_unary_expr_from_id(Identifier *identifier);
UnaryExpr *create_unary_expr_from_string(char *string);
UnaryExpr *create_unary_expr_from_method_call(MethodCall *method_call);
UnaryExpr *create_unary_expr_from_collection(Collection *collection);
MethodCall *create_method_call(MethodSignature *method_signature, ExprList *param_exprs);
// Collection
Collection *create_collection(Type *type, ExprList *expr_list);
// Enum
EnumDeclaration *create_enum_declaration(Type *type, ConstantVariableList *const_var_list);
// Primitives
Identifier *create_identifier(char *name);
ConstantVariable *create_constant_variable(char *name);
ConstantVariableList *create_const_var_list(ConstantVariable *constant_variable);
ConstantVariableList *add_const_var(ConstantVariableList *list, ConstantVariable *element);
Type *create_type(char *name);
TypeList *create_type_list(Type *type);
TypeList *add_type(TypeList *list, Type *element);

void free_entity(Entity *obj);
void free_object_file(ObjectEntity *obj);
void free_implements_block(ImplementsBlock *ib);
void free_object_field_list(ObjFieldList *fl);
void free_object_field(ObjectField *f);
void free_methods_block_list(ObjMethodsBlockList *mbl);
void free_methods_block(ObjectMethodsBlock *mb);
void free_methods_list(ObjectMethodsList *ml);
void free_method(ObjectMethod *m);
void free_method_signature(MethodSignature *ms);
void free_statement_list(StatementList *sl);
void free_statement(Statement *s);
void free_local_declaration(LocalDeclaration *ld);
void free_if_statement(IfStatement *is);
void free_if_block(IfBlock *ib);
void free_if_or_block(IfOrBlock *iob);
void free_if_or_block_list(IfOrBlockList *iobl);
void free_or_block(OrBlock *ob);
void free_pattern(Pattern *p);
void free_pattern_list(PatternList *pl);
void free_pattern_matching(PatternMatching *pm);
void free_pattern_matching_expr(PatternMatchingExpr *pme);
void free_iteration(Iteration *fl);
void free_for_in_loop(ForInLoop *fli);
void free_while_loop(WhileLoop *wl);
void free_return_statement(ReturnStatement *rs);
void free_expr(Expr *e);
void free_expr_list(ExprList *el);
void free_binary_expr(BinaryExpr *be);
void free_unary_expr(UnaryExpr *ue);
void free_variable_declaration_list(VariableDecList *vdl);
void free_variable_declaration(VariableDec *vd);
void free_collection(Collection *c);
void free_enum_declaration(EnumDeclaration *ed);
void free_type(Type *t);
void free_type_list(TypeList *tl);
void free_const_variable(ConstantVariable *cv);
void free_const_variable_list(ConstantVariableList *cvl);
void free_identifier(Identifier *i);

#endif //TREE_H
