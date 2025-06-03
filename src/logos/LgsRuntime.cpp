#include "logos/LgsRuntime.h"

#include "data/LgsErrors.h"
#include "exprs/unary/LgsEnumField.h"
#include "funcs/LgsFunc.h"
#include "logos/LgsErrHandler.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsEnum.h"
#include "types/LgsInterface.h"
#include "utils/LgsUtils.h"

void LgsRuntime::initRuntime(LgsRuntime* runtime) {
    const auto voidTy = runtime->builder.getVoidTy();
    const auto stackStr = getIRStructType(context, "StackStr", {ArrayType::get(runtime->builder.getInt8Ty(), 1024), runtime->builder.getInt32Ty()});
    const auto stack = getIRStructType(context, "Stack", {runtime->builder.getInt32Ty(), ArrayType::get(stackStr, 512)});
    const auto runtimeType = getIRStructType(context, "Runtime", {stack});
    const auto zeroInit = Constant::getNullValue(runtimeType);
    runtimeStruct = new GlobalVariable(*runtime->module, runtimeType, false, GlobalValue::ExternalLinkage, zeroInit);
    const auto initStackFunc = runtime->module->getOrInsertFunction("Runtime_init", FunctionType::get(voidTy, {runtime->builder.getPtrTy()}, false));
    runtime->builder.CreateCall(initStackFunc, {runtimeStruct});
}

void LgsRuntime::pushStackTrace(LgsRuntime* runtime, const string& path) const {
    const auto voidTy = runtime->builder.getVoidTy();
    const auto pushStackFunc =runtime->module->getOrInsertFunction("Runtime_push", FunctionType::get(voidTy, {runtime->builder.getPtrTy(), runtime->builder.getPtrTy()}, false));
    runtime->builder.CreateCall(pushStackFunc, {runtimeStruct, getIRStr(runtime, path)});
}

void LgsRuntime::printStack(LgsRuntime* runtime) const {
    const auto voidTy = runtime->builder.getVoidTy();
    const auto printStackFunc =runtime->module->getOrInsertFunction("Runtime_print_stack", FunctionType::get(voidTy, {runtime->builder.getPtrTy()}, false));
    runtime->builder.CreateCall(printStackFunc, {runtimeStruct});
}

void LgsRuntime::addAllocatedExpr(LgsExpr* expr) {
    assert(stack.size() > 0);
    stack.top().allocatedExprs.emplace_back(expr);
}

void LgsRuntime::freeExprs(LgsRuntime* runtime) {
    const auto& exprs = stack.top().allocatedExprs;
    for (const auto expr : exprs) {
        expr->free(runtime);
    }
    stack.top().allocatedExprs.clear();
}

void LgsGlobals::addSymbol(const string& name, const LgsSymbol& symbol, LgsErrHandler* errHandler) {
    if (symbols.find(name) != symbols.end()) {
        const auto location = symbol.getLocation();
        errHandler->handleError(E10011, location, {name, location->lineNumberStr()});
        return;
    }
    std::lock_guard lock(mtx);
    symbols[name] = symbol;
}

void LgsGlobals::addEnum(LgsEnum* lgsEnum, LgsErrHandler* errHandler) {
    if (symbols.find(lgsEnum->name) != symbols.end()) {
        const auto location = lgsEnum->location;
        errHandler->handleError(E10011, &location, {lgsEnum->name, location.lineNumberStr()});
        return;
    }
    lock_guard lock(mtx);
    symbols[lgsEnum->name] = LgsSymbol(lgsEnum);
    for (const auto& [name, field] : lgsEnum->fields) {
        symbols[name] = LgsSymbol(dynamic_cast<LgsEnumField*>(field));
    }
}

LgsGlobals::~LgsGlobals() {
    for (const auto& [_, symbol] : symbols) {
        switch (symbol.type) {
        case VAR_DEC: delete symbol.varDec; break;
        case PARAM: delete symbol.param; break;
        case OBJECT: delete symbol.object; break;
        case INTERFACE: delete symbol.interface; break;
        case FUNC: if (!symbol.func->funcType.isBuiltin) delete symbol.func; break;
        case ENUM: delete symbol.lgsEnum; break;
        case ENUM_FIELD: delete symbol.enumField; break;
        default: break;
        }
    }
}