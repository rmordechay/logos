#ifndef SYMBOL_H
#define SYMBOL_H

#include "exprs/LogosExpr.h"
#include "funcs/LogosFunc.h"

#include <string>

using namespace std;

class LogosSymbol {
public:
    const LogosType& type;
    using Value = variant<LogosExpr, LogosFunc>;
    Value value;

    LogosSymbol(const LogosType& type, const Value& value) : type(type), value(value) {}
    ~LogosSymbol() = default;
};


#endif //SYMBOL_H
