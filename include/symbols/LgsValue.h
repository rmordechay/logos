#pragma once
#include "configs/LgsErrors.h"

#include <llvm/IR/DebugInfoMetadata.h>

class LgsType;

namespace llvm {
    class Value;
}

class LgsVariable;
class LgsExpr;
class LgsCodeGen;
class LgsFunc;

class LgsValue {
public:
    llvm::Value* IRValue = nullptr;
    LgsLocation location{0, 0, 0};

    void setIRValue(llvm::Value* value);
    virtual void setDebugValue(LgsCodeGen& codeGen);
    virtual json::value asJSON() = 0;
    virtual ~LgsValue() = default;
    llvm::DILocation* getDebugLoc(LgsCodeGen& codeGen) const;
};
