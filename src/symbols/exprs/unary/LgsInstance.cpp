#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsHashMap.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"
#include "utils/LgsIRUtils.h"

string LgsInstance::prettyName() {
    return obj->name;
}

Value* LgsInstance::createIRValue(LgsModule* module) {
    const auto objIRType = obj->getIRType(module);
    if(obj->singleton) {
        const auto zeroInitializer = ConstantAggregateZero::get(objIRType);
        IRValue = new GlobalVariable(*module->IRModule, objIRType, false, GlobalValue::ExternalLinkage, zeroInitializer);
    } else {
        IRValue = module->builder.CreateAlloca(objIRType);
    }
    initFields(module);
    if (obj->hasVirtuals) {
        setVirtuals(module);
    }
    return IRValue;
}

void LgsInstance::initFields(LgsModule* module) {
    for (const auto& [fieldName, field] : obj->fields) {
        auto arg = args.find(fieldName);
        if (arg != args.end()) {
            field->storeIRValue(module, IRValue, arg->second->expr);
        }
    }
}

void LgsInstance::setVirtuals(LgsModule* module) const {
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
    for (const auto& [name, field] : obj->fields) {
        if (!field->isVirtual) continue;
        const auto keyIRStr = getIRStr(module, field->name);
        const auto fieldGEP = field->getGEP(module, IRValue);
        const auto fieldIRType = field->type->getIRType(module);
        const auto loadGEP = module->builder.CreateLoad(fieldIRType, fieldGEP);
        const auto valuePtr = module->builder.CreateAlloca(fieldIRType);
        module->builder.CreateStore(loadGEP, valuePtr);
        vtable->addFunc.callIR(module, {vtableGEP, keyIRStr, valuePtr});
    }
}

void LgsInstance::free(LgsModule* module) {
    if (!isHeapAlloc) {
        module->builder.CreateFree(IRValue);
    }
}

LgsInstance::~LgsInstance() {
    for (const auto arg : args) {
        delete arg.second;
    }
}
