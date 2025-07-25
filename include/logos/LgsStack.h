#pragma once
#include "LgsSymbol.h"
#include "LgsSymbolTable.h"
#include "stmts/LgsStmtsBlock.h"

class LgsStmtsBlock;
class LgsStmt;
class LgsIfStmt;
class LgsExpr;
class LgsForLoop;
class LgsFunc;

enum LgsScope {
    FUNC_SCOPE,
    LOOP_SCOPE,
    IF_SCOPE,
    BLOCK_SCOPE,
};

struct LgsStackFrame {
    LgsSymbolTable symbolTable;
    LgsFunc* func = nullptr;
    LgsScope scopeType;
    union {
        LgsForLoop* loop;
        LgsIfStmt* ifStmt;
        LgsStmtsBlock* stmtsBlock;
    };
};

class LgsStack final : public stack<LgsStackFrame> {
public:
    LgsFunc* currentFunc = nullptr;
    vector<LgsExpr*> allocatedExprs;

    void enterScope(LgsScope scope, LgsValue* value);
    void exitScope(bool isFunc = false);
    LgsForLoop* getLoop();
    LgsIfStmt* getIfStmt();
    void addAllocatedExpr(LgsExpr* expr);
    auto begin() { return c.begin(); }
    auto end() { return c.end(); }
    auto rbegin() { return c.rbegin(); }
    auto rend() { return c.rend(); }
    ~LgsStack() = default;
};
