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
Value* i1(LgsModule* module, bool v);
Value* i8(LgsModule* module, int8_t v);
Value* i16(LgsModule* module, int16_t v);
Value* i32(LgsModule* module, int32_t v);
Value* i64(LgsModule* module, int64_t v);
FunctionCallee getPrintf(LgsModule* module);
FunctionCallee getSnprintf(LgsModule* module);
FunctionCallee getStrHash(LgsModule* module);
Function* getMemcpy(LgsModule* module);
TargetMachine* getTargetMachine();
