#include "funcs/LgsMainFunc.h"
#include <llvm/IR/Module.h>
#include "types/iterables/LgsStr.h"
#include "types/primitives/LgsInt.h"
#include <llvm/IR/DIBuilder.h>

Function* LgsMainFunc::getIRFunc(LgsLLVMGen& cg) {
    FunctionType* mainFuncType;
    if (funcType->params.empty()) {
        mainFuncType = cg.getFT(cg.i32Ty());
    } else {
        mainFuncType = cg.getFT(cg.i32Ty(), {cg.i32Ty(), cg.builder.getPtrTy()});
    }
    const auto IRFunc = cg.getFunc(LGS_MAIN_FUNC, mainFuncType);
    if (funcType->params.empty()) return IRFunc;
    auto IRArgs = IRFunc->arg_begin();
    IRArgs->setName("argc");
    IRArgs++;
    IRArgs->setName("argv");
    return IRFunc;
}

void LgsMainFunc::setDebugValue(LgsLLVMGen& cg) {
    const auto diBuilder = cg.debugger.diBuilder;
    const auto dbInt32 = LGS_INT.getDebugType(cg);
    const auto parameterTypes = diBuilder->getOrCreateTypeArray({dbInt32});
    const auto subroutine = diBuilder->createSubroutineType(parameterTypes);
    cg.debugger.diProgram = diBuilder->createFunction(
        cg.debugger.compileUnit,
        funcType->name,
        funcType->name,
        cg.debugger.diFile,
        location.lineStart,
        subroutine,
        location.lineStart,
        llvm::DINode::FlagPrototyped,
        DISubprogram::SPFlagDefinition
    );
    getIRFunc(cg)->setSubprogram(cg.debugger.diProgram);
    cg.builder.SetCurrentDebugLocation(getDebugLoc(cg));
}
