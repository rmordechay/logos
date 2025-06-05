#include "exprs/unary/LgsInstance.h"
#include "codegen/CodeGenerator.h"
#include "builtin/LgsPrint.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"

string LgsInstance::getName() {
    return obj->name;
}

Value* LgsInstance::createIRValue(LgsRuntime* runtime) {
    const auto currentFunc = runtime->stack.currentFunc;
    if (currentFunc->funcType.swapReturn && isReturnExpr) {
        IRValue = currentFunc->getReturnParam()->IRValue;
    } else {
        IRValue = runtime->builder.CreateAlloca(obj->getIRType());
    }
    if (!obj->implements.empty()) {
        setVirtualFuncs(runtime);
    }
    for (const auto arg : args) {
        const auto field = obj->getField(arg->name);
        field->setFieldIRValue(runtime, arg->expr, IRValue);
    }
    return IRValue;
}

void LgsInstance::setVirtualFuncs(LgsRuntime* runtime) const {
    const auto map = obj->vtable.getIRValue(runtime);
    const auto vtableGEP = runtime->builder.CreateStructGEP(obj->getIRType(), IRValue, 0);
    runtime->builder.CreateStore(map, vtableGEP);
    auto mapPtr = runtime->builder.CreateLoad(PointerType::getUnqual(context), vtableGEP);
    for (const auto& [name, method] : obj->methods) {
        const auto interface = method->implements;
        if (!interface) continue;
        const auto keyIRStr = getIRStr(runtime, interface->funcType.getIRName());
        const auto IRFunc = method->getIRFunc(runtime);
        auto valuePtr = runtime->builder.CreateAlloca(PointerType::getUnqual(context));
        runtime->builder.CreateStore(IRFunc, valuePtr);
        obj->vtable.mapType.add.callIR(runtime, {mapPtr, keyIRStr, valuePtr});
    }
}
