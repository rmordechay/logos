#include "LgsCoroutine.h"

#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsSelection.h"
#include "utils/LgsIRUtils.h"

void LgsCoroutine::createIRStmt(LgsModule* module) {
    // const auto coroSizeFunc = getOrInsertDeclaration(module->IRModule, Intrinsic::coro_size, {sizeTy(module)});
    // const auto coroIDFunc = getOrInsertDeclaration(module->IRModule, Intrinsic::coro_id);
    // // const auto coroBegin = getOrInsertDeclaration(module->IRModule, Intrinsic::coro_begin);
    // // const auto coroSuspend = getOrInsertDeclaration(module->IRModule, Intrinsic::coro_suspend);
    // // const auto coroEnd = getOrInsertDeclaration(module->IRModule, Intrinsic::coro_end);
    // const auto crID = module->builder.CreateCall(coroIDFunc, {i32Zero(module), null(module), null(module), null(module)});
    // // const auto size = module->builder.CreateCall(coroSizeFunc);
    // const auto frameTy = ArrayType::get(ptrTy(module), 1024);
    // const auto allocaTy = PointerType::getUnqual(frameTy);
    // const auto mallocInst = module->builder.CreateMalloc(ptrTy(module), frameTy, i64(module, 1), nullptr);


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
