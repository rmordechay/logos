#ifndef LOGOSOPERATOR_H
#define LOGOSOPERATOR_H

enum LogosOperator {
    PLUS,
    MINUS,
    STAR,
    SLASH,
    NOOP,
};

inline LogosOperator mapOperator(LogosParser::ExprContext* expr) {
    if (expr->PLUS()) return PLUS;
    if (expr->MINUS()) return MINUS;
    if (expr->STAR()) return STAR;
    if (expr->PLUS()) return PLUS;
    return NOOP;
}

#endif //LOGOSOPERATOR_H
