#include "funcs/LgsMainFunc.h"
#include "exprs/LgsArrayExpr.h"
#include <llvm/IR/Module.h>
#include "types/iterables/LgsStr.h"

Function* LgsMainFunc::getIRFunc(LgsLLVMGen& cg) {
    FunctionType* mainFuncType;
    if (funcType->params.empty()) {
        mainFuncType = cg.getFT(cg.i32Ty());
    } else {
        mainFuncType = cg.getFT(cg.i32Ty(), {cg.i32Ty(), cg.builder.getPtrTy()});
    }
    const auto IRFunc = cg.getFunc(LGS_MAIN_FUNC_NAME, mainFuncType);
    if (funcType->params.empty()) return IRFunc;
    auto IRArgs = IRFunc->arg_begin();
    IRArgs->setName("argc");
    IRArgs++;
    IRArgs->setName("argv");
    return IRFunc;
}

LgsMainFunc::~LgsMainFunc() {
    freeExpr(args);
    args = nullptr;
}
