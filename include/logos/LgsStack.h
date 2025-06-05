#ifndef LGSSTACK_H
#define LGSSTACK_H
#include "LgsSymbol.h"

class LgsStmt;
class LgsIfStmt;
class LgsExpr;
class LgsForLoop;
class LgsFunc;

enum ScopeType {
    LOOP,
    IF_STMT,
};

struct LgsStackFrame {
    std::map<std::string, LgsSymbol> symbols;
    std::vector<LgsExpr*> allocatedExprs;
};

class LgsStack final : public std::stack<LgsStackFrame> {
public:
    LgsFunc* returnFunc = nullptr;
    LgsFunc* currentFunc = nullptr;
    LgsForLoop* currentLoop = nullptr;
    LgsIfStmt* currentIfStmt = nullptr;

    void enterFunc(LgsFunc* func);
    void enterScope(LgsStmt* stmt);
    void exitFunc();
    void exitScope(ScopeType type);
    void addSymbol(const std::string& name, const LgsSymbol& symbol);
    ~LgsStack() = default;
};

#endif //LGSSTACK_H
