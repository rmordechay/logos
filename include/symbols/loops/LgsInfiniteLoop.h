#pragma once
#include "LgsForLoop.h"

class LgsInfiniteLoop final : public LgsForLoop {
public:
    Value* loopStart(LgsRuntime* runtime) override;
    Value* loopEnd(LgsRuntime* runtime) override;
    void initIRLoop(LgsRuntime* runtime) override;
    void exitIRLoop(LgsRuntime* runtime) const override;
    ~LgsInfiniteLoop() override = default;
};
