#pragma once
#include "LgsForLoop.h"

class LgsInfiniteLoop final : public LgsForLoop {
public:
    void initIRLoop(LgsCodeGen* codeGen) override;
    ~LgsInfiniteLoop() override = default;
};
