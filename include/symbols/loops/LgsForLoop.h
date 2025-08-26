#pragma once
#include "loops/LgsLoopMetaVar.h"

class LgsWhileLoop;
class LgsRangeLoop;
class LgsInfiniteLoop;
class LgsForeachLoop;

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

    virtual void setBlocks(LgsLLVM& codeGen);
    virtual void incAndJumpToCond(LgsLLVM& codeGen);
    virtual Value* loopStart(LgsLLVM& codeGen) = 0;
    virtual Value* loopEnd(LgsLLVM& codeGen) = 0;
    void incIndex(LgsLLVM* codeGen);
    Value* loadIndex(LgsLLVM& codeGen) const;
    json::value asJSON() override;

    ~LgsForLoop() override;
};
