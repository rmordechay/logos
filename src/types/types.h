#ifndef TYPES_H
#define TYPES_H

#include "config.h"
#include "utils/utils.h"
#include "ast/ast.h"

#define SRC_DIR "src"
#define LOGOS_FILE_EXT "lgs"
#define MAIN_CONFIG_FILE_NAME "Config.lgs"
#define MAIN_FILE_NAME "Main.lgs"
#define PATH_MAX 1024


///**
// *
// */
//typedef enum Operation {
//    ADD = 1,
//    SUB,
//    MUL,
//    DIV,
//} Operation;
//
///**
// *
// */
//typedef enum ExprType {
//    UNARY = 1,
//    BINARY,
//} ExprType;
//
///**
// *
// */
//typedef struct Variable {
//    char *name;
//} Variable;
//
///**
// *
// */
//typedef struct Type {
//    char *name;
//} Type;
//
///**
// *
// */
//typedef struct VariableDec {
//    Variable *variable_name;
//    Type *type;
//} VariableDec;
//
///**
// *
// */
//typedef struct Expr {
//    char *value;
//    ExprType expr_type;
//    union {
//        struct UnaryExpr* unary_expr;
//        struct BinaryExpr* binary_expr;
//    } e;
//} Expr;
//
///**
// *
// */
//typedef struct UnaryExpr {
//    Operation op;
//    Expr *expr;
//} UnaryExpr;
//
///**
// *
// */
//typedef struct BinaryExpr {
//    Operation op;
//    Expr *left_expr;
//    Expr *right_expr;
//} BinaryExpr;
//
///**
// *
// */
//typedef struct LocalDeclaration {
//    VariableDec *variable_dec;
//    Expr *expr;
//} LocalDec;
//
///**
// *
// */
//typedef struct Statement {
//    LocalDec *local_dec;
//} Statement;
//
///**
// *
// */
//typedef struct Interface {
//    char *name;
//} Interface;
//
///**
// *
// */
//typedef struct Field {
//    VariableDec *variable_dec;
//    Interface *interface;
//} Field;
//
///**
// *
// */
//typedef struct Method {
//    VariableDec *var_dec;
//    VariableDec **params;
//    size_t params_len;
//    Statement **statements;
//    size_t statements_len;
//} Method;
//
///**
// *
// */
//typedef struct MethodBlock {
//    char *name;
//    Method **methods;
//    size_t methods_len;
//} MethodBlock;
//
///**
// *
// */
//typedef struct Object {
//    char *name;
//    Interface **interfaces;
//    size_t interfaces_len;
//    Field **fields;
//    size_t fields_len;
//    MethodBlock **method_blocks;
//    size_t method_blocks_len;
//} Object;
//
//Object *create_object();
//Expr *create_expr();
//UnaryExpr *create_unary_expr();
//BinaryExpr *create_binary_expr();
//Field *create_field();
//Interface *create_interface();
//Method *create_method();
//MethodBlock *create_method_block();
//Statement *create_statement();
//LocalDec *create_local_declaration();
//Type *create_type();
//VariableDec *create_variable_declaration();
//Variable *create_variable_name();
//
//void free_object(Object *obj);
//void free_expr(Expr *expr);
//void free_unary_expr(UnaryExpr *unary_expr);
//void free_binary_expr(BinaryExpr *binary_expr);
//void free_field(Field *field);
//void free_interface(Interface *interface);
//void free_method(Method *method);
//void free_method_block(MethodBlock *method_block);
//void free_statement(Statement *stmt);
//void free_local_declaration(LocalDec *local_dec);
//void free_type(Type *type);
//void free_variable_declaration(VariableDec *variable);
//void print_obj(Object *obj);
//
#endif //TYPES_H
