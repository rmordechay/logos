#include "exprs/LgsInstance.h"
#include "exprs/LgsHashMap.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"

Value* LgsInstance::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

void LgsInstance::setObject(LgsObject* newObj) {
    obj = newObj;
    setType(obj);
}

void LgsInstance::setVirtuals(LgsLLVMGen& cg) const {
    for (const auto& [methodName, method] : obj->methods) {
        if (!method->funcType->isVirtual) continue;
        const auto keyIRStr = cg.getIRStr(method->funcType->getName());
        const auto IRFunc = method->getIRFunc(cg);
        cg.addPtrToVtable(IRValue, keyIRStr, IRFunc);
    }
    for (const auto& field : obj->fields) {
        if (!field->isVirtual) continue;
        const auto keyIRStr = cg.getIRStr(field->name);
        const auto objIR = obj->getIRType(cg);
        const auto fieldGEP = cg.builder.CreateStructGEP(objIR, IRValue, field->position);
        cg.addPtrToVtable(IRValue, keyIRStr, fieldGEP);
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
    args.clear();
    if (obj) {
        freeType(obj);
        obj = nullptr;
        type = nullptr;
    }
}
