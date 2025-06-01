#ifndef LOGOSRANGELOOP_H
#define LOGOSRANGELOOP_H
#include "loops/LgsForLoop.h"

class LgsRangeLoop final : public LgsForLoop {
public:
    LgsExpr* rangeStart = nullptr;
    LgsExpr* rangeEnd = nullptr;

    LgsRangeLoop(LgsExpr* rangeStart, LgsExpr* rangeEnd) : rangeStart(rangeStart), rangeEnd(rangeEnd) {}
    void setIRLoopVars(Module* module) override;
    void setIRIterable(Module* module) override;
    Value* loopStart(Module* module) override;
    Value* loopEnd(Module* module) override;
    ~LgsRangeLoop() override;
};

#endif //LOGOSRANGELOOP_H
