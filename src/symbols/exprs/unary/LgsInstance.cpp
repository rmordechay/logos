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

Value* LgsInstance::createIRValue(CodeGenMetadata* metadata) {
    const auto IRType = obj->getIRType();
    const auto currentFunc = metadata->runtime.getCurrentFunc()->getIRFunc(metadata);
    auto& builder = metadata->builder;
    // TODO cover all cases
    if (isSelf || isReturnValue) {
        IRValue = currentFunc->arg_begin();
    } else {
        IRValue = builder.CreateAlloca(IRType);
    }
    if (!obj->implements.empty()) {
        setVirtualFuncs(metadata);
    }
    for (const auto& arg : args) {
        const auto field = obj->getField(arg->name);
        field->setFieldIRValue(metadata, arg->expr, IRValue);
    }
    return IRValue;
}

void LgsInstance::setVirtualFuncs(CodeGenMetadata* metadata) const {
    const auto map = obj->vtable.getIRValue(metadata);
    auto& builder = metadata->builder;
    const auto vtableGEP = builder.CreateStructGEP(obj->getIRType(), IRValue, 0);
    builder.CreateStore(map, vtableGEP);
    auto mapPtr = builder.CreateLoad(ptrTy, vtableGEP);

    for (const auto& [name, method] : obj->methods) {
        const auto interface = method->implements;
        if (!interface) continue;
        const auto keyIRStr = getIRStr(metadata->module, interface->funcType.getIRName());
        const auto IRFunc = method->getIRFunc(metadata);
        auto valuePtr = builder.CreateAlloca(ptrTy);
        builder.CreateStore(IRFunc, valuePtr);
        obj->vtable.mapType.add.callIR(metadata, {mapPtr, keyIRStr, valuePtr});

    }
}
