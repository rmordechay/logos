#include "stmts/LgsBreak.h"

#include "logos/LgsCodeGen.h"
#include "loops/LgsForLoop.h"

void LgsBreak::createIRValue(LgsCodeGen* codeGen) {
    const auto loop = codeGen->stack.currentLoop();
    codeGen->builder.CreateBr(loop->IRExitBlock);
}
