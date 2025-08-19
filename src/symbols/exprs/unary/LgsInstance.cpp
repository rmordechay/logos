#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsHashMap.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"

json::value_ref LgsInstance::asJSON() {
    json::object obj;
    return obj;
}

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

void LgsInstance::initFields(LgsCodeGen* codeGen, std::map<std::string, LgsField*>& fields) {
    for (const auto& [argName, arg] : args) {
        const auto exprIR = arg->expr->getIRValue(codeGen);
        auto field = fields.find(argName);
        if (field != fields.end()) {
            field->second->parentIRValue = IRValue;
            const auto gep = field->second->getIRValue(codeGen);
            codeGen->builder.CreateStore(exprIR, gep);
        }
    }
}

void LgsInstance::setVirtuals(LgsCodeGen* codeGen) const {
    for (const auto& [methodName, method] : obj->methods) {
        if (!method->funcType->isVirtual) continue;
        const auto keyIRStr = codeGen->getIRStr(method->funcType->getName());
        const auto IRFunc = method->getIRFunc(codeGen);
        codeGen->addPtrToVtable(IRValue, keyIRStr, IRFunc);
    }
    for (const auto& [fieldName, field] : obj->fields) {
        if (!field->isVirtual) continue;
        const auto keyIRStr = codeGen->getIRStr(field->name);
        const auto objIR = obj->getIRType(codeGen);
        const auto fieldGEP = codeGen->builder.CreateStructGEP(objIR, IRValue, field->position);
        codeGen->addPtrToVtable(IRValue, keyIRStr, fieldGEP);
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
    for (const auto [_, arg] : args) {
        delete arg;
    }
    if (obj) {
        delete obj;
    }
}