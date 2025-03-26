#ifndef CODEGENMETADATA_H
#define CODEGENMETADATA_H

#include <LgsStack.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Target/TargetMachine.h>
#include <filesystem>
#include <llvm/TargetParser/Host.h>

inline LLVMContext context;
inline map<string, Module*> modules;
inline TargetMachine* targetMachine = nullptr;
inline string targetTriple = sys::getDefaultTargetTriple();

struct CodeGenMetadata {
    LgsStack logosStack;
    Module* currentModule;
    filesystem::path buildDir;
    IRBuilder<> builder = IRBuilder(context);
};

#endif //CODEGENMETADATA_H
