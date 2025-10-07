#pragma once
#include "loops/LgsLoopMetaVar.h"
#include "stmts/LgsStmt.h"

namespace llvm {
    class BasicBlock;
    class AllocaInst;
}

using namespace llvm;
class LgsWhileLoop;
class LgsInfiniteLoop;
class LgsRangeLoop;
class LgsForeachLoop;
class LgsStmtsBlock;

class LgsForLoop : public LgsStmt {
public:
    std::vector<LgsVarDec*> loopVars;
    std::map<LgsLoopMetaVarType, LgsLoopMetaVar*> metaVars;
    AllocaInst* iPtr = nullptr;
    Value* iValue = nullptr;

    LgsStmtsBlock* stmtsBlock = nullptr;
    BasicBlock* IRCondBlock = nullptr;
    BasicBlock* IRBodyBlock = nullptr;
    BasicBlock* IRExitBlock = nullptr;

    LgsForeachLoop* asForeachLoop();
    LgsRangeLoop* asRangeLoop();
    LgsInfiniteLoop* asInfiniteLoop();
    LgsWhileLoop* asWhileLoop();

    virtual void setBlocks(LgsLLVMGen& cg);
    virtual void incAndJumpToCond(LgsLLVMGen& cg);
    virtual Value* loopStart(LgsLLVMGen& cg) = 0;
    virtual Value* loopEnd(LgsLLVMGen& cg) = 0;
    Value* loadIndex(LgsLLVMGen& cg) const;

    ~LgsForLoop() override;
};
