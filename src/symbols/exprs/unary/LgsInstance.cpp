#include "exprs/unary/LgsInstance.h"
#include "CodeGenerator.h"
#include "funcs/LgsFunc.h"
#include "funcs/LgsMethodImpl.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"

string LgsInstance::getName() {
    return obj->name;
}

Value* LgsInstance::createIRValue(CodeGenMetadata* metadata) {
    const auto IRType = obj->getIRType();
    const auto currentFunc = metadata->lgsStack.currentFunc->createIRFunc(metadata);
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
    auto& builder = metadata->builder;
    const auto methods = obj->getAllMethods();
    for (const auto& method : methods) {
        if (!method->implements) continue;
        const auto gep = builder.CreateStructGEP(obj->getIRType(), IRValue, method->implements->vtableKey);
        builder.CreateStore(method->createIRFunc(metadata), gep);
    }
}
