#pragma once
#include "LgsSymbolTable.h"

class LgsValue;
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
    LgsIfStmt* ifStmt = nullptr;
};

class LgsStack final : std::stack<LgsStackFrame> {
public:
    void enterScope(LgsValue* value);
    void exitScope();
    LgsFunc* currentFunc();
    LgsForLoop* currentLoop();
    LgsIfStmt* currentIfStmt();
    LgsIfStmt* outermostIfStmt();
    LgsSymbolTable& getSymbolTable();
    void addHeapAllocExpr(LgsExpr* expr);
    bool isRootScope() const;
    auto begin() { return c.begin(); }
    auto end() { return c.end(); }
    auto rbegin() { return c.rbegin(); }
    auto rend() { return c.rend(); }
};
