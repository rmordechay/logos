#ifndef RUNTIMESTACKFRAME_H
#define RUNTIMESTACKFRAME_H
#include "LogosSymbol.h"
#include "types/LogosInt.h"

#include <map>

class LogosStackFrame {
public:
    Function* currentFunction = nullptr;
    map<string, LogosSymbol*> symbolTable;
    map<string, Function*> functions;
};

#endif //RUNTIMESTACKFRAME_H
