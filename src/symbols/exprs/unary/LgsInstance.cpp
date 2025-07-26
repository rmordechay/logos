#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsHashMap.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"
#include "utils/LgsIRUtils.h"
#include "utils/LgsUtils.h"

string LgsInstance::prettyName() {
    return obj->name;
}

Value* LgsInstance::createIRValue(LgsModule* module) {
    const auto parentIRType = obj->getIRType(module);
    const auto objIRType = parentIRType;
    IRValue = module->builder.CreateAlloca(objIRType);

    for (const auto& [fieldName, field] : fields) {
        field->parentIRType = parentIRType;
        field->parentIRValue = IRValue;
        auto arg = args.find(fieldName);
        if (arg != args.end()) {
            field->storeIRValue(module, arg->second->expr);
        } else {
            field->storeIRZeroValue(module);
        }
    }

    if (obj->hasVirtuals) {
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

void LgsInstance::copyFields() {
    assert(fields.empty());
    for (auto [name, field] : obj->fields) {
        fields[name] = field->clone();
    }
}

void LgsInstance::free(LgsModule* module) {
    if (!isHeapAlloc) {
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
