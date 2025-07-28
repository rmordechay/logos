#pragma once
#include "logos/LgsModule.h"

inline TargetMachine* targetMachine = nullptr;
inline mutex mtx;

void initLLVM();
Value* getIRStr(LgsModule* module, const string& value);
StructType* getIRStructType(LLVMContext& context, const string& name, const vector<Type*>& fields);
Module* createIRModule(const string& moduleName, LLVMContext& context);
GlobalVariable* createIRGlobal(const LgsModule* module, Type* type, Constant* value);
void branchToBlock(LgsModule* module, BasicBlock* block);
void startBlock(LgsModule* module, BasicBlock* block);
void startFuncBlock(LgsModule* module);
void copyMem(LgsModule* module, Value* src, Value* dest, size_t n);
bool lastInstTerminator(const LgsModule* module);
FunctionCallee getPrintf(LgsModule* module);
FunctionCallee getSnprintf(LgsModule* module);
FunctionCallee getStrHash(LgsModule* module);
Function* getMemcpy(LgsModule* module);
TargetMachine* getTargetMachine();

inline PointerType* ptrTy(LgsModule* module) {
    return PointerType::getUnqual(module->context);
}

inline Value* null(LgsModule* module) {
    return ConstantPointerNull::get(ptrTy(module));
}

inline Type* sizeTy(LgsModule* module) {
    return module->IRModule->getDataLayout().getIntPtrType(module->context);
}

inline Type* i1Ty(LgsModule* module) {
    return IntegerType::getInt32Ty(module->context);
}

inline Type* i8Ty(LgsModule* module) {
    return IntegerType::getInt32Ty(module->context);
}

inline Type* i16Ty(LgsModule* module) {
    return IntegerType::getInt32Ty(module->context);
}

inline Type* i32Ty(LgsModule* module) {
    return IntegerType::getInt32Ty(module->context);
}

inline Type* i64Ty(LgsModule* module) {
    return IntegerType::getInt64Ty(module->context);
}

inline ConstantInt* i1(LgsModule* module, const bool v) {
    return module->builder.getInt1(v);
}

inline ConstantInt* i8(LgsModule* module, const int8_t v) {
    return module->builder.getInt8(v);
}

inline ConstantInt* i16(LgsModule* module, const int16_t v) {
    return module->builder.getInt16(v);
}

inline ConstantInt* i32(LgsModule* module, const int32_t v) {
    return module->builder.getInt32(v);
}

inline ConstantInt* i64(LgsModule* module, const int64_t v) {
    return module->builder.getInt64(v);
}

inline ConstantInt* i32Zero(LgsModule* module) {
    return module->builder.getInt32(0);
}

inline ConstantInt* i64Zero(LgsModule* module) {
    return module->builder.getInt64(0);
}
