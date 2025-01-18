#ifndef RUNTIMESTACKFRAME_H
#define RUNTIMESTACKFRAME_H
#include "types/LogosInt.h"

#include <map>
#include <stack>
#include <llvm/IR/Value.h>

using namespace std;
using namespace llvm;

class RuntimeStackFrame {
public:
    Function *currentFunction;
    map<string, Value*> symbolTable;
    map<string, Function*> functions;
};

#endif //RUNTIMESTACKFRAME_H
