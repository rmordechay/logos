#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsHashMap.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"
#include "types/LgsTable.h"

void LgsInstance::createIRTable(LgsLLVM& codeGen) {
    const auto tableFieldType = codeGen.getStructType({codeGen.ptrTy(), codeGen.ptrTy()}, "_Table_Field");
    const auto fieldsType = ArrayType::get(tableFieldType, 1024);
    const auto tableType = codeGen.getStructType({codeGen.ptrTy(), codeGen.sizeTy(), fieldsType}, "_Table");
    IRValue = codeGen.builder.CreateAlloca(tableType);
    codeGen.callLgsFunc("Table_init", codeGen.getFT(codeGen.voidTy(), {codeGen.ptrTy()}), {IRValue});
    const auto ft = codeGen.getFT(codeGen.voidTy(), {codeGen.ptrTy(), codeGen.ptrTy(), codeGen.ptrTy()});
    for (int i = 0; i < table->fields.size(); ++i) {
        const auto fieldNameIR = codeGen.getIRStr(table->fields[i]->name);
        const auto fieldTypeIR = codeGen.getIRStr(table->fields[i]->type->getName());
        codeGen.callLgsFunc("Table_add", ft, {IRValue, fieldNameIR, fieldTypeIR});
    }
}

void LgsInstance::setObject(LgsObject* newObj) {
    obj = newObj;
    setType(obj);
}

void LgsInstance::setVirtuals(LgsLLVM& codeGen) const {
    for (const auto& [methodName, method] : obj->methods) {
        if (!method->funcType->isVirtual) continue;
        const auto keyIRStr = codeGen.getIRStr(method->funcType->getName());
        const auto IRFunc = method->getIRFunc(codeGen);
        codeGen.addPtrToVtable(IRValue, keyIRStr, IRFunc);
    }
    for (const auto& field : obj->fields) {
        if (!field->isVirtual) continue;
        const auto keyIRStr = codeGen.getIRStr(field->name);
        const auto objIR = obj->getIRType(codeGen);
        const auto fieldGEP = codeGen.builder.CreateStructGEP(objIR, IRValue, field->position);
        codeGen.addPtrToVtable(IRValue, keyIRStr, fieldGEP);
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
