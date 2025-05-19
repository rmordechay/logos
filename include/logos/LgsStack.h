#ifndef LOGOSSTACK_H
#define LOGOSSTACK_H
#include "LgsActiveEnv.h"
#include "symbols/LgsSymbol.h"
#include <stack>
#include <map>
#include <llvm/IR/Module.h>

using namespace std;
using namespace llvm;
class LgsLoop;
class LgsFuncType;

struct LgsStackFrame {
    map<string, LgsSymbol> symbols;
};

class LgsStack : public stack<LgsStackFrame> {
public:
    LgsFunc* currentFunc = nullptr;
    LgsFunc* returnFunc = nullptr;
    LgsLoop* currentLoop = nullptr;

    void enterScope(LgsFunc* func = nullptr);
    void exitScope();
    void addLocalSymbol(const string& name, const LgsSymbol& symbol);
    void reset();
    ~LgsStack() = default;
};

#endif //LOGOSSTACK_H
