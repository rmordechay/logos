#include "exprs/unary/LgsInstance.h"
#include "CodeGenerator.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"

string LgsInstance::getName() {
    return obj->name;
}

Value* LgsInstance::createIRValue(CodeGenMetadata* metadata) {
    const auto IRType = obj->getIRType();
    const auto currentFunc = metadata->lgsStack.currentFunc->getIRFunc(metadata);
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

void LgsInstance::setVirtualFuncs(CodeGenMetadata* metadata) {
    const auto value = vtable.getIRValue(metadata);
    const auto vtableGEP = metadata->builder.CreateStructGEP(obj->getIRType(), IRValue, 0);
    metadata->builder.CreateStore(value, vtableGEP);

    for (const auto [_, method] : obj->getAllMethods()) {
        for (const auto overload : method) {
            if (!overload->funcType.implements) continue;

        }
    }
    const auto constantInt = metadata->builder.getInt32(23);
    const auto valuePtr = metadata->builder.CreateAlloca(i32Ty);
    metadata->builder.CreateStore(constantInt, valuePtr);
    auto keyIRStr = createIRStr(metadata->module, "roi");
    vtable.mapType.add.makeCall(metadata, {value, keyIRStr, valuePtr});
}
