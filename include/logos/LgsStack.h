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
};

struct LgsStackFrame {
    LgsSymbolTable symbolTable;
    LgsFunc* func = nullptr;
    LgsScope scopeType;
    union {
        LgsForLoop* loop;
        LgsIfStmt* ifStmt;
    };
};

class LgsStack final : public stack<LgsStackFrame> {
public:
    void enterScope(LgsScope scope, LgsValue* value);
    void exitScope();
    LgsFunc* currentFunc();
    LgsForLoop* currentLoop();
    LgsStmtsBlock* currentStmtsBlock();
    auto begin();
    auto end();
    auto rbegin();
    auto rend();
    ~LgsStack() = default;
};
