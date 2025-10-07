#pragma once
#include "LgsSymbolTable.h"
#include <llvm/IR/BasicBlock.h>

class LgsPatternMatch;
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
    bool inCoroutine = false;
};

class LgsStack final : std::stack<LgsStackFrame> {
public:
    void enterScope(LgsValue* value);
    void exitScope();
    LgsFunc* currentFunc();
    LgsForLoop* currentLoop();
    LgsIfStmt* currentIfStmt();
    LgsIfStmt* outermostIfStmt();
    llvm::BasicBlock* findTagExitBlock(const std::string& tag);
    LgsSymbolTable& getSymbolTable();
    bool inCoroutine();
    auto begin() { return c.begin(); }
    auto end() { return c.end(); }
    auto rbegin() { return c.rbegin(); }
    auto rend() { return c.rend(); }
};
