#pragma once
#include "LgsForLoop.h"
#include "LgsValue.h"

class LgsInfiniteLoop final : public LgsForLoop {
public:
    void setBlocks(LgsCodeGen& cg) override;
    void incAndJumpToCond(LgsCodeGen& cg) override;
    Value* loopStart(LgsCodeGen& cg) override;
    Value* loopEnd(LgsCodeGen& cg) override;
    void setDebugValue(LgsCodeGen& cg) override;
};
