#include "stmts/LgsContinueStmt.h"

#include "utils/LgsUtils.h"


#include <loops/LgsForLoop.h>

void LgsContinueStmt::createIRStmt(LgsModule* module) {
    const auto currentLoop = module->stack.getLoop();
    const auto loopCondition = currentLoop->IRCondBlock;
    const auto iValue = module->builder.CreateLoad(module->builder.getInt32Ty(), currentLoop->iPtr);
    const auto inc = module->builder.CreateAdd(iValue, i32(module, 1));
    module->builder.CreateStore(inc, currentLoop->iPtr);
    module->builder.CreateBr(loopCondition);
}
