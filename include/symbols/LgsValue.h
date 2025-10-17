#pragma once
#include "data/LgsErrors.h"
#include <llvm/IR/DebugInfoMetadata.h>

namespace llvm {
    class Value;
}

using namespace llvm;

class LgsType;
class LgsVariable;
class LgsExpr;
class LgsLLVMGen;
class LgsFunc;

class LgsValue {
public:
    Value* IRValue = nullptr;
    LgsLocation location;

    virtual std::string asText();
    virtual Value* loadIR(LgsLLVMGen& cg);
    virtual void parseAsJSON(std::stringstream& json);
    virtual void setDebugValue(LgsLLVMGen& cg);
    DILocation* getDebugLoc(LgsLLVMGen& cg) const;
    virtual ~LgsValue() = default;
};
