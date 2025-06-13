#pragma once
#include "exprs/LgsExpr.h"

class LgsProject;
struct LgsIndex;

inline std::mutex mtx;
inline TargetMachine* targetMachine = nullptr;

std::string getFileText(path filePath);
std::string removeUnderscores(const std::string& input);
void freeType(const LgsType* type);
Value* getIRStr(const LgsRuntime* runtime, const std::string& value);
StructType* getIRStructType(LLVMContext& context, const std::string& name, const std::vector<Type*>& fields);
Module* createIRModule(const std::string& moduleName, LLVMContext& context);
FunctionCallee getPrintf(LgsRuntime* runtime);
FunctionCallee getSnprintf(LgsRuntime* runtime);
TargetMachine* getTargetMachine();
