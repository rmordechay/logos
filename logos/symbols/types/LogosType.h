#ifndef LOGOSTYPE_H
#define LOGOSTYPE_H

#include <llvm/IR/IRBuilder.h>

using namespace llvm;

class LogosType {
public:
    virtual Type* getLLVMType(IRBuilder<>& builder) const = 0;
    virtual ~LogosType() = default;
};

#endif //LOGOSTYPE_H
