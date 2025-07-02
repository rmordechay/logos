#pragma once
#include "LgsForLoop.h"

class LgsInfiniteLoop final : public LgsForLoop {
public:
    Value* loopStart(LgsModule* module) override;
    Value* loopEnd(LgsModule* module) override;
    void initIRLoop(LgsModule* module) override;
    void exitIRLoop(LgsModule* module) const override;
    ~LgsInfiniteLoop() override = default;
};
