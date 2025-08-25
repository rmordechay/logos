#pragma once
#include "configs/LgsErrors.h"
#include <llvm/IR/DebugInfoMetadata.h>

class LgsType;

namespace llvm {
    class Value;
}

class LgsVariable;
class LgsExpr;
class LgsLLVM;
class LgsFunc;

class LgsValue {
public:
    llvm::Value* IRValue = nullptr;
    LgsLocation location{0, 0, 0};

    void setIRValue(llvm::Value* value);
    virtual llvm::Value* loadIR(LgsLLVM& codeGen);
    virtual void setDebugValue(LgsLLVM& codeGen);
    virtual json::value asJSON() = 0;
    llvm::DILocation* getDebugLoc(LgsLLVM& codeGen) const;
    virtual ~LgsValue() = default;
};
