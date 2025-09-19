#pragma once
#include "data/LgsErrors.h"
#include <llvm/IR/DebugInfoMetadata.h>

namespace llvm {
    class Value;
}

class LgsType;
class LgsVariable;
class LgsExpr;
class LgsLLVMGen;
class LgsFunc;

class LgsValue {
public:
    bool isOwner = false;
    llvm::Value* IRValue = nullptr;
    LgsLocation location{0, 0, 0};

    virtual std::string pname(); // pretty name
    virtual llvm::Value* loadIR(LgsLLVMGen& cg);
    virtual void setDebugValue(LgsLLVMGen& cg);
    virtual json::value asJSON() = 0;
    llvm::DILocation* getDebugLoc(LgsLLVMGen& cg) const;
    virtual ~LgsValue() = default;
};
