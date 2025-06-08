#include "LgsVTable.h"

#include "types/LgsInterface.h"
#include "types/LgsObject.h"

void LgsVTable::setImplementsVFuncs(LgsRuntime* runtime, LgsObject* obj, Value* IRValue) const {
    auto& builder = runtime->builder;
    const auto map = obj->vtable->getIRValue(runtime);
    const auto vtableGEP = builder.CreateStructGEP(obj->getIRType(), IRValue, 0);
    builder.CreateStore(map, vtableGEP);
    auto mapPtr = builder.CreateLoad(PointerType::getUnqual(context), vtableGEP);
    for (const auto& [name, method] : obj->methods) {
        const auto interface = method->implements;
        if (!interface) continue;
        const auto keyIRStr = getIRStr(runtime, interface->funcType.getIRName());
        const auto IRFunc = method->getIRFunc(runtime);
        auto valuePtr = builder.CreateAlloca(PointerType::getUnqual(context));
        builder.CreateStore(IRFunc, valuePtr);
        obj->vtable->mapType.add.callIR(runtime, {mapPtr, keyIRStr, valuePtr});
    }
}

Value* LgsVTable::resolveVirtualFunc(LgsRuntime* runtime, LgsExpr* parent, LgsFunc* func) const {
    auto& builder = runtime->builder;
    const auto type = parent->type;
    const auto parentIRValue = parent->getIRValue(runtime);
    if (const auto group = type->asGroup()) {
        assert(false);
    }
    if (const auto interface = type->asInterface()) {
        const auto keyIR = getIRStr(runtime, func->funcType.getIRName());
        const auto mapPtr = builder.CreateLoad(PointerType::getUnqual(context), parentIRValue);
        const auto rv = interface->vtable->mapType.get.callIR(runtime, {mapPtr, keyIR});
        const auto getValuePtr = builder.CreateAlloca(PointerType::getUnqual(context));
        builder.CreateStore(rv, getValuePtr);
        return builder.CreateLoad(PointerType::getUnqual(context), builder.CreateLoad(PointerType::getUnqual(context), getValuePtr));
    }
    assert(false);
}