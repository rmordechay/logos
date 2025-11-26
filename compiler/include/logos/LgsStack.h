#pragma once
#include "LgsSymbolTable.h"
#include <stack>

namespace llvm {
    class BasicBlock;
}

class LgsSwitch;
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

class LgsStack final {
public:
    std::stack<LgsStackFrame> stack;

    void enterScope(LgsValue* value);
    void exitScope();
    LgsFunc* currentFunc();
    LgsForLoop* currentLoop();
    LgsIfStmt* currentIfStmt();
    LgsIfStmt* outermostIfStmt();
    BasicBlock* findTagExitBlock(const std::string& tag);
    LgsSymbolTable& getSymbolTable();
};
