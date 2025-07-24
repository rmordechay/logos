#pragma once
#include "LgsStack.h"

class LgsFile;
class LgsErrHandler;
class LgsForLoop;
class LgsFuncType;

inline DataLayout dataLayout;
inline GlobalVariable* runtimeStruct = nullptr;

class LgsModule {
public:
    LgsStack stack;
    LLVMContext context;
    Module* IRModule = nullptr;
    IRBuilderBase::InsertPoint savedIP;
    IRBuilder<> builder = IRBuilder(context);

    void initRuntime();
    void addAllocatedExpr(LgsExpr* expr);
    void pushStackTrace(const string& path);
    void printStack();
    ~LgsModule() = default;
};

inline map<string, LgsFile*> externalFiles;
