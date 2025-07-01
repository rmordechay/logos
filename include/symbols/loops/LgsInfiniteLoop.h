#pragma once
#include "LgsForLoop.h"

class LgsInfiniteLoop final : public LgsForLoop {
public:
    Value* loopStart(LgsModule* runtime) override;
    Value* loopEnd(LgsModule* runtime) override;
    void initIRLoop(LgsModule* runtime) override;
    void exitIRLoop(LgsModule* runtime) const override;
    ~LgsInfiniteLoop() override = default;
};
