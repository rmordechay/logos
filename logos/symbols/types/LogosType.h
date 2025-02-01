#ifndef LOGOSTYPE_H
#define LOGOSTYPE_H

#include "stmts/LogosVarDec.h"

#include <llvm/IR/IRBuilder.h>

using namespace llvm;

class LogosType {
public:
    virtual const string& name() const = 0;
    virtual Type* getLLVMType(IRBuilder<>* builder) const = 0;
    virtual bool operator==(const LogosType* other) const = 0;
    virtual ~LogosType() = default;
};

#endif //LOGOSTYPE_H
