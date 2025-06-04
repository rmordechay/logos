#ifndef LGSUTILS_H
#define LGSUTILS_H
#include "exprs/LgsExpr.h"
#include <llvm/IR/DerivedTypes.h>

class LogosProject;
struct LgsIndex;

inline std::mutex mtx;

std::string getFileText(std::filesystem::path filePath);
std::string getExprStr(LgsExpr* baseExpr);
int getExprConstNumber(LgsExpr* expr);
std::string getFormatString(const std::vector<LgsExpr*>& args);
void setIterIndices(const LgsIterIndex* iterIndex, std::vector<LgsIndex*>& indices);
StructType* getIRStructType(LLVMContext& context, const std::string& name, const std::vector<Type*>& fields);
Value* getIRStr(LgsRuntime* runtime, const std::string& value);
Module* createEmptyModule(const std::string& moduleName, LLVMContext& context);
void writeIRToFile(LogosProject& project);
bool shouldLoadIRArg(Value* value);

#endif //LGSUTILS_H
