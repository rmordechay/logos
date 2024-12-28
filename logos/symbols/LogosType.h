#ifndef LOGOSTYPE_H
#define LOGOSTYPE_H
#include "LogosParser.h"

class LogosType {
public:
    virtual ~LogosType() = default;
    LogosType *inferBinaryType(LogosType *other, LogosParser::BinaryExprContext* binaryExpr);
    virtual std::string getName() const = 0;
};

#endif //LOGOSTYPE_H
