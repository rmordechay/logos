#ifndef LOGOSRANGELOOP_H
#define LOGOSRANGELOOP_H
#include "loops/LgsLoop.h"

class LgsRangeLoop final : public LgsLoop {
public:
  LgsExpr* rangeStart = nullptr;
  LgsExpr* rangeEnd = nullptr;

  LgsRangeLoop(LgsExpr* rangeStart, LgsExpr* rangeEnd) : rangeStart(rangeStart), rangeEnd(rangeEnd) {}
  void setIRLoopVariable(CodeGenMetadata* metadata) override;
  int loopStart() override;
  int loopEnd() override;
  ~LgsRangeLoop() override;
};

#endif //LOGOSRANGELOOP_H
