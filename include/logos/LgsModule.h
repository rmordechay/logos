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
    LgsSymbolTable& globals;
    Module* IRModule = nullptr;
    IRBuilderBase::InsertPoint savedIP;
    IRBuilder<> builder = IRBuilder(context);

    explicit LgsModule(LgsSymbolTable& globals): globals(globals) {}
    ~LgsModule() = default;
};

inline map<string, LgsFile*> externalFiles;
