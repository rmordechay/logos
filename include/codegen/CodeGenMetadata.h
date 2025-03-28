#ifndef CODEGENMETADATA_H
#define CODEGENMETADATA_H

#include <LgsStack.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Target/TargetMachine.h>
#include <filesystem>
#include <llvm/TargetParser/Host.h>

using namespace llvm;

inline LLVMContext context;
inline map<string, Module*> modules;
inline TargetMachine* targetMachine = nullptr;
inline string targetTriple = sys::getDefaultTargetTriple();

PointerType* const ptrTy = PointerType::get(Type::getInt8Ty(context), 0);
Type* const i32Type = Type::getInt32Ty(context);

struct CodeGenMetadata {
    LgsStack logosStack;
    Module* currentModule;
    filesystem::path buildDir;
    IRBuilder<> builder = IRBuilder(context);
};

#endif //CODEGENMETADATA_H
