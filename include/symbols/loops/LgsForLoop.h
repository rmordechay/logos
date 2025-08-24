#pragma once
#include "stmts/LgsStmt.h"

namespace llvm {
    class BasicBlock;
    class AllocaInst;
}

class LgsVariable;
class LgsStmtsBlock;
class LgsExpr;

class LgsForLoop : public LgsStmt {
public:
    std::vector<LgsVarDec*> loopVars;
    llvm::AllocaInst* iPtr = nullptr;
    LgsStmtsBlock* stmtsBlock = nullptr;
    llvm::BasicBlock* IRCondBlock = nullptr;
    llvm::BasicBlock* IRBodyBlock = nullptr;
    llvm::BasicBlock* IRExitBlock = nullptr;
    LgsVarDec* isFirst = nullptr;
    LgsVarDec* isLast = nullptr;

    virtual void setBlocks(LgsLLVM& codeGen);
    virtual void incAndJumpToCond(LgsLLVM& codeGen) const;
    void incIndex(LgsLLVM* codeGen) const;
    llvm::Value* loadIndex(LgsLLVM& codeGen) const;
    json::value asJSON() override;
    ~LgsForLoop() override;
};
