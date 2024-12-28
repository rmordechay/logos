#ifndef LOGOSOPERATOR_H
#define LOGOSOPERATOR_H
#include "LogosParser.h"

enum LogosOperator {
    PLUS,
    MINUS,
    STAR,
    SLASH,
    NOOP,
};

inline LogosOperator mapOperator(LogosParser::BinaryExprContext* binaryExpr) {
    if (binaryExpr->PLUS()) return PLUS;
    if (binaryExpr->MINUS()) return MINUS;
    if (binaryExpr->STAR()) return STAR;
    if (binaryExpr->PLUS()) return PLUS;
    return NOOP;
}

#endif //LOGOSOPERATOR_H
