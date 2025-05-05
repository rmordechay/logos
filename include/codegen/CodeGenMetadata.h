#ifndef CODEGENMETADATA_H
#define CODEGENMETADATA_H

#include <LgsStack.h>
#include <json/json.hpp>
#include <llvm/IR/IRBuilder.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/TargetParser/Host.h>

using namespace llvm;
using namespace nlohmann;

inline LLVMContext context;
inline LgsActiveEnv activeEnv;
inline map<string, Module*> IRModules;
inline TargetMachine* targetMachine = nullptr;
inline string targetTriple = sys::getDefaultTargetTriple();

PointerType* const ptrTy = PointerType::get(Type::getInt8Ty(context), 0);
Type* const i1Ty = Type::getInt1Ty(context);
Type* const i8Ty = Type::getInt8Ty(context);
Type* const i16Ty = Type::getInt16Ty(context);
Type* const i32Ty = Type::getInt32Ty(context);
Type* const i64Ty = Type::getInt64Ty(context);
Type* const voidTy = Type::getVoidTy(context);
Value* const i32Zero = ConstantInt::get(i32Ty, 0);

struct CodeGenMetadata {
    LgsStack lgsStack;
    Module* module;
    IRBuilder<> builder = IRBuilder(context);
};

struct Location {
    size_t lineNumber{};
    size_t posInLine{};

    string lineNumberStr() const {
        return to_string(lineNumber);
    }
};

#endif //CODEGENMETADATA_H
