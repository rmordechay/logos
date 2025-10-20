#include "funcs/LgsMainFunc.h"
#include "exprs/LgsArrayExpr.h"
#include <llvm/IR/Module.h>
#include "types/iterables/LgsStr.h"
#include "types/primitives/LgsInt.h"

Function* LgsMainFunc::getIRFunc(LgsLLVMGen& cg) {
    if (IRFunc) return IRFunc;
    FunctionType* mainFuncType;
    if (funcType->params.empty()) {
        mainFuncType = cg.getFT(cg.i32Ty());
    } else {
        mainFuncType = cg.getFT(cg.i32Ty(), {cg.i32Ty(), cg.builder.getPtrTy()});
    }
    IRFunc = cg.getFunc(LGS_MAIN_FUNC_NAME, mainFuncType);
    if (funcType->params.empty()) return IRFunc;
    auto IRArgs = IRFunc->arg_begin();
    argc = IRArgs;
    IRArgs->setName("argc");
    argv = IRArgs++;
    IRArgs->setName("argv");
    return IRFunc;
}

void LgsMainFunc::setMainArgs() {
    assert(0);
}

LgsMainFunc::~LgsMainFunc() {
    if (initArgsFunc) {
        delete initArgsFunc;
        initArgsFunc = nullptr;
    }
}
