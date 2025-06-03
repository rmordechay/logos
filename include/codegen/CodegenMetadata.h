#ifndef CODEGENMETADATA_H
#define CODEGENMETADATA_H

#include "logos/LgsActiveEnv.h"
#include <json/json.hpp>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/TargetParser/Host.h>

using namespace llvm;
using namespace nlohmann;

inline LLVMContext context;
inline LgsActiveEnv activeEnv;
inline std::map<std::string, Module*> IRModules;
inline auto builder = IRBuilder(context);
inline TargetMachine* targetMachine = nullptr;
inline std::string targetTriple = sys::getDefaultTargetTriple();

Type* const i1Ty = Type::getInt1Ty(context);
Type* const i8Ty = Type::getInt8Ty(context);
Type* const i16Ty = Type::getInt16Ty(context);
Type* const i32Ty = Type::getInt32Ty(context);
Type* const i64Ty = Type::getInt64Ty(context);
Type* const voidTy = Type::getVoidTy(context);
Value* const i32Zero = ConstantInt::get(i32Ty, 0);
PointerType* const ptrTy = PointerType::get(i8Ty, 0);
Value* const null = ConstantPointerNull::get(ptrTy);

#endif //CODEGENMETADATA_H
