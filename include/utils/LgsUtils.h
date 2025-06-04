#ifndef LGSUTILS_H
#define LGSUTILS_H
#include "exprs/LgsExpr.h"
#include <llvm/IR/DerivedTypes.h>

class LogosProject;
struct LgsIndex;

inline std::mutex mtx;

std::string getFileText(std::filesystem::path filePath);
std::string getFormatString(const std::vector<LgsExpr*>& args);
Value* getIRStr(const LgsRuntime* runtime, const std::string& value);
StructType* getIRStructType(LLVMContext& context, const std::string& name, const std::vector<Type*>& fields);
Module* createIRModule(const std::string& moduleName, LLVMContext& context);

#endif //LGSUTILS_H
