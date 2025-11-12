#pragma once
#include "data/LgsErrors.h"
#include <llvm/IR/DIBuilder.h>

namespace llvm {
    class TargetMachine;
}

class LgsType;
class LgsVariable;
class LgsExpr;
class LgsLLVMGen;
class LgsFunc;
using llvm::Value;
using llvm::Type;

using llvm::DIFile;
using llvm::DICompileUnit;
using llvm::DISubprogram;
using llvm::LLVMContext;
using llvm::Module;
using llvm::GlobalVariable;
using llvm::ConstantInt;
using llvm::ConstantAggregateZero;
using llvm::StructType;
using llvm::Constant;
using llvm::GlobalValue;
using llvm::IntegerType;
using llvm::PointerType;
using llvm::TypeSize;
using llvm::FunctionType;
using llvm::Function;
using llvm::BasicBlock;
using llvm::UndefValue;
using llvm::ArrayType;
using llvm::TargetMachine;
using llvm::raw_fd_ostream;
using llvm::DIBasicType;

class LgsValue {
public:
    Value* IRValue = nullptr;
    LgsLocation location;

    virtual Value* loadIR(LgsLLVMGen& cg);
    virtual void setDebugValue(LgsLLVMGen& cg);
    virtual void hashNode(size_t& oldHash);
    llvm::DILocation* getDebugLoc(LgsLLVMGen& cg) const;
    virtual ~LgsValue() = default;
};
