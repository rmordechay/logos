#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsHashMap.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"
#include "utils/LgsUtils.h"

Value* LgsInstance::createIRValue(LgsModule* module) {
    const auto objIRType = obj->getIRType(module);
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
            field->setZeroValue(module, obj->getIRType(module), IRValue);
        }
    }

    if (!obj->hasVirtual) {
        setVirtualFuncs(module);
    }
    return IRValue;
}

void LgsInstance::setVirtualFuncs(LgsModule* module) {
    const auto vtable = obj->vtable->type->asMap();
    const auto vtableGEP = cast<GetElementPtrInst>(module->builder.CreateStructGEP(obj->getIRType(module), IRValue, 0));
    const auto elementSize = i64(module, 8);
    vtable->initFunc.callIR(module, {vtableGEP, elementSize});
    for (const auto& [name, method] : obj->methods) {
        const auto implementFunc = method->implementsFunc;
        if (!implementFunc) continue;
        const auto keyIRStr = getIRStr(module, implementFunc->funcType->getName());
        const auto IRFunc = method->getIRFunc(module);
        const auto valuePtr = module->builder.CreateAlloca(ptrTy(module));
        module->builder.CreateStore(IRFunc, valuePtr);
        vtable->addFunc.callIR(module, {vtableGEP, keyIRStr, valuePtr});
    }
    for (const auto& [name, field] : obj->fields) {
        const auto implementField = field->implementsField;
        if (!implementField) continue;
        const auto keyIRStr = getIRStr(module, implementField->name);
        const auto positionPtr = module->builder.CreateAlloca(i64Ty(module));
        module->builder.CreateStore(i64(module, field->position), positionPtr);
        vtable->addFunc.callIR(module, {vtableGEP, keyIRStr, positionPtr});
    }
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
            i64Ty(module),
            objIRType,
            ConstantExpr::getSizeOf(objIRType),
            i64(module, 1)
        );
        module->addAllocatedExpr(this);
    }
}

void LgsInstance::free(LgsModule* module) {
    if (!isReturnExpr) {
        module->builder.CreateFree(IRValue);
    }
}
