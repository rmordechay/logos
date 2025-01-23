#ifndef LOGOSSYMBOL_H
#define LOGOSSYMBOL_H

#include <stack>
#include <llvm/IR/Value.h>

using namespace std;
using namespace llvm;

class LogosSymbol {
public:
    int pos = -1;
    Type* llvmType = nullptr;
    Value* llvmValue = nullptr;

    explicit LogosSymbol() = default;
    explicit LogosSymbol(Value* symbolValue) : llvmValue(symbolValue) {}
    explicit LogosSymbol(Type* symbolType) : llvmType(symbolType) {}
    explicit LogosSymbol(Type* symbolType, const int position) : pos(position), llvmType(symbolType) {}
    ~LogosSymbol() = default;
};

#endif //LOGOSSYMBOL_H
