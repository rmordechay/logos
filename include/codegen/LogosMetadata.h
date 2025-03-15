#ifndef LOGOSMETADATA_H
#define LOGOSMETADATA_H

#include <LgsStack.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/Target/TargetMachine.h>

class CodeGenerator;
class LgsStack;

using namespace llvm;
using namespace std;

inline LLVMContext context;
inline map<string, Module*> modules;
inline TargetMachine* targetMachine = nullptr;

struct CodeGenMetadata {
    LgsStack logosStack;
    Module* currentModule;
    IRBuilder<> builder = IRBuilder(context);
};

struct Location {
    size_t lineNumber{};
    size_t posInLine{};
};

inline bool moduleExists(const string& name) {
    return modules.find(name) != modules.end();
}

inline void initLLVM() {
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    InitializeAllTargetMCs();
    InitializeAllTargets();
    InitializeAllTargetInfos();
    string error;
    const auto targetTriple = sys::getDefaultTargetTriple();
    const auto target = TargetRegistry::lookupTarget(targetTriple, error);
    targetMachine = target->createTargetMachine(targetTriple, "generic", "", TargetOptions(), std::nullopt);
}

#endif //LOGOSMETADATA_H
