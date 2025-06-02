#ifndef LOGOSSTACK_H
#define LOGOSSTACK_H

#include "LgsStack.h"
#include "LgsSymbol.h"
#include "exprs/LgsExpr.h"
#include <map>
#include <llvm/IR/Module.h>

using namespace std;
using namespace llvm;
class LgsErrHandler;
class LgsForLoop;
class LgsFuncType;

class LgsRuntime {
public:
    LgsStack stack;
    Module* currentModule = nullptr;
    GlobalVariable* runtimeStruct = nullptr;

    void initRuntime(Module* mainModule);
    void pushStackTrace(Module* module, const string& path) const;
    void printStack(Module* module) const;
    void addLocalSymbol(const string& name, const LgsSymbol& symbol);
    void addAllocatedExpr(LgsExpr* expr);
    void freeExprs(Module* module);
    ~LgsRuntime() = default;
};

struct LgsGlobals {
    std::mutex mtx;
    map<string, LgsSymbol> symbols;

    void addSymbol(const string& name, const LgsSymbol& symbol, LgsErrHandler* errHandler);
    void addEnum(LgsEnum* lgsEnum, LgsErrHandler* errHandler = nullptr);
    ~LgsGlobals();
};

inline LgsGlobals globals;
inline LgsRuntime runtime;

#endif //LOGOSSTACK_H
