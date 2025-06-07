#ifndef LGSSTACK_H
#define LGSSTACK_H
#include "LgsSymbol.h"

class LgsStmt;
class LgsIfStmt;
class LgsExpr;
class LgsForLoop;
class LgsFunc;

enum LgsScope {
    FUNC_SCOPE,
    LOOP_SCOPE,
    IF_SCOPE,
};

struct LgsStackFrame {
    LgsScope scopeType;
    LgsFunc* func = nullptr;
    union {
        LgsForLoop* loop;
        LgsIfStmt* ifStmt;
    };
    std::map<std::string, LgsSymbol> symbols;
};

class LgsStack final : public std::stack<LgsStackFrame> {
public:
    LgsFunc* currentFunc = nullptr;
    std::vector<LgsExpr*> allocatedExprs;

    void enterFunc(LgsFunc* func);
    void enterScope(LgsScope scope, LgsStmt* stmt);
    void exitFunc();
    void exitScope(LgsScope scope);
    LgsForLoop* getLoop();
    LgsIfStmt* getIfStmt();
    void addSymbol(const std::string& name, const LgsSymbol& symbol);
    auto begin() { return c.begin(); }
    auto end() { return c.end(); }
    auto rbegin() { return c.rbegin(); }
    auto rend() { return c.rend(); }
    ~LgsStack() = default;
};

#endif //LGSSTACK_H
