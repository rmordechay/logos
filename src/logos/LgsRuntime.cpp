#include "logos/LgsRuntime.h"
#include "configs/LgsDefinitions.h"
#include "logos/LgsCodeGen.h"

void LgsRuntime::setRuntime(LgsCodeGen* codeGen) {
    const auto localsArr = ArrayType::get(codeGen->ptrTy(), 16);
    const auto stackFrameStruct = codeGen->getStructType("stack_frame", {localsArr, codeGen->i32Ty()});
    const auto stackCapacity = ArrayType::get(stackFrameStruct, 64);
    const auto stackStruct = codeGen->getStructType("stack", {stackCapacity, codeGen->i32Ty()});
    const auto runtimeType = codeGen->getStructType("runtime", {stackStruct});
    if (codeGen->IRModule->getName() == LGS_MAIN_FILE_NAME) {
        runtimePtr = codeGen->createGlobal(runtimeType, ConstantAggregateZero::get(runtimeType));
    } else {
        runtimePtr = codeGen->createGlobal(runtimeType, nullptr);
    }
}
