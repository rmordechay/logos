#ifndef CODEGENERATION_H
#define CODEGENERATION_H
#include "LogosStack.h"
#include "types/LogosType.h"
#include <llvm/IR/IRBuilder.h>

using namespace llvm;
using namespace std;

struct Position {
    int lineNumber;
    int posInLine;
    Position(const int lineNumber, const int posInLine) : lineNumber(lineNumber), posInLine(posInLine) {}
};

class CodeGeneration {
public:
    Position *position = nullptr;
    virtual Value* getLLVMValue(IRBuilder<>* builder, LogosStack* stack, Module* module) = 0;
    virtual ~CodeGeneration();
};

inline CodeGeneration::~CodeGeneration() {
    delete position;
}

#endif //CODEGENERATION_H
