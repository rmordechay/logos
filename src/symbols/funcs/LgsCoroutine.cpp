#include "LgsCoroutine.h"
#include "builtins/LgsBuiltins.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsSelection.h"

void LgsCoroutine::createIRStmt(LgsCodeGen* codeGen) {
    auto& builder = codeGen->builder;
    // codeGen->savedIP = builder.saveIP();
    const auto coroID = codeGen->callCoroIDFunc();
    const auto coroSize = codeGen->callCoroSizeFunc();
    const auto coroBegin = codeGen->callCoroBeginFunc(coroID, coroSize);
    auto callCoroEndFunc = codeGen->callCoroEndFunc(coroBegin);
    // Back to the caller
    // builder.restoreIP(codeGen->savedIP);
}

LgsCoroutine::~LgsCoroutine() {
    if (stmtsBlock) delete stmtsBlock;
    if (funcCall) delete funcCall;
    if (selection) delete selection;
}
