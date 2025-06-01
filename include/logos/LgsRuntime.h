#ifndef LOGOSSTACK_H
#define LOGOSSTACK_H

#include "LgsSymbol.h"
#include "data/LgsDefinitions.h"
#include "exprs/LgsExpr.h"

#include <stack>
#include <map>
#include <llvm/IR/Module.h>

using namespace std;
using namespace llvm;
class LgsForLoop;
class LgsFuncType;

struct LgsStackFrame {
    map<string, LgsSymbol> symbols;
    LgsFunc* currentFunc = nullptr;
    LgsForLoop* currentLoop = nullptr;
    vector<LgsExpr*> allocatedExprs;
};

enum LgsStage {
    LGS_ANALYSIS,
    LGS_RUNTIME,
};

class LgsRuntime {
public:
    stack<LgsStackFrame> stack;
    LgsStage stage = LGS_ANALYSIS;
    LgsFunc* returnFunc = nullptr;
    GlobalVariable* runtimeStruct = nullptr;

    void enterScope();
    void enterFunc(LgsFunc* func);
    void exitScope();
    void exitFunc();
    void reset();
    void initRuntime(Module* mainModule);
    void push(Module* module, const string& path) const;
    void printStack(Module* module) const;
    LgsFunc* getCurrentFunc();
    LgsForLoop* getCurrentLoop();
    map<string, LgsSymbol>& getSymbols();
    void addLocalSymbol(const string& name, const LgsSymbol& symbol);
    void addAllocatedExpr(LgsExpr* expr);
    void freeExprs(Module* module);
    ~LgsRuntime() = default;
};

#endif //LOGOSSTACK_H
