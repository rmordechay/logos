#ifndef RUNTIMESCOPE_H
#define RUNTIMESCOPE_H
#include <map>
#include <llvm/IR/Function.h>

using namespace llvm;
using namespace std;

class RuntimeScope {
public:
    Function* currentFrame = nullptr;
    map<string, Function*> functions;
    map<string, Value*> symbols;
    ~RuntimeScope() = default;
};

#endif //RUNTIMESCOPE_H
