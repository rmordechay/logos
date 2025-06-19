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
Value* getIRStr(const LgsRuntime* runtime, const std::string& value);
StructType* getIRStructType(const std::string& name, const std::vector<Type*>& fields);
Module* createIRModule(const std::string& moduleName, LLVMContext& context);
bool hasTerminator(const LgsRuntime* runtime);
FunctionCallee getPrintf(LgsRuntime* runtime);
FunctionCallee getSnprintf(LgsRuntime* runtime);
FunctionCallee getStrHash(LgsRuntime* runtime);
Function* getMemcpy(LgsRuntime* runtime);
TargetMachine* getTargetMachine();
