#pragma once
#include "exprs/LgsExpr.h"
#include "logos/LgsModule.h"

class LgsApp;
struct LgsIndex;

inline mutex mtx;
inline TargetMachine* targetMachine = nullptr;

bool isLogosFile(const directory_entry& entry);
bool isCharPointer(clang::QualType qt);
bool isLgsKeyword(const string& s);
string getFileText(path filePath);
string removeUnderscores(const string& input);
void freeType(const LgsType* type);

// Codegen
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

inline Value* i1(LgsModule* module, const bool v) {
    return module->builder.getInt1(v);
}

inline Value* i8(LgsModule* module, const int8_t v) {
    return module->builder.getInt8(v);
}

inline Value* i16(LgsModule* module, const int16_t v) {
    return module->builder.getInt16(v);
}

inline Value* i32(LgsModule* module, const int32_t v) {
    return module->builder.getInt32(v);
}

inline Value* i64(LgsModule* module, const int64_t v) {
    return module->builder.getInt64(v);
}