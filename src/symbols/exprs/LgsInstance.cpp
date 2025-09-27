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
    const auto ft = cg.getFT(cg.voidTy(), {cg.ptrTy(), cg.ptrTy(), cg.ptrTy()});
    for (const auto& [methodName, method] : obj->methods) {
        if (!method->funcType->isVirtual) continue;
        const auto keyIRStr = cg.getIRStr(method->funcType->getName());
        const auto IRFunc = method->getIRFunc(cg);
        cg.callLgsFunc("vtable_add", ft, {IRValue, keyIRStr, IRFunc});
    }
    for (const auto& field : obj->fields) {
        if (!field->isVirtual) continue;
        const auto keyIRStr = cg.getIRStr(field->name);
        const auto objIR = obj->getIRType(cg);
        const auto fieldGEP = cg.builder.CreateStructGEP(objIR, IRValue, field->position);
        cg.callLgsFunc("vtable_add", ft, {IRValue, keyIRStr, fieldGEP});
    }
}

json::value LgsInstance::asJsonStr() {
    json::object jsonObj;
    jsonObj["exprType"] = "instance";
    jsonObj["obj"] = obj->asJsonStr();
    jsonObj["args"] = json::array();
    for (const auto& [argName, arg] : args) {
        jsonObj["args"].as_array().push_back(arg->asJsonStr());
    }
    return jsonObj;
}

std::string LgsInstance::pname() {
    return name;
}

bool LgsInstance::equals(LgsExpr* other) {
    const auto otherInstance = other->asInstance();
    if (!otherInstance) return false;
    assert(0);
}

LgsInstance::~LgsInstance() {
    for (const auto [_, arg] : args) {
        delete arg;
    }
    args.clear();
    if (obj) {
        for (const auto& field : obj->fields) {
            delete field;
        }
        for (const auto interface : obj->interfaces) {
            delete interface;
        }
        delete obj;
        obj = nullptr;
        type = nullptr;
    }
}
