#pragma once
#include "loops/LgsMetaVar.h"
#include "stmts/LgsStmt.h"

namespace llvm {
    class BasicBlock;
    class AllocaInst;
}

class LgsWhileLoop;
class LgsInfiniteLoop;
class LgsRangeLoop;
class LgsForeachLoop;
class LgsStmtsBlock;

class LgsForLoop : public LgsStmt {
public:
    std::vector<LgsVarDec*> loopVars;
    llvm::AllocaInst* iPtr = nullptr;
    Value* iValue = nullptr;
    Value* isReversed = nullptr;
    LgsStmtsBlock* stmtsBlock = nullptr;
    BasicBlock* IRCondBlock = nullptr;
    BasicBlock* IRBodyBlock = nullptr;
    BasicBlock* IRExitBlock = nullptr;
    std::unordered_map<LgsMetaVarType, LgsMetaVar*> metaVars;

    virtual void setBlocks(LgsLLVMGen& cg);
    virtual void incAndJumpToCond(LgsLLVMGen& cg);
    virtual Value* loopStart(LgsLLVMGen& cg) = 0;
    virtual Value* loopEnd(LgsLLVMGen& cg) = 0;
    LgsForeachLoop* asForeachLoop();
    LgsRangeLoop* asRangeLoop();
    LgsInfiniteLoop* asInfiniteLoop();
    LgsWhileLoop* asWhileLoop();
    ~LgsForLoop() override;
};
