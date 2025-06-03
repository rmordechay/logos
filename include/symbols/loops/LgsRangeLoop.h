#ifndef LOGOSRANGELOOP_H
#define LOGOSRANGELOOP_H
#include "loops/LgsForLoop.h"

class LgsRangeLoop final : public LgsForLoop {
public:
    LgsExpr* rangeStart = nullptr;
    LgsExpr* rangeEnd = nullptr;

    LgsRangeLoop(LgsExpr* rangeStart, LgsExpr* rangeEnd) : rangeStart(rangeStart), rangeEnd(rangeEnd) {}
    void setIRLoopVars(LgsRuntime* runtime) override;
    void setIRIterable(LgsRuntime* runtime) override;
    Value* loopStart(LgsRuntime* runtime) override;
    Value* loopEnd(LgsRuntime* runtime) override;
    ~LgsRangeLoop() override;
};

#endif //LOGOSRANGELOOP_H
