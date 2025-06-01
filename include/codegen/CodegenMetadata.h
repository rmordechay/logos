#ifndef CODEGENMETADATA_H
#define CODEGENMETADATA_H

#include "logos/LgsActiveEnv.h"
#include <logos/LgsRuntime.h>
#include <json/json.hpp>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/TargetParser/Host.h>

using namespace llvm;
using namespace nlohmann;

inline LLVMContext context;
inline LgsActiveEnv activeEnv;
inline map<string, Module*> IRModules;
inline TargetMachine* targetMachine = nullptr;
inline string targetTriple = sys::getDefaultTargetTriple();

Type* const i1Ty = Type::getInt1Ty(context);
Type* const i8Ty = Type::getInt8Ty(context);
Type* const i16Ty = Type::getInt16Ty(context);
Type* const i32Ty = Type::getInt32Ty(context);
Type* const i64Ty = Type::getInt64Ty(context);
Type* const voidTy = Type::getVoidTy(context);
Value* const i32Zero = ConstantInt::get(i32Ty, 0);
PointerType* const ptrTy = PointerType::get(i8Ty, 0);
Value* const null = ConstantPointerNull::get(ptrTy);

struct CodegenMetadata {
    LgsRuntime runtime;
    Module* module;
    IRBuilder<> builder = IRBuilder(context);
};

struct Location {
    size_t lineNumber{};
    size_t posInLine{};

    string lineNumberStr() const {
        return to_string(lineNumber);
    }

    string getFullPath(const filesystem::path& path) const {
        return path.string() + ":" + lineNumberStr() + ":" + to_string(posInLine);
    }
};

inline FunctionCallee getPrintf(Module* module) {
    const auto printfType = FunctionType::get(i32Ty, {ptrTy}, true);
    return module->getOrInsertFunction("printf", printfType);
}

inline FunctionCallee getSnprintf(Module* module) {
    const auto printfType = FunctionType::get(i32Ty, {ptrTy, i64Ty, ptrTy}, true);
    return module->getOrInsertFunction("snprintf", printfType);
}

#endif //CODEGENMETADATA_H
