#pragma once
#include "LgsStack.h"
#include "LgsSymbolTable.h"

class LgsFile;
class LgsErrHandler;
class LgsForLoop;
class LgsFuncType;

inline LLVMContext context;
inline DataLayout dataLayout;

class LgsRuntime {
public:
    LgsStack stack;
    Module* module = nullptr;
    Function* IRFunc = nullptr;
    IRBuilderBase::InsertPoint savedIP;
    IRBuilder<> builder = IRBuilder(context);
    GlobalVariable* runtimeStruct = nullptr;

    void initRuntime();
    void freeExprs();
    void addAllocatedExpr(LgsExpr* expr);
    void pushStackTrace(const string& path);
    void printStack();
    ~LgsRuntime() = default;
};

inline LgsSymbolTable globals;
inline map<string, LgsFile*> externalFiles;
