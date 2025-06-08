#pragma once
#include "LgsStack.h"
#include "LgsSymbol.h"

using namespace std;
using namespace llvm;
class LgsErrHandler;
class LgsForLoop;
class LgsFuncType;

inline LLVMContext context;

class LgsRuntime {
public:
    LgsStack stack;
    Module* module = nullptr;
    IRBuilder<> builder = IRBuilder(context);
    GlobalVariable* runtimeStruct = nullptr;

    void initRuntime();
    void pushStackTrace(const string& path);
    void printStack();
    void addAllocatedExpr(LgsExpr* expr);
    void freeExprs();
    ~LgsRuntime() = default;
};

struct LgsGlobals {
    map<string, LgsSymbol> symbols;

    void addSymbol(const string& name, const LgsSymbol& symbol, LgsErrHandler* errHandler);
    void addEnum(LgsEnum* lgsEnum, LgsErrHandler* errHandler = nullptr);
    ~LgsGlobals();
};

inline LgsGlobals globals;


