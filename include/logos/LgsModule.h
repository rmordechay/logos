#pragma once
#include "LgsStack.h"

class LgsFile;
class LgsErrHandler;
class LgsForLoop;
class LgsFuncType;

class LgsModule {
public:
    LgsFile& file;
    LgsStack stack;
    LLVMContext context;
    LgsSymbolTable& globals;
    Value* pathIR = nullptr;
    Module* IRModule = nullptr;
    IRBuilderBase::InsertPoint savedIP;
    IRBuilder<> builder = IRBuilder(context);

    LgsModule(LgsFile& file, LgsSymbolTable& globals) : file(file), globals(globals) {}
    ~LgsModule() = default;
};

inline map<string, LgsFile*> externalFiles;
