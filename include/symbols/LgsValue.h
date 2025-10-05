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
    LgsLocation location{0, 0, 0};

    virtual LgsType* getType();
    virtual std::string getName();
    virtual Value* loadIR(LgsLLVMGen& cg);
    virtual void setDebugValue(LgsLLVMGen& cg);
    virtual json::value asJsonStr() = 0;
    virtual Value* addIR(LgsLLVMGen& cg, Value* other);
    virtual Value* subIR(LgsLLVMGen& cg, Value* other);
    virtual Value* mulIR(LgsLLVMGen& cg, Value* other);
    virtual Value* divIR(LgsLLVMGen& cg, Value* other);
    virtual Value* eqIR(LgsLLVMGen& cg, Value* other);
    virtual Value* neIR(LgsLLVMGen& cg, Value* other);
    virtual Value* ltIR(LgsLLVMGen& cg, Value* other);
    virtual Value* gtIR(LgsLLVMGen& cg, Value* other);
    virtual Value* geIR(LgsLLVMGen& cg, Value* other);
    virtual Value* leIR(LgsLLVMGen& cg, Value* other);
    virtual Value* andIR(LgsLLVMGen& cg, Value* other);
    virtual Value* orIR(LgsLLVMGen& cg, Value* other);
    DILocation* getDebugLoc(LgsLLVMGen& cg) const;
    virtual ~LgsValue() = default;
};
