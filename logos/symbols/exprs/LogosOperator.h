#ifndef LOGOSOPERATOR_H
#define LOGOSOPERATOR_H
#include "../../parser/LogosParser.h"

enum LogosOperator {
    PLUS,
    MINUS,
    STAR,
    SLASH,
    DOUBLE_EQUAL,
    RBRACK,
    LBRACK,
    GE,
    LE,
    NOOP,
};

inline LogosOperator mapOperator(LogosParser::ExprContext* expr) {
    if (expr->PLUS()) return PLUS;
    if (expr->MINUS()) return MINUS;
    if (expr->STAR()) return STAR;
    if (expr->SLASH()) return SLASH;
    if (expr->DOUBLE_EQUAL()) return DOUBLE_EQUAL;
    if (expr->RBRACK()) return RBRACK;
    if (expr->LBRACK()) return LBRACK;
    if (expr->GE()) return GE;
    if (expr->LE()) return LE;
    return NOOP;
}

#endif //LOGOSOPERATOR_H
