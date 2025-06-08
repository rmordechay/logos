#pragma once
#include "LgsStack.h"
#include "LgsSymbol.h"


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

struct LgsSymbolTable {
    map<string, LgsSymbol> symbols;

    LgsSymbol* getSymbol(const string& name);
    void addSymbol(const string& name, const LgsSymbol& symbol, LgsErrHandler* errHandler);
    void addEnum(LgsEnum* lgsEnum, LgsErrHandler* errHandler = nullptr);
    ~LgsSymbolTable();
};

inline LgsSymbolTable globals;
