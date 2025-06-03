#ifndef LGSUTILS_H
#define LGSUTILS_H
#include "exprs/LgsExpr.h"
#include <llvm/IR/DerivedTypes.h>

struct LgsIndex;

std::string getFileText(std::filesystem::path filePath);
std::string getExprStr(LgsExpr* baseExpr);
int getExprConstNumber(LgsExpr* expr);
std::string getFormatString(const std::vector<LgsExpr*>& args);
void setIterIndices(const LgsIterIndex* iterIndex, std::vector<LgsIndex*>& indices);
StructType* getIRStructType(const std::string& name, const std::vector<Type*>& fields);
Value* getIRStr(Module* module, const std::string& value);
Module* createEmptyModule(const std::string& objName);
void writeIRToFile(const Module* module, const std::filesystem::path& name);
bool shouldLoadIRArg(Value* value);

#endif //LGSUTILS_H
