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

class LgsStack final : public stack<LgsStackFrame> {
public:
    void enterScope(LgsValue* value, LgsStmtsBlock* stmtsBlock);
    void exitScope();
    LgsFunc* getCurrentFunc();
    LgsForLoop* getCurrentLoop();
    LgsStmtsBlock* getCurrentStmtsBlock();
    auto begin() { return c.begin(); }
    auto end() { return c.end(); }
    auto rbegin() { return c.rbegin(); }
    auto rend() { return c.rend(); }
    ~LgsStack() = default;
};
