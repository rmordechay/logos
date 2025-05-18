#ifndef LOGOSRANGELOOP_H
#define LOGOSRANGELOOP_H
#include "loops/LgsLoop.h"

class LgsRangeLoop final : public LgsLoop {
public:
    LgsExpr* rangeStart = nullptr;
    LgsExpr* rangeEnd = nullptr;

    LgsRangeLoop(LgsExpr* rangeStart, LgsExpr* rangeEnd) : rangeStart(rangeStart), rangeEnd(rangeEnd) {}
    void setIRLoopVars(CodeGenMetadata* metadata) override;
    Value* loopStart(CodeGenMetadata* metadata) override;
    Value* loopEnd(CodeGenMetadata* metadata) override;
    ~LgsRangeLoop() override;
};

#endif //LOGOSRANGELOOP_H
