#pragma once
#include "exprs/LgsExpr.h"

class LgsApp;
struct LgsIndex;

inline std::mutex mtx;
inline TargetMachine* targetMachine = nullptr;

std::string getFileText(path filePath);
std::string removeUnderscores(const std::string& input);
size_t hashString(const string& str); // FNV-1a 32-bit hash
void freeType(const LgsType* type);
Value* getIRStr(LgsModule* module, const std::string& value);
StructType* getIRStructType(LLVMContext& context, const std::string& name, const std::vector<Type*>& fields);
Module* createIRModule(const std::string& moduleName, LLVMContext& context);
bool hasTerminator(const LgsModule* module);
PointerType* ptrTy(LLVMContext& context);
Type* i1Ty(LLVMContext& context);
Type* i8Ty(LLVMContext& context);
Type* i16Ty(LLVMContext& context);
Type* i32Ty(LLVMContext& context);
Type* i64Ty(LLVMContext& context);
FunctionCallee getPrintf(LgsModule* module);
FunctionCallee getSnprintf(LgsModule* module);
FunctionCallee getStrHash(LgsModule* module);
Function* getMemcpy(LgsModule* module);
TargetMachine* getTargetMachine();
