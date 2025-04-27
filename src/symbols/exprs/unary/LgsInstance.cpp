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
    const auto parentType = obj->getIRType();
    const auto currentFunc = metadata->lgsStack.currentFunc->getIRFunc(metadata);
    if (isSelf && isReturnValue) {
        IRValue = currentFunc->arg_begin();
    } else if (isSelf) {
        IRValue = currentFunc->arg_begin();
    } else if (isReturnValue) {
        IRValue = currentFunc->arg_begin();
    } else {
        IRValue = metadata->builder.CreateAlloca(parentType, nullptr, getName() + "_ptr");
    }
    for (const auto& arg : args) {
        const auto field = obj->getField(arg->name);
        field->setFieldIRValue(metadata, arg->expr, IRValue);
    }
    return IRValue;
}

