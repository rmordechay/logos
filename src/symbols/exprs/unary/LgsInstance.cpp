#include "exprs/unary/LgsInstance.h"
#include "codegen/CodeGenerator.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"

string LgsInstance::getName() {
    return obj->name;
}

Value* LgsInstance::createIRValue(LgsRuntime* runtime) {
    const auto objIRType = obj->getIRType();
    if (isReturnExpr) {
        setReturnExpr(runtime, objIRType);
    } else {
        IRValue = runtime->builder.CreateAlloca(objIRType);
    }
    unordered_set<string> initializedFields;
    for (const auto arg : args) {
        const auto field = obj->getField(arg->name);
        field->storeIRValue(runtime, IRValue, arg->expr);
        initializedFields.insert(field->name);
    }
    for (const auto& [name, field] : obj->fields) {
        if (initializedFields.count(name)) continue;
        if (const auto fieldObj = field->type->asObject()) {
            setZeroFields(runtime, fieldObj, IRValue);
        } else {
            const auto zeroValue = field->type->getZeroValue();
            field->storeIRValue(runtime, IRValue, zeroValue);
        }
    }
    return IRValue;
}

void LgsInstance::setZeroFields(LgsRuntime* runtime, LgsObject* object, Value* parentIRValue) const {
    for (const auto& [name, field] : object->fields) {
        if (const auto fieldObj = field->type->asObject()) {
            setZeroFields(runtime, fieldObj, parentIRValue);
        } else {
            const auto zeroValue = field->type->getZeroValue();
            field->storeIRValue(runtime, parentIRValue, zeroValue);
        }
    }
}

void LgsInstance::setReturnExpr(LgsRuntime* runtime, Type* objIRType) {
    const auto currentFunc = runtime->stack.currentFunc;
    if (currentFunc->funcType->hasFlag(SWAP_RETURN)) {
        IRValue = currentFunc->getReturnSwapParam().IRValue;
    } else {
        IRValue = runtime->builder.CreateMalloc(
            Type::getInt64Ty(context),
            objIRType,
            ConstantExpr::getSizeOf(objIRType),
            ConstantInt::get(Type::getInt64Ty(context), 1)
        );
        runtime->addAllocatedExpr(this);
    }
}

void LgsInstance::free(LgsRuntime* runtime) {
    if (!isReturnExpr) {
        runtime->builder.CreateFree(IRValue);
    }
}
