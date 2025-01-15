#ifndef CODEGENERATION_H
#define CODEGENERATION_H
#include "types/LogosType.h"
#include <llvm/IR/IRBuilder.h>
#include <codegen/StackFrame.h>

using namespace llvm;
using namespace std;

class CodeGeneration {
public:
    virtual ~CodeGeneration() = default;
    virtual Value* getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame) = 0;
    virtual const LogosType& getType() const = 0;
};

#endif //CODEGENERATION_H
