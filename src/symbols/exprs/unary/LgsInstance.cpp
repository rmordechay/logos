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
    initFields(codeGen);
    if (!obj->interfaces.empty()) {
        setVirtuals(codeGen);
    }
}

void LgsInstance::initFields(LgsCodeGen* codeGen) {
    for (const auto& [argName, arg] : args) {
        const auto exprIR = arg->expr->getIRValue(codeGen);
        const auto field = obj->getField(argName);
        if (!field) continue;
        field->parentIRValue = IRValue;
        const auto gep = field->getIRValue(codeGen);
        codeGen->builder.CreateStore(exprIR, gep);
    }
}

void LgsInstance::setObject(LgsObject* newObj) {
    obj = newObj;
    setType(obj);
}

void LgsInstance::setVirtuals(LgsCodeGen* codeGen) const {
    for (const auto& [methodName, method] : obj->methods) {
        if (!method->funcType->isVirtual) continue;
        const auto keyIRStr = codeGen->getIRStr(method->funcType->getName());
        const auto IRFunc = method->getIRFunc(codeGen);
        codeGen->addPtrToVtable(IRValue, keyIRStr, IRFunc);
    }
    for (const auto& field : obj->fields) {
        if (!field->isVirtual) continue;
        const auto keyIRStr = codeGen->getIRStr(field->name);
        const auto objIR = obj->getIRType(codeGen);
        const auto fieldGEP = codeGen->builder.CreateStructGEP(objIR, IRValue, field->position);
        codeGen->addPtrToVtable(IRValue, keyIRStr, fieldGEP);
    }
}

json::value LgsInstance::asJSON() {
    json::object jsonObj;
    jsonObj["exprType"] = "instance";
    jsonObj["obj"] = obj->asJSON();
    jsonObj["args"] = json::array();
    for (const auto& [argName, arg] : args) {
        jsonObj["args"].as_array().push_back(arg->asJSON());
    }
    return jsonObj;
}

std::string LgsInstance::pname() {
    return obj->name;
}

LgsInstance::~LgsInstance() {
    for (const auto [_, arg] : args) {
        delete arg;
    }
    if (obj) {
        delete obj;
    }
}
