#ifndef RUNTIMESTACKFRAME_H
#define RUNTIMESTACKFRAME_H
#include "types/LogosInt.h"

#include <map>
#include <stack>
#include <llvm/IR/Value.h>

using namespace std;
using namespace llvm;

class LogosSymbol {
public:
    int pos = -1;
    Type* symbolType = nullptr;
    Value* symbolValue = nullptr;

    explicit LogosSymbol(Value* symbolValue) : symbolValue(symbolValue) {}
    explicit LogosSymbol(Type* symbolType) : symbolType(symbolType) {}
    explicit LogosSymbol(Type* symbolType, const int position) : pos(position), symbolType(symbolType) {}
    ~LogosSymbol() = default;
};

class LogosStackFrame {
public:
    Function* currentFunction = nullptr;
    map<string, LogosSymbol*> symbolTable;
    map<string, Function*> functions;
};

#endif //RUNTIMESTACKFRAME_H
