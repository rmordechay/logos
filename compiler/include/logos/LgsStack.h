#pragma once
#include "LgsSymbolTable.h"
#include "loops/LgsForeachLoop.h"

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
    std::vector<LgsStackFrame> frames;

    void enterScope(LgsValue* value);
    void exitScope();
    LgsSymbolTable& getSymbolTable();
    LgsFunc* currentFunc() const;
    LgsForLoop* currentLoop() const;
    LgsIfStmt* currentIfStmt() const;
    LgsIfStmt* getOutermostIfStmt() const;
    LgsForeachLoop* getInnermostForeachLoop() const;
    BasicBlock* findTagExitBlock(const std::string& tag) const;
};
