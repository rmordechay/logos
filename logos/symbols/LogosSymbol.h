#ifndef SYMBOL_H
#define SYMBOL_H

#include "funcs/LogosFunc.h"

using namespace std;

class LogosSymbol {
public:
    const LogosType* type;
    CodeGeneration* value;

    explicit LogosSymbol(CodeGeneration* value) : type(&value->getType()), value(value) {}

    ~LogosSymbol() = default;
};


#endif //SYMBOL_H
