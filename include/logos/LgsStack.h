#ifndef LGSSTACK_H
#define LGSSTACK_H
#include "LgsSymbol.h"

class LgsExpr;
class LgsForLoop;
class LgsFunc;

struct LgsStackFrame {
    std::map<std::string, LgsSymbol> symbols;
    LgsFunc* func = nullptr;
    LgsForLoop* loop = nullptr;
    std::vector<LgsExpr*> allocatedExprs;
};

class LgsStack final : public std::stack<LgsStackFrame> {
public:
    LgsFunc* returnFunc = nullptr;
    LgsFunc* currentFunc = nullptr;
    LgsForLoop* currentLoop = nullptr;

    void enterFunc(LgsFunc* func);
    void enterScope();
    void exitFunc();
    void exitScope();
    void addSymbol(const std::string& name, const LgsSymbol& symbol);
    ~LgsStack() = default;
};

#endif //LGSSTACK_H
