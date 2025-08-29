#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsHashMap.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"

bool LgsFuncCall::equals(const LgsFuncType* funcType) const {
    if (funcType->hasDefaults) return equalsDefaultParams(funcType);
    if (funcType->isVariadic) return equalsVariadic(funcType);
    if (funcType->params.size() - funcType->isMethod != args.size()) return false;
    if (funcType->params.size() == 0 && args.size() == 0) return true;
    if (funcType->isLambda) return true;
    for (size_t i = funcType->isMethod; i < funcType->params.size(); ++i) {
        const auto paramType = funcType->params[i].type;
        const auto arg = args[i - funcType->isMethod];
        const auto argType = arg->type;
        if (!paramType || !argType) return false;
        if (arg->isNull) continue;
        if (!argType->canCastTo(paramType)) return false;
    }
    return true;
}

bool LgsFuncCall::equalsVariadic(const LgsFuncType* funcType) const {
    return true;
}

bool LgsFuncCall::equalsDefaultParams(const LgsFuncType* funcType) const {
    const auto argsSize = args.size();
    for (size_t i = funcType->isMethod; i < funcType->params.size(); ++i) {
        const auto param = funcType->params[i];
        if (i >= argsSize) continue;
        const auto arg = args[i];
        if (!param.type->canCastTo(arg->type)) return false;
    }
    return true;
}

void LgsFuncCall::resolveVirtualFunc(LgsLLVMGen& cg) const {
    const auto self = args[0];
    const auto keyIR = cg.getIRStr(func->funcType->getName());
    const auto selfPtr = self->IRValue;
    const auto rv = cg.getPtrFromVtable(selfPtr, keyIR);
    func->setIRValue(rv);
}

std::string LgsFuncCall::pname() {
    std::stringstream strStream;
    strStream << name << '(';
    for (size_t i = isMethodCall; i < args.size(); ++i) {
        strStream << args[i]->type->pname();
        if (i != args.size() - 1) strStream << ", ";
    }
    if (type && !type->isUnknown()) {
        strStream << "): " << type->pname();
    } else {
        strStream << ')';
    }
    return strStream.str();
}

json::value LgsFuncCall::asJSON() {
    json::object jsonObj;
    jsonObj["name"] = name;
    jsonObj["type"] = type->asJSON();
    json::array jsonArgs;
    for (const auto& arg : args) {
        jsonArgs.emplace_back(arg->asJSON());
    }
    return jsonObj;
}

LgsFuncCall::~LgsFuncCall() {
    for (const auto& arg : args) {
        delete arg;
    }
}
