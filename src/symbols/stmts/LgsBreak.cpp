#include "stmts/LgsBreak.h"

#include "logos/LgsCodeGen.h"
#include "loops/LgsForLoop.h"

json::value_ref LgsBreak::asJSON() {
    json::object obj;
    return obj;
}

void LgsBreak::createIRValue(LgsCodeGen* codeGen) {
    const auto loop = codeGen->stack.currentLoop();
    codeGen->builder.CreateBr(loop->IRExitBlock);
}
