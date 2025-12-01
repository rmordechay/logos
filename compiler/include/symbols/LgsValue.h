#pragma once
#include "errors/LgsErrors.h"
#include <llvm/IR/DIBuilder.h>

namespace llvm {
    class TargetMachine;
}

class LgsType;
class LgsVariable;
class LgsExpr;
class LgsCgModule;
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

    virtual Value* loadIR(LgsCgModule& cg);
    virtual void hashNode(size_t& oldHash);
    virtual void setDebugValue(LgsCgModule& cg) = 0;
    virtual ~LgsValue() = default;
};