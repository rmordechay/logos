#pragma once
#include "configs/LgsErrors.h"
#include <llvm/IR/DebugInfoMetadata.h>

class LgsType;

namespace llvm {
    class Value;
}

class LgsVariable;
class LgsExpr;
class LgsLLVMGen;
class LgsFunc;

class LgsValue {
public:
    llvm::Value* IRValue = nullptr;
    LgsLocation location{0, 0, 0};

    void setIRValue(llvm::Value* value);
    virtual std::string pname(); // pretty name
    virtual llvm::Value* loadIR(LgsLLVMGen& cg);
    virtual void setDebugValue(LgsLLVMGen& cg);
    virtual json::value asJSON() = 0;
    llvm::DILocation* getDebugLoc(LgsLLVMGen& cg) const;
    virtual ~LgsValue() = default;
};
