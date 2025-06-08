#pragma once
#include "exprs/LgsExpr.h"
#include <llvm/IR/DerivedTypes.h>

class LogosProject;
struct LgsIndex;

inline std::mutex mtx;

std::string getFileText(path filePath);
std::string getFormatString(const std::vector<LgsExpr*>& args);
Value* getIRStr(LgsRuntime* runtime, const std::string& value);
StructType* getArrStruct(LLVMContext& context, const std::string& name, const std::vector<Type*>& fields);
Module* createIRModule(const std::string& moduleName, LLVMContext& context);


