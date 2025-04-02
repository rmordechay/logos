#ifndef LOGOSRANGELOOP_H
#define LOGOSRANGELOOP_H
#include "loops/LgsLoop.h"

class LgsRangeLoop final : public LgsLoop {
public:
  LgsExpr* rangeStart = nullptr;
  LgsExpr* rangeEnd = nullptr;

  LgsRangeLoop(const vector<LgsVarDec*>& loopVars, LgsExpr* rangeStart, LgsExpr* rangeEnd, LgsStmtBlock* stmtBlock) : LgsLoop(loopVars, stmtBlock), rangeStart(rangeStart), rangeEnd(rangeEnd) {}
  void setIRBody(CodeGenMetadata* metadata) override;
  int loopStart() override;
  int loopEnd() override;
};

#endif //LOGOSRANGELOOP_H
