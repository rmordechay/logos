#ifndef LOGOSOPERATOR_H
#define LOGOSOPERATOR_H
#include "parser/LogosParser.h"

enum LgsOperator {
    ADD,
    SUB,
    MUL,
    DIV,
    NE,
    EQ,
    LT,
    GT,
    GE,
    LE,
    AND,
    OR,
    NOOP,
};

inline LgsOperator mapOperator(LogosParser::ExprContext* expr) {
    if (expr->PLUS()) return ADD;
    if (expr->MINUS()) return SUB;
    if (expr->STAR()) return MUL;
    if (expr->SLASH()) return DIV;
    if (expr->NOT_EQUAL()) return NE;
    if (expr->DOUBLE_EQUAL()) return EQ;
    if (expr->RANGLE()) return GT;
    if (expr->LANGLE()) return LT;
    if (expr->GE()) return GE;
    if (expr->LE()) return LE;
    if (expr->AND()) return AND;
    if (expr->OR()) return OR;
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
