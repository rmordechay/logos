#include "exprs/unary/LgsInstance.h"
#include "codegen/CodeGenerator.h"
#include "builtin/LgsPrint.h"
#include "funcs/LgsFunc.h"
#include "logos/LgsGlobals.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"

string LgsInstance::getName() {
    return obj->name;
}

Value* LgsInstance::createIRValue(Module* module) {
    const auto IRType = obj->getIRType();
    const auto currentFunc = runtime.getCurrentFunc()->getIRFunc(module);

    // TODO cover all cases
    if (isSelf || isReturnValue) {
        IRValue = currentFunc->arg_begin();
    } else {
        IRValue = builder.CreateAlloca(IRType);
    }
    if (!obj->implements.empty()) {
        setVirtualFuncs(module);
    }
    for (const auto& arg : args) {
        const auto field = obj->getField(arg->name);
        field->setFieldIRValue(module, arg->expr, IRValue);
    }
    return IRValue;
}

void LgsInstance::setVirtualFuncs(Module* module) const {
    const auto map = obj->vtable.getIRValue(module);

    const auto vtableGEP = builder.CreateStructGEP(obj->getIRType(), IRValue, 0);
    builder.CreateStore(map, vtableGEP);
    auto mapPtr = builder.CreateLoad(ptrTy, vtableGEP);

    for (const auto& [name, method] : obj->methods) {
        const auto interface = method->implements;
        if (!interface) continue;
        const auto keyIRStr = getIRStr(module, interface->funcType.getIRName());
        const auto IRFunc = method->getIRFunc(module);
        auto valuePtr = builder.CreateAlloca(ptrTy);
        builder.CreateStore(IRFunc, valuePtr);
        obj->vtable.mapType.add.callIR(module, {mapPtr, keyIRStr, valuePtr});

    }
}
