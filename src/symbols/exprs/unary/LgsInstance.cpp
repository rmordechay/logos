#include "exprs/unary/LgsInstance.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"
#include "utils/LgsUtils.h"

Value* LgsInstance::createIRValue(LgsModule* module) {
    const auto objIRType = obj->getIRType(module->context);
    if (isReturnExpr) {
        setReturnExpr(module, objIRType);
    } else {
        IRValue = module->builder.CreateAlloca(objIRType);
    }

    for (const auto& [fieldName, field] : obj->fields) {
        auto arg = args.find(fieldName);
        if (arg != args.end()) {
            field->storeIRValue(module, IRValue, arg->second->expr);
        } else {
            field->setZeroValue(module, obj->getIRType(module->context), IRValue);
        }
    }

    return IRValue;
}

void LgsInstance::setZeroField(LgsModule* module, const LgsField* field, Value* parentIRValue) const {
    if (const auto fieldObj = field->type->asObject()) {
        for (const auto& [name, field] : fieldObj->fields) {
            setZeroField(module, field, parentIRValue);
        }
    } else {
        field->storeIRValue(module, parentIRValue, field->expr);
    }
}

string LgsInstance::getExprName() {
    return obj->name;
}

string LgsInstance::prettyName() {
    return obj->name;
}

void LgsInstance::setReturnExpr(LgsModule* module, Type* objIRType) {
    const auto currentFunc = module->stack.currentFunc;
    if (currentFunc->funcType->isSwapReturn) {
        IRValue = currentFunc->getReturnSwapParam().IRValue;
    } else {
        IRValue = module->builder.CreateMalloc(
            i64Ty(module->context),
            objIRType,
            ConstantExpr::getSizeOf(objIRType),
            module->builder.getInt64(1)
        );
        module->addAllocatedExpr(this);
    }
}

void LgsInstance::free(LgsModule* module) {
    if (!isReturnExpr) {
        module->builder.CreateFree(IRValue);
    }
}
