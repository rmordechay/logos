#ifndef SYMBOL_H
#define SYMBOL_H

#include "funcs/LogosFunc.h"

using namespace std;

class LogosSymbol {
public:
    CodeGeneration* value;

    explicit LogosSymbol(CodeGeneration* value) : value(value) {}

    ~LogosSymbol() = default;
};


#endif //SYMBOL_H
