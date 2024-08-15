#ifndef MYLANG_EXPR_H
#define MYLANG_EXPR_H

typedef struct Expression {
    char *value;
} Expr;

Expr *create_expr();
void free_expr(Expr *expr);

#endif //MYLANG_EXPR_H
