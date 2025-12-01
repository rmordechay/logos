#pragma once
#include "LgsForLoop.h"

class LgsInfiniteLoop final : public LgsForLoop {
public:
    void setBlocks(LgsCgModule& cg) override;
    void incAndJumpToCond(LgsCgModule& cg) override;
    Value* loopStart(LgsCgModule& cg) override;
    Value* loopEnd(LgsCgModule& cg) override;
    void setDebugValue(LgsCgModule& cg) override;
};
