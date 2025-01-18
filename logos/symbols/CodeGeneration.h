#ifndef CODEGENERATION_H
#define CODEGENERATION_H
#include "types/LogosType.h"
#include <llvm/IR/IRBuilder.h>
#include <codegen/StackFrame.h>

using namespace llvm;
using namespace std;

class CodeGeneration {
public:
    virtual Value* getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) = 0;
    virtual ~CodeGeneration() = default;
};

#endif //CODEGENERATION_H
