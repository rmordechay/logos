#ifndef LOGOSRANGELOOP_H
#define LOGOSRANGELOOP_H
#include "loops/LogosLoop.h"

class LgsRangeLoop final : public LgsLoop {
public:
  LgsLoopVar* loopVar;
  LgsExpr* startRange;
  LgsExpr* endRange;
  LgsStmtBlock* stmtBlock;

  LgsRangeLoop(LgsLoopVar* loopVar, LgsExpr* rangeStart, LgsExpr* rangeEnd, LgsStmtBlock* stmtBlock) : loopVar(loopVar), startRange(rangeStart), endRange(rangeEnd), stmtBlock(stmtBlock) {}
  Value* createIRValue(CodeGenMetadata* metadata) override;
};

#endif //LOGOSRANGELOOP_H
