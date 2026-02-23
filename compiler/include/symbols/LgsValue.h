#pragma once
#include <llvm/IR/DIBuilder.h>

#include "LgsTokens.h"

namespace llvm {
    class TargetMachine;
class ArrayType;
class BasicBlock;
class Constant;
class ConstantAggregateZero;
class ConstantInt;
class DIBasicType;
class DICompileUnit;
class DIFile;
class DISubprogram;
class Function;
class FunctionType;
class GlobalValue;
class GlobalVariable;
class IntegerType;
class LLVMContext;
class Module;
class PointerType;
class StructType;
class Type;
class TypeSize;
class UndefValue;
class Value;
class raw_fd_ostream;
}

class LgsType;
class LgsVariable;
class LgsExpr;
class LgsCodeGen;
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
    LgsLocation location;
    Value* IRValue = nullptr;

    virtual LgsType* getType();
    virtual void setType(LgsType* newType);
    virtual void hashNode(size_t& oldHash);
    virtual void setDebugValue(LgsCodeGen& cg) = 0;
    virtual LgsValue* clone();
    void setDebugLoc(LgsCodeGen& cg) const;
    virtual ~LgsValue() = default;
};