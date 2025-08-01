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
    LgsForLoop* loop;
    LgsIfStmt* ifStmt;
    LgsStmtsBlock* stmtsBlock;
};

class LgsStack final : public stack<LgsStackFrame> {
public:
    void enterScope(LgsValue* value, LgsStmtsBlock* stmtsBlock = nullptr);
    void exitScope();
    LgsFunc* currentFunc();
    LgsForLoop* currentLoop();
    LgsIfStmt* currentIfStmt();
    LgsStmtsBlock* currentStmtsBlock();
    auto begin();
    auto end();
    auto rbegin();
    auto rend();
    ~LgsStack() = default;
};
