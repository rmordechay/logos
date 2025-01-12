#ifndef LOGOSTYPE_H
#define LOGOSTYPE_H

#include <llvm/IR/IRBuilder.h>

using namespace llvm;

class LogosValue {
public:
    virtual std::string getTypeName() const = 0;
    virtual Type* getLLVMType(IRBuilder<>& builder) const = 0;
    virtual Value* getLLVMValue(IRBuilder<>& builder) const = 0;
    virtual ~LogosValue() = default;
};

#endif //LOGOSTYPE_H
