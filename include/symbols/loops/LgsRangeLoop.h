#ifndef LOGOSRANGELOOP_H
#define LOGOSRANGELOOP_H
#include "loops/LgsForLoop.h"

class LgsRangeLoop final : public LgsForLoop {
public:
    LgsExpr* rangeStart = nullptr;
    LgsExpr* rangeEnd = nullptr;

    LgsRangeLoop(LgsExpr* rangeStart, LgsExpr* rangeEnd) : rangeStart(rangeStart), rangeEnd(rangeEnd) {}
    void setIRLoopVars(CodegenMetadata* metadata) override;
    void setIRIterable(CodegenMetadata* metadata) override;
    Value* loopStart(CodegenMetadata* metadata) override;
    Value* loopEnd(CodegenMetadata* metadata) override;
    ~LgsRangeLoop() override;
};

#endif //LOGOSRANGELOOP_H
