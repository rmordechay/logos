#include "logos/LgsRuntime.h"
#include "utils/LgsUtils.h"


void LgsRuntime::initRuntime() {
    const auto voidTy = builder.getVoidTy();
    const auto stackStr = getIRStructType(context, "StackStr", {ArrayType::get(builder.getInt8Ty(), 1024), builder.getInt32Ty()});
    const auto stack = getIRStructType(context, "Stack", {builder.getInt32Ty(), ArrayType::get(stackStr, 512)});
    const auto runtimeType = getIRStructType(context, "Runtime", {stack});
    const auto zeroInit = Constant::getNullValue(runtimeType);
    runtimeStruct = new GlobalVariable(*module, runtimeType, false, GlobalValue::ExternalLinkage, zeroInit);
    const auto initStackFunc = module->getOrInsertFunction("Runtime_init", FunctionType::get(voidTy, {builder.getPtrTy()}, false));
    builder.CreateCall(initStackFunc, {runtimeStruct});
}

void LgsRuntime::pushStackTrace(const string& path) {
    const auto voidTy = builder.getVoidTy();
    const auto pushStackFunc =module->getOrInsertFunction("Runtime_push", FunctionType::get(voidTy, {builder.getPtrTy(), builder.getPtrTy()}, false));
    builder.CreateCall(pushStackFunc, {runtimeStruct, getIRStr(this, path)});
}

void LgsRuntime::printStack() {
    const auto voidTy = builder.getVoidTy();
    const auto printStackFunc =module->getOrInsertFunction("Runtime_print_stack", FunctionType::get(voidTy, {builder.getPtrTy()}, false));
    builder.CreateCall(printStackFunc, {runtimeStruct});
}

void LgsRuntime::addAllocatedExpr(LgsExpr* expr) {
    assert(stack.size() > 0);
    stack.allocatedExprs.push_back(expr);
}

void LgsRuntime::freeExprs() {
    auto& exprs = stack.allocatedExprs;
    exprs.erase(std::remove_if(exprs.begin(), exprs.end(), [this](LgsExpr* expr) {
        if (!expr->isReturnExpr) {
            // expr->free(this);
            return true;
        }
        return false;
    }), exprs.end());
}

