#include "LgsCoroutine.h"

#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsSelection.h"
#include "utils/LgsIRUtils.h"

void LgsCoroutine::createIRStmt(LgsModule* module) {
    // const auto coroIDFunc = getOrInsertDeclaration(module->IRModule, Intrinsic::coro_id);
    // const auto coroBegin = getOrInsertDeclaration(module->IRModule, Intrinsic::coro_begin);
    // const auto coroSuspend = getOrInsertDeclaration(module->IRModule, Intrinsic::coro_suspend);
    // const auto coroEnd = getOrInsertDeclaration(module->IRModule, Intrinsic::coro_end);
    // const auto crID = module->builder.CreateCall(coroIDFunc, {i32Zero(module), null(module), null(module), null(module)});
    // const auto frameTy = ArrayType::get(i8Ty(module), 1024);
    // const auto mallocInst = module->builder.CreateMalloc(i32Ty(module), i32Ty(module), i32(module, 1024), nullptr, nullptr);

    if (stmtsBlock) {
        stmtsBlock->createIRValue(module);
    } else if (funcCall) {
        funcCall->getIRValue(module);
    } else if (selection) {
        selection->getIRValue(module);
    } else {
        assert(0);
    }
}
