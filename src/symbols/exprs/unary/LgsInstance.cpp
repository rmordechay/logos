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
    if (isSelf) {
        const auto currentFunc = metadata->lgsStack.currentFunc->getIRFunc(metadata);
        return currentFunc->arg_begin();
    }
    const auto parentType = obj->getIRType();
    const auto instanceIR = metadata->builder.CreateAlloca(parentType);
    for (const auto& [_, field] : obj->fields) {
        field->parentIRValue = instanceIR;
        field->parentIRType = parentType;
    }
    if (args.empty()) return instanceIR;
    for (const auto& arg : args) {
        const auto field = obj->getField(arg->name);
        field->setFieldIRValue(metadata, arg->expr);
    }
    return instanceIR;
}

