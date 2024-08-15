#include <stdlib.h>
#include "types.h"


/**
 *
 */
Expr *create_expr() {
    Expr *expr = malloc(sizeof(Expr));
    expr->value = NULL;
    return expr;
}

/**
 *
 */
UnaryExpr *create_unary_expr() {
    UnaryExpr *unary_expr = malloc(sizeof(UnaryExpr));
    unary_expr->expr = NULL;
    unary_expr->op = 0;
    return unary_expr;
}

/**
 *
 */
BinaryExpr *create_binary_expr() {
    BinaryExpr *binary_expr = malloc(sizeof(BinaryExpr));
    binary_expr->left_expr = NULL;
    binary_expr->right_expr = NULL;
    binary_expr->op = 0;
    return binary_expr;
}

/**
 *
 */
void free_expr(Expr *expr) {
    if (!expr) return;
    if (expr->expr_type == UNARY) {
        free_unary_expr(expr->e.unary_expr);
    } else if (expr->expr_type == BINARY) {
        free_binary_expr(expr->e.binary_expr);
    }
    free(expr);
}

/**
 *
 */
void free_unary_expr(UnaryExpr *unary_expr) {
    if (unary_expr->expr) {
        free_expr(unary_expr->expr);
    }
    free(unary_expr);
}

/**
 *
 */
void free_binary_expr(BinaryExpr *binary_expr) {
    if (binary_expr->left_expr) {
        free_expr(binary_expr->left_expr);
    }
    if (binary_expr->right_expr) {
        free_expr(binary_expr->right_expr);
    }
    free(binary_expr);
}

/**
 *
 */
void evaluate(Expr* expr) {
    switch (expr->expr_type) {
        case UNARY: {
            UnaryExpr* unaryExpr = (UnaryExpr*)expr;
            break;
        }
        case BINARY: {
            BinaryExpr* binaryExpr = (BinaryExpr*)expr;
            break;
        }
        default: return;
    }
}