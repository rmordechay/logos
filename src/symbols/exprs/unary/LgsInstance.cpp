#include "exprs/unary/LgsInstance.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"
#include "utils/LgsUtils.h"

Value* LgsInstance::createIRValue(LgsModule* runtime) {
    const auto objIRType = obj->getIRType(runtime->context);
    if (isReturnExpr) {
        setReturnExpr(runtime, objIRType);
    } else {
        IRValue = runtime->builder.CreateAlloca(objIRType);
    }

    for (const auto& [fieldName, field] : obj->fields) {
        auto arg = args.find(fieldName);
        if (arg != args.end()) {
            field->storeIRValue(runtime, obj->getIRType(runtime->context), IRValue, arg->second->expr);
        } else {
            field->setZeroValue(runtime, obj->getIRType(runtime->context), IRValue);
        }
    }

    return IRValue;
}

void LgsInstance::setZeroField(LgsModule* runtime, const LgsField* field, Value* parentIRValue) const {
    if (const auto fieldObj = field->type->asObject()) {
        for (const auto& [name, field] : fieldObj->fields) {
            setZeroField(runtime, field, parentIRValue);
        }
    } else {
        field->storeIRValue(runtime, obj->getIRType(runtime->context), parentIRValue, field->expr);
    }
}

string LgsInstance::getExprName() {
    return obj->name;
}

string LgsInstance::prettyName() {
    return obj->name;
}

void LgsInstance::setReturnExpr(LgsModule* runtime, Type* objIRType) {
    const auto currentFunc = runtime->stack.currentFunc;
    if (currentFunc->funcType->isSwapReturn) {
        IRValue = currentFunc->getReturnSwapParam().IRValue;
    } else {
        IRValue = runtime->builder.CreateMalloc(
            i64Ty(runtime->context),
            objIRType,
            ConstantExpr::getSizeOf(objIRType),
            runtime->builder.getInt64(1)
        );
        runtime->addAllocatedExpr(this);
    }
}

void LgsInstance::free(LgsModule* runtime) {
    if (!isReturnExpr) {
        runtime->builder.CreateFree(IRValue);
    }
}
