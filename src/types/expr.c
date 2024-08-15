#include <stdlib.h>
#include "expr.h"

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
void free_expr(Expr *expr) {
    free(expr->value);
    free(expr);
}
