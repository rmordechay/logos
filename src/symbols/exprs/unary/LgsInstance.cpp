#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsHashMap.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"
#include "utils/LgsUtils.h"

Value* LgsInstance::createIRValue(LgsModule* module) {
    const auto parentIRType = obj->getIRType(module);
    const auto objIRType = parentIRType;
    if (isReturnExpr) {
        setReturnExpr(module, objIRType);
    } else {
        IRValue = module->builder.CreateAlloca(objIRType);
    }

    for (const auto& [fieldName, field] : fields) {
        field->parentIRType = parentIRType;
        field->parentIRValue = IRValue;
        auto arg = args.find(fieldName);
        if (arg != args.end()) {
            field->storeIRValue(module, arg->second->expr);
        } else {
            field->setZeroValue(module);
        }
    }

    if (!obj->hasVirtual) {
        setVirtualFuncs(module);
    }
    return IRValue;
}

void LgsInstance::setVirtualFuncs(LgsModule* module) const {
    const auto vtable = obj->vtable->type->asMap();
    const auto vtableGEP = module->builder.CreateGEP(vtable->getIRType(module), IRValue, {i32(module, 0)});
    vtable->initFunc.callIR(module, {vtableGEP, i64(module, sizeof(void*))});
    for (const auto& [name, method] : obj->methods) {
        if (!method->funcType->isVirtual) continue;
        const auto keyIRStr = getIRStr(module, method->funcType->getName());
        const auto IRFunc = method->getIRFunc(module);
        const auto valuePtr = module->builder.CreateAlloca(ptrTy(module));
        module->builder.CreateStore(IRFunc, valuePtr);
        vtable->addFunc.callIR(module, {vtableGEP, keyIRStr, valuePtr});
    }
    for (const auto& [name, field] : fields) {
        if (!field->isVirtual) continue;
        const auto keyIRStr = getIRStr(module, field->name);
        const auto gep = field->getGEP(module);
        const auto ty = field->type->getIRType(module);
        const auto v = module->builder.CreateLoad(ty, gep);
        const auto valuePtr = module->builder.CreateAlloca(ty);
        module->builder.CreateStore(v, valuePtr);
        vtable->addFunc.callIR(module, {vtableGEP, keyIRStr, valuePtr});
    }
}

string LgsInstance::getExprName() {
    return obj->name;
}

string LgsInstance::prettyName() {
    return obj->name;
}

void LgsInstance::setReturnExpr(LgsModule* module, Type* objIRType) {
    const auto currentFunc = module->stack.currentFunc();
    if (currentFunc->funcType->isSwapReturn) {
        IRValue = currentFunc->getReturnSwapParam().IRValue;
    } else {
        IRValue = module->builder.CreateMalloc(
            i64Ty(module),
            objIRType,
            ConstantExpr::getSizeOf(objIRType),
            i64(module, 1)
        );
        module->stack.currentFunc()->allocatedExprs.push_back(this);
    }
}

void LgsInstance::free(LgsModule* module) {
    if (!isReturnExpr) {
        module->builder.CreateFree(IRValue);
    }
}

LgsInstance::~LgsInstance() {
    for (const auto field : fields) {
        delete field.second;
    }
    for (const auto arg : args) {
        delete arg.second;
    }
}
