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
    void enterScope(LgsScope scope, LgsValue* value);
    void exitScope();
    LgsFunc* currentFunc();
    LgsForLoop* currentLoop();
    void addHeapExpr(LgsExpr* expr);
    auto begin();
    auto end();
    auto rbegin();
    auto rend();
    ~LgsStack() = default;
};
