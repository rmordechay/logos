#pragma once
#include "LgsStack.h"
#include "LgsSymbolTable.h"

class LgsFile;
using namespace llvm;
class LgsErrHandler;
class LgsForLoop;
class LgsFuncType;

inline LLVMContext context;

class LgsRuntime {
public:
    LgsStack stack;
    Module* module = nullptr;
    IRBuilderBase::InsertPoint savedIP;
    IRBuilder<> builder = IRBuilder(context);
    GlobalVariable* runtimeStruct = nullptr;

    void initRuntime();
    void pushStackTrace(const string& path);
    void printStack();
    void addAllocatedExpr(LgsExpr* expr);
    void freeExprs();
    ~LgsRuntime() = default;
};

inline LgsSymbolTable globals;
inline map<string, LgsFile*> externalFiles;
