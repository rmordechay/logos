#include "exprs/unary/LgsInstance.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"

Value* LgsInstance::createIRValue(LgsRuntime* runtime) {
    const auto objIRType = obj->getIRType();
    if (isReturnExpr) {
        setReturnExpr(runtime, objIRType);
    } else {
        IRValue = runtime->builder.CreateAlloca(objIRType);
    }

    for (const auto& [fieldName, field] : obj->fields) {
        auto arg = args.find(fieldName);
        if (arg != args.end()) {
            field->storeIRValue(runtime, obj->getIRType(), IRValue, arg->second->expr);
        } else {
            field->setZeroValue(runtime, obj->getIRType(), IRValue);
        }
    }

    return IRValue;
}

void LgsInstance::setZeroField(LgsRuntime* runtime, LgsField* field, Value* parentIRValue) const {
    if (const auto fieldObj = field->type->asObject()) {
        for (const auto& [name, field] : fieldObj->fields) {
            setZeroField(runtime, field, parentIRValue);
        }
    } else {
        field->storeIRValue(runtime, obj->getIRType(), parentIRValue, field->expr);
    }
}

string LgsInstance::getExprName() {
    return obj->name;
}

string LgsInstance::prettyName() {
    return obj->name;
}

void LgsInstance::setReturnExpr(LgsRuntime* runtime, Type* objIRType) {
    const auto currentFunc = runtime->stack.currentFunc;
    if (currentFunc->funcType->isSwapReturn) {
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
