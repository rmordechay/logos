#pragma once
#include "LgsStack.h"

class LgsFile;
class LgsErrHandler;
class LgsForLoop;
class LgsFuncType;

class LgsModule {
public:
    LgsStack stack;
    LLVMContext context;
    Module* IRModule = nullptr;
    IRBuilderBase::InsertPoint savedIP;
    IRBuilder<> builder = IRBuilder(context);

    ~LgsModule() = default;
};

inline map<string, LgsFile*> externalFiles;
