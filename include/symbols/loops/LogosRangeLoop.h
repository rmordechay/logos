#ifndef LOGOSRANGELOOP_H
#define LOGOSRANGELOOP_H
#include "loops/LogosLoop.h"

class LogosRangeLoop final : public LogosLoop {
public:
  LogosLoopVar* loopVar;
  LogosExpr* startRange;
  LogosExpr* endRange;
  LogosStmtBlock* stmtBlock;

  LogosRangeLoop(LogosLoopVar* loopVar, LogosExpr* rangeStart, LogosExpr* rangeEnd, LogosStmtBlock* stmtBlock) : loopVar(loopVar), startRange(rangeStart), endRange(rangeEnd), stmtBlock(stmtBlock) {}
  Value* computeIRValue(CodeGenMetadata* metadata) override;
};

#endif //LOGOSRANGELOOP_H
