#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsHashMap.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"

void LgsInstance::createIRValue(LgsCodeGen* codeGen) {
    const auto objIRType = obj->getIRType(codeGen);
    if(obj->singleton) {
        IRValue = codeGen->createGlobal(objIRType, ConstantAggregateZero::get(objIRType), obj->name);
    } else {
        IRValue = codeGen->builder.CreateAlloca(objIRType);
    }
    initFields(codeGen, obj->fields);
    if (!obj->interfaces.empty()) {
        setVirtuals(codeGen);
    }
}

LgsExpr* LgsInstance::castTo(LgsType* toType) {
    return this;
}

void LgsInstance::initFields(LgsCodeGen* codeGen, std::map<std::string, LgsField*>& fields) {
    for (const auto& [argName, arg] : args) {
        const auto exprIR = arg->expr->getIRValue(codeGen);
        auto field = fields.find(argName);
        if (field != fields.end()) {
            const auto gep = field->second->getIRValue(codeGen);
            codeGen->builder.CreateStore(exprIR, gep);
        }
    }
}

void LgsInstance::setVirtuals(LgsCodeGen* codeGen) const {
    const auto vtable = obj->vtable->type->asMap();
    const auto vtableGEP = codeGen->builder.CreateGEP(vtable->getIRType(codeGen), IRValue, {codeGen->i32Zero()});
    vtable->initFunc->callIR(codeGen, {vtableGEP, codeGen->i64(sizeof(void*))});
    for (const auto& [methodName, method] : obj->methods) {
        if (!method->funcType->isVirtual) continue;
        const auto keyIRStr = codeGen->getIRStr(method->funcType->getName());
        const auto IRFunc = method->getIRFunc(codeGen);
        const auto valuePtr = codeGen->builder.CreateAlloca(codeGen->ptrTy());
        codeGen->builder.CreateStore(IRFunc, valuePtr);
        vtable->addFunc->callIR(codeGen, {vtableGEP, keyIRStr, valuePtr});
    }
    for (const auto& [fieldName, field] : obj->fields) {
        if (!field->isVirtual) continue;
        const auto keyIRStr = codeGen->getIRStr(field->name);
        const auto objIR = obj->getIRType(codeGen);
        const auto fieldGEP = codeGen->builder.CreateStructGEP(objIR, IRValue, field->position);
        const auto fieldIRType = field->type->getIRType(codeGen);
        const auto loadGEP = codeGen->builder.CreateLoad(fieldIRType, fieldGEP);
        const auto valuePtr = codeGen->builder.CreateAlloca(fieldIRType);
        codeGen->builder.CreateStore(loadGEP, valuePtr);
        vtable->addFunc->callIR(codeGen, {vtableGEP, keyIRStr, valuePtr});
    }
}

std::string LgsInstance::pname() {
    return obj->name;
}

void LgsInstance::setObject(LgsObject* newObj) {
    obj = newObj;
    setType(obj);
}

LgsInstance::~LgsInstance() {
    for (const auto arg : args) {
        delete arg.second;
    }
    if (obj) {
        delete obj;
    }
}