#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsHashMap.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"


string LgsInstance::prettyName() {
    return obj->name;
}

Value* LgsInstance::createIRValue(LgsCodeGen* codeGen) {
    const auto objIRType = obj->getIRType(codeGen);
    if(obj->singleton) {
        const auto zeroInitializer = ConstantAggregateZero::get(objIRType);
        IRValue = new GlobalVariable(*codeGen->IRModule, objIRType, false, GlobalValue::ExternalLinkage, zeroInitializer);
    } else {
        IRValue = codeGen->builder.CreateAlloca(objIRType);
    }
    initFields(codeGen);
    if (obj->hasVirtuals) {
        setVirtuals(codeGen);
    }
    return IRValue;
}

void LgsInstance::initFields(LgsCodeGen* codeGen) {
    for (const auto& [fieldName, field] : obj->fields) {
        auto arg = args.find(fieldName);
        if (arg != args.end()) {
            field->storeIRValue(codeGen, IRValue, arg->second->expr);
        }
    }
}

void LgsInstance::setVirtuals(LgsCodeGen* codeGen) const {
    const auto vtable = obj->vtable->type->asMap();
    const auto vtableGEP = codeGen->builder.CreateGEP(vtable->getIRType(codeGen), IRValue, {codeGen->i32Zero()});
    vtable->initFunc.callIR(codeGen, {vtableGEP, codeGen->i64(sizeof(void*))});
    for (const auto& [name, method] : obj->methods) {
        if (!method->funcType->isVirtual) continue;
        const auto keyIRStr = codeGen->getIRStr(method->funcType->getName());
        const auto IRFunc = method->getIRFunc(codeGen);
        const auto valuePtr = codeGen->builder.CreateAlloca(codeGen->ptrTy());
        codeGen->builder.CreateStore(IRFunc, valuePtr);
        vtable->addFunc.callIR(codeGen, {vtableGEP, keyIRStr, valuePtr});
    }
    for (const auto& [name, field] : obj->fields) {
        if (!field->isVirtual) continue;
        const auto keyIRStr = codeGen->getIRStr(field->name);
        const auto fieldGEP = field->getGEP(codeGen, IRValue);
        const auto fieldIRType = field->type->getIRType(codeGen);
        const auto loadGEP = codeGen->builder.CreateLoad(fieldIRType, fieldGEP);
        const auto valuePtr = codeGen->builder.CreateAlloca(fieldIRType);
        codeGen->builder.CreateStore(loadGEP, valuePtr);
        vtable->addFunc.callIR(codeGen, {vtableGEP, keyIRStr, valuePtr});
    }
}

void LgsInstance::free(LgsCodeGen* codeGen) {
    if (!isHeapAlloc) {
        codeGen->builder.CreateFree(IRValue);
    }
}

LgsInstance::~LgsInstance() {
    for (const auto arg : args) {
        delete arg.second;
    }
}
