#pragma once
#include "LgsForLoop.h"

class LgsInfiniteLoop final : public LgsForLoop {
public:
    Value* loopStart(LgsRuntime* runtime) override;
    Value* loopEnd(LgsRuntime* runtime) override;
    void setIRIterable(LgsRuntime* runtime) override;
    void setIRLoopVars(LgsRuntime* runtime) override;
    ~LgsInfiniteLoop() override = default;
};
