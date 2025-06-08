#pragma once
#include "exprs/LgsExpr.h"

class LogosProject;
struct LgsIndex;

inline std::mutex mtx;

std::string getFileText(path filePath);
std::string getFormatString(const std::vector<LgsExpr*>& args);
std::string removeUnderscores(const std::string& input);
Value* getIRStr(const LgsRuntime* runtime, const std::string& value);
StructType* getIRStructType(LLVMContext& context, const std::string& name, const std::vector<Type*>& fields);
Module* createIRModule(const std::string& moduleName, LLVMContext& context);
FunctionCallee getPrintf(LgsRuntime* runtime);
FunctionCallee getSnprintf(LgsRuntime* runtime);


