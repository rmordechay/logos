#ifndef LOGOSTYPE_H
#define LOGOSTYPE_H
#include "LogosParser.h"

enum Operator {
    PLUS,
    MINUS,
    STAR,
    SLASH,
    NOOP,
};

inline Operator mapOperator(LogosParser::BinaryExprContext* binaryExpr) {
    if (binaryExpr->PLUS()) return PLUS;
    if (binaryExpr->MINUS()) return MINUS;
    if (binaryExpr->STAR()) return STAR;
    if (binaryExpr->PLUS()) return PLUS;
    return NOOP;
}

class LogosType {
public:
    virtual ~LogosType() = default;
    LogosType *inferBinaryType(const LogosType *other, Operator op);
    virtual LogosType* inferType(LogosType* other) = 0;
    virtual std::string getName() const = 0;
};

#endif //LOGOSTYPE_H
