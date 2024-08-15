#ifndef MYLANG_EXPR_H
#define MYLANG_EXPR_H


typedef enum Operation {
    ADD = 1,
    SUB,
    MUL,
    DIV,
} Operation;

typedef enum ExprType {
    UNARY = 1,
    BINARY,
} ExprType;

typedef struct Expr {
    char *value;
    ExprType expr_type;
    union {
        struct UnaryExpr* unary_expr;
        struct BinaryExpr* binary_expr;
    } e;
} Expr;

typedef struct UnaryExpr {
    Operation op;
    Expr *expr;
} UnaryExpr;

typedef struct BinaryExpr {
    Operation op;
    Expr *left_expr;
    Expr *right_expr;
} BinaryExpr;

Expr *create_expr();
UnaryExpr *create_unary_expr();
BinaryExpr *create_binary_expr();

void free_expr(Expr *expr);
void free_unary_expr(UnaryExpr *unary_expr);
void free_binary_expr(BinaryExpr *binary_expr);

//void evaluate(Expr* expr) {
//    switch (expr->expr_type) {
//        case UNARY: {
//            UnaryExpr* unaryExpr = (UnaryExpr*)expr;
//            break;
//        }
//        case BINARY: {
//            BinaryExpr* binaryExpr = (BinaryExpr*)expr;
//            break;
//        }
//        default: return;
//    }
//}


#endif //MYLANG_EXPR_H
