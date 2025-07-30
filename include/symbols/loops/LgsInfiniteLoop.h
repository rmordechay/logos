#pragma once
#include "LgsForLoop.h"

class LgsInfiniteLoop final : public LgsForLoop {
public:
    Value* loopStart(LgsCodeGen* codeGen) override;
    Value* loopEnd(LgsCodeGen* codeGen) override;
    void initIRLoop(LgsCodeGen* codeGen) override;
    void IRLoopPrologue(LgsCodeGen* codeGen) const override;
    ~LgsInfiniteLoop() override = default;
};
