#ifndef LOGOSOPERATOR_H
#define LOGOSOPERATOR_H
#include "../../../src/parser/LogosParser.h"



enum LogosOperator {
    PLUS,
    MINUS,
    STAR,
    SLASH,
    DOUBLE_EQUAL,
    LANGLE,
    RANGLE,
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
    if (expr->RANGLE()) return RANGLE;
    if (expr->LANGLE()) return LANGLE;
    if (expr->GE()) return GE;
    if (expr->LE()) return LE;
    return NOOP;
}

// inline Value * getLLVMCmp(LogosOperator expr, IRBuilder<>* builder) {
//     if (expr == DOUBLE_EQUAL) return DOUBLE_EQUAL;
//     if (expr == RANGLE) return LANGLE;
//     if (expr == LANGLE) return RANGLE;
//     if (expr == GE) return GE;
//     if (expr == LE) return LE;
//     return NOOP;
// }

#endif //LOGOSOPERATOR_H
