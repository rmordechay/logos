#pragma once
#include "LgsForLoop.h"

class LgsInfiniteLoop final : public LgsForLoop {
public:
    void setBlocks(LgsCodeGen* codeGen) override;
    void createIRLoop(LgsCodeGen* codeGen) override;
    void incAndJumpToCond(LgsCodeGen* codeGen) const override;
    ~LgsInfiniteLoop() override = default;
};
