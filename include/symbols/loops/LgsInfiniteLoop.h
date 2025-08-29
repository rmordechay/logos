#pragma once
#include "LgsForLoop.h"

class LgsInfiniteLoop final : public LgsForLoop {
public:
    void setBlocks(LgsLLVMGen& cg) override;
    void incAndJumpToCond(LgsLLVMGen& cg) override;
    Value* loopStart(LgsLLVMGen& cg) override;
    Value* loopEnd(LgsLLVMGen& cg) override;
};
