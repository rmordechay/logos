#include "funcs/LgsMainFunc.h"

#include <llvm/IR/DIBuilder.h>
#include <llvm/ADT/ArrayRef.h>
#include <llvm/ADT/Twine.h>
#include <llvm/IR/DebugInfoMetadata.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <vector>

#include "types/primitives/LgsInt.h"
#include "codegen/LgsCodeGen.h"
#include "LgsTokens.h"

Function* LgsMainFunc::getIRFunc(LgsCodeGen& cg) {
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

void LgsMainFunc::setDebugValue(LgsCodeGen& cg) {
    const auto diBuilder = cg.debugger.diBuilder;
    const auto dbInt32 = LGS_INT.getDebugType(cg);
    const auto parameterTypes = diBuilder->getOrCreateTypeArray({dbInt32});
    const auto subroutine = diBuilder->createSubroutineType(parameterTypes);
    cg.debugger.subprogram = diBuilder->createFunction(
        cg.debugger.compileUnit,
        funcType->name,
        funcType->name,
        cg.debugger.diFile,
        location.lineStart,
        subroutine,
        location.lineStart,
        DINode::FlagPrototyped,
        DISubprogram::SPFlagDefinition
    );
    getIRFunc(cg)->setSubprogram(cg.debugger.subprogram);
    setDebugLoc(cg);
}
