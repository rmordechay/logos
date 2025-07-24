#include "logos/LgsModule.h"
#include "utils/LgsUtils.h"

void LgsModule::initRuntime() {
    const auto voidTy = builder.getVoidTy();
    const auto stackStr = getIRStructType(context, "StackStr", {ArrayType::get(builder.getInt8Ty(), 1024), builder.getInt32Ty()});
    const auto stack = getIRStructType(context, "Stack", {builder.getInt32Ty(), ArrayType::get(stackStr, 512)});
    const auto runtimeType = getIRStructType(context, "Runtime", {stack});
    const auto zeroInit = Constant::getNullValue(runtimeType);
    runtimeStruct = new GlobalVariable(*IRModule, runtimeType, false, GlobalValue::ExternalLinkage, zeroInit);
    const auto initStackFunc = IRModule->getOrInsertFunction("Runtime_init", FunctionType::get(voidTy, {builder.getPtrTy()}, false));
    builder.CreateCall(initStackFunc, {runtimeStruct});
}

void LgsModule::pushStackTrace(const string& path) {
    const auto voidTy = builder.getVoidTy();
    const auto pushStackFunc =IRModule->getOrInsertFunction("Runtime_push", FunctionType::get(voidTy, {builder.getPtrTy(), builder.getPtrTy()}, false));
    builder.CreateCall(pushStackFunc, {runtimeStruct, getIRStr(this, path)});
}

void LgsModule::printStack() {
    const auto voidTy = builder.getVoidTy();
    const auto printStackFunc =IRModule->getOrInsertFunction("Runtime_print_stack", FunctionType::get(voidTy, {builder.getPtrTy()}, false));
    builder.CreateCall(printStackFunc, {runtimeStruct});
}

void LgsModule::addAllocatedExpr(LgsExpr* expr) {
    assert(stack.size() > 0);
    stack.allocatedExprs.push_back(expr);
}
