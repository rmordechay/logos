#ifndef LOGOSMETADATA_H
#define LOGOSMETADATA_H

#include <LgsStack.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Target/TargetMachine.h>
#include <filesystem>
#include "json/json.hpp"
using json = nlohmann::json;

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
    filesystem::path buildDir;
    IRBuilder<> builder = IRBuilder(context);
};

struct Location {
    size_t lineNumber{};
    size_t posInLine{};
};


#endif //LOGOSMETADATA_H
