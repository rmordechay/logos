#include "logos/LgsRuntime.h"
#include "logos/LgsGlobals.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsVarDec.h"
#include "utils/LgsUtils.h"

void LgsRuntime::enterFunc(LgsFunc* func) {
    if (stack.empty()) {
        returnFunc = func;
        stack.push(LgsStackFrame{.func = func});
    } else {
        returnFunc = getCurrentFunc();
        stack.push(LgsStackFrame{.symbols = getSymbols(), .func = func, .loop = getCurrentLoop()});
    }
    if (stage == LGS_RUNTIME) {
        returnFunc->savedIP = builder.saveIP();
    }
}

void LgsRuntime::enterScope() {
    stack.push(LgsStackFrame{
        .symbols = getSymbols(),
        .func = getCurrentFunc(),
        .loop = getCurrentLoop()
    });
}

void LgsRuntime::exitFunc() {
    stack.pop();
    if (stage == LGS_RUNTIME && returnFunc) builder.restoreIP(returnFunc->savedIP);
    returnFunc = nullptr;
}

void LgsRuntime::exitScope() {
    stack.pop();
}

void LgsRuntime::reset() {
    while (stack.size() > 0) {
        stack.pop();
    }
    returnFunc = nullptr;
}

void LgsRuntime::initRuntime(Module* mainModule) {
    const auto stackStr = getIRStructType("StackStr", {ArrayType::get(i8Ty, 1024), i32Ty});
    const auto stack = getIRStructType("Stack", {i32Ty, ArrayType::get(stackStr, 512)});
    const auto runtimeType = getIRStructType("Runtime", {stack});
    const auto zeroInit = Constant::getNullValue(runtimeType);
    runtimeStruct = new GlobalVariable(*mainModule, runtimeType, false, GlobalValue::ExternalLinkage, zeroInit);
    const auto initStackFunc = mainModule->getOrInsertFunction("Runtime_init", FunctionType::get(voidTy, {ptrTy}, false));
    builder.CreateCall(initStackFunc, {runtimeStruct});
}

void LgsRuntime::pushStackTrace(Module* module, const string& path) const {
    const auto pushStackFunc = module->getOrInsertFunction("Runtime_push", FunctionType::get(voidTy, {ptrTy, ptrTy}, false));
    builder.CreateCall(pushStackFunc, {runtimeStruct, getIRStr(module, path)});
}

void LgsRuntime::printStack(Module* module) const {
    const auto printStackFunc = module->getOrInsertFunction("Runtime_print_stack", FunctionType::get(voidTy, {ptrTy}, false));
    builder.CreateCall(printStackFunc, {runtimeStruct});
}

LgsFunc* LgsRuntime::getCurrentFunc() {
    assert(stack.size() > 0);
    return stack.top().func;
}

LgsForLoop* LgsRuntime::getCurrentLoop() {
    assert(stack.size() > 0);
    return stack.top().loop;
}

map<string, LgsSymbol>& LgsRuntime::getSymbols() {
    assert(stack.size() > 0);
    return stack.top().symbols;
}

void LgsRuntime::addLocalSymbol(const string& name, const LgsSymbol& symbol) {
    assert(stack.size() > 0);
    stack.top().symbols[name] = symbol;
}

void LgsRuntime::addAllocatedExpr(LgsExpr* expr) {
    assert(stack.size() > 0);
    stack.top().allocatedExprs.emplace_back(expr);
}

void LgsRuntime::freeExprs(Module* module) {
    const auto& exprs = stack.top().allocatedExprs;
    for (const auto expr : exprs) {
        expr->free(module);
    }
    stack.top().allocatedExprs.clear();
}
