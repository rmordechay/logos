#ifndef LOGOSTYPE_H
#define LOGOSTYPE_H

#include <llvm/IR/IRBuilder.h>
#include <symbols/CodeGeneration.h>

class LogosStack;
using namespace llvm;
using namespace std;

class LogosType {
public:
    virtual const string name() const = 0;
    virtual Type* getLLVMType(CodeGenMetadata* metadata) = 0;
    virtual bool operator==(LogosType* other) const = 0;
    virtual ~LogosType() = default;
};

#endif //LOGOSTYPE_H
