#pragma once
#include "exprs/LgsExpr.h"

class LgsApp;
struct LgsIndex;

inline std::mutex mtx;
inline TargetMachine* targetMachine = nullptr;

std::string getFileText(path filePath);
std::string removeUnderscores(const std::string& input);
void freeType(const LgsType* type);
void initLLVM();
Value* getIRStr(LgsModule* module, const std::string& value);
StructType* getIRStructType(LLVMContext& context, const std::string& name, const std::vector<Type*>& fields);
Module* createIRModule(const std::string& moduleName, LLVMContext& context);
bool lastInstTerminator(const LgsModule* module);
PointerType* ptrTy(LgsModule* module);
Type* i1Ty(LgsModule* module);
Type* i8Ty(LgsModule* module);
Type* i16Ty(LgsModule* module);
Type* i32Ty(LgsModule* module);
Type* i64Ty(LgsModule* module);
FunctionCallee getPrintf(LgsModule* module);
FunctionCallee getSnprintf(LgsModule* module);
FunctionCallee getStrHash(LgsModule* module);
Function* getMemcpy(LgsModule* module);
TargetMachine* getTargetMachine();
