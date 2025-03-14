#ifndef LOGOSRANGELOOP_H
#define LOGOSRANGELOOP_H
#include "loops/LogosLoop.h"

class LgsRangeLoop final : public LgsLoop {
public:
  LgsLoopVar* loopVar;
  LogosExpr* startRange;
  LogosExpr* endRange;
  LgsStmtBlock* stmtBlock;

  LgsRangeLoop(LgsLoopVar* loopVar, LogosExpr* rangeStart, LogosExpr* rangeEnd, LgsStmtBlock* stmtBlock) : loopVar(loopVar), startRange(rangeStart), endRange(rangeEnd), stmtBlock(stmtBlock) {}
  Value* createIRValue(CodeGenMetadata* metadata) override;
};

#endif //LOGOSRANGELOOP_H
