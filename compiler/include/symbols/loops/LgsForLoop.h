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
    Value* iPtr = nullptr;
    std::vector<LgsVarDec*> loopVars;
    LgsStmtsBlock* stmtsBlock = nullptr;
    BasicBlock* IRCondBlock = nullptr;
    BasicBlock* IRBodyBlock = nullptr;
    BasicBlock* IRExitBlock = nullptr;
    std::unordered_map<LgsMetaVarType, LgsMetaVar*> metaVars;

    virtual void setBlocks(LgsCodeGen& cg);
    virtual void incAndJumpToCond(LgsCodeGen& cg);
    virtual Value* loopStart(LgsCodeGen& cg) = 0;
    virtual Value* loopEnd(LgsCodeGen& cg) = 0;
    Value* loadIndex(LgsCodeGen& cg) const;
    LgsForeachLoop* asForeachLoop();
    LgsRangeLoop* asRangeLoop();
    LgsInfiniteLoop* asInfiniteLoop();
    LgsWhileLoop* asWhileLoop();
    ~LgsForLoop() override;
};
