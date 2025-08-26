#pragma once
#include "LgsForLoop.h"

class LgsInfiniteLoop final : public LgsForLoop {
public:
    void setBlocks(LgsLLVM& codeGen) override;
    void incAndJumpToCond(LgsLLVM& codeGen) override;
    Value* loopStart(LgsLLVM& codeGen) override;
    Value* loopEnd(LgsLLVM& codeGen) override;
};
