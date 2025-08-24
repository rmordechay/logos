#pragma once
#include "LgsForLoop.h"

class LgsInfiniteLoop final : public LgsForLoop {
public:
    void setBlocks(LgsLLVM& codeGen) override;
    void incAndJumpToCond(LgsLLVM& codeGen) const override;
};
