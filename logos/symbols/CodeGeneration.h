#ifndef CODEGENERATION_H
#define CODEGENERATION_H
#include "LogosStack.h"
#include "types/LogosType.h"
#include <llvm/IR/IRBuilder.h>
#include <codegen/LogosStackFrame.h>

using namespace llvm;
using namespace std;

class CodeGeneration {
public:
    virtual Value* getLLVMValue(IRBuilder<>* builder, LogosStack* stack, Module* module) = 0;
    virtual ~CodeGeneration() = default;
};

#endif //CODEGENERATION_H
