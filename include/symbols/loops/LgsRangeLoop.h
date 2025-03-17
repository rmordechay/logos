#ifndef LOGOSRANGELOOP_H
#define LOGOSRANGELOOP_H
#include "loops/LogosLoop.h"

class LgsRangeLoop final : public LgsLoop {
public:
  LgsExpr* rangeStart = nullptr;
  LgsExpr* rangeEnd = nullptr;

  LgsRangeLoop(const vector<LgsVarDec*>& loopVars, LgsExpr* rangeStart, LgsExpr* rangeEnd, LgsStmtBlock* stmtBlock)
    : LgsLoop(loopVars, stmtBlock), rangeStart(rangeStart), rangeEnd(rangeEnd) {}
  Value* createIRValue(CodeGenMetadata* metadata) override;
};

#endif //LOGOSRANGELOOP_H
