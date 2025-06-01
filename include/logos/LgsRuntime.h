#ifndef LOGOSSTACK_H
#define LOGOSSTACK_H

#include "LgsSymbol.h"
#include "data/LgsDefinitions.h"

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
};

class LgsRuntime {
public:
    stack<LgsStackFrame> stack;
    LgsStage stage = LGS_ANALYSIS;
    LgsFunc* returnFunc = nullptr;
    // LgsFuncImpl a = LgsFuncImpl("print_stack", &LGS_VOID);

    void enterScope(LgsFunc* func = nullptr);
    void exitScope();
    void exitFunc();
    void reset();
    LgsFunc* getCurrentFunc();
    LgsForLoop* getCurrentLoop();
    void addLocalSymbol(const string& name, const LgsSymbol& symbol);
    ~LgsRuntime() = default;
};

#endif //LOGOSSTACK_H
