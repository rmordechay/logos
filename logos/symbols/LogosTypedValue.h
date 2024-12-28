#ifndef LOGOSTYPE_H
#define LOGOSTYPE_H
#include "LogosParser.h"

class LogosTypedValue {
public:
    virtual LogosTypedValue* applyOperation(LogosTypedValue* other) = 0;
    virtual std::string getName() const = 0;
    virtual ~LogosTypedValue() = default;
};

#endif //LOGOSTYPE_H
