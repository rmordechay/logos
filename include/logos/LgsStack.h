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

struct LgsStackFrame {
    LgsSymbolTable symbolTable;
    LgsFunc* func = nullptr;
    LgsForLoop* loop = nullptr;
    LgsStmtsBlock* stmtsBlock = nullptr;
};

class LgsStack final : stack<LgsStackFrame> {
public:
    void enterScope(LgsValue* value, LgsStmtsBlock* stmtsBlock);
    void exitScope();
    LgsFunc* currentFunc();
    LgsForLoop* currentLoop();
    LgsStmtsBlock* currentStmtsBlock();
    LgsSymbolTable& getSymbolTable();
    void addHeapAllocExpr(LgsExpr* expr);
    auto begin() { return c.begin(); }
    auto end() { return c.end(); }
    auto rbegin() { return c.rbegin(); }
    auto rend() { return c.rend(); }
    ~LgsStack() = default;
};
